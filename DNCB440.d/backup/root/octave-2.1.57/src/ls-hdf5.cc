/*

Copyright (C) 1996, 1997 John W. Eaton

This file is part of Octave.

Octave is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2, or (at your option) any
later version.

Octave is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with Octave; see the file COPYING.  If not, write to the Free
Software Foundation, 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

// Author: Steven G. Johnson <stevenj@alum.mit.edu>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#if defined (HAVE_HDF5)

#include <cfloat>
#include <cstring>
#include <cctype>

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include <hdf5.h>

#include "byte-swap.h"
#include "data-conv.h"
#include "file-ops.h"
#include "glob-match.h"
#include "lo-mappers.h"
#include "lo-sstream.h"
#include "mach-info.h"
#include "oct-env.h"
#include "oct-time.h"
#include "quit.h"
#include "str-vec.h"

#include "Cell.h"
#include "defun.h"
#include "error.h"
#include "gripes.h"
#include "load-save.h"
#include "oct-obj.h"
#include "oct-map.h"
#include "ov-cell.h"
#include "pager.h"
#include "pt-exp.h"
#include "symtab.h"
#include "sysdep.h"
#include "unwind-prot.h"
#include "utils.h"
#include "variables.h"
#include "version.h"
#include "dMatrix.h"

#include "ls-utils.h"
#include "ls-hdf5.h"

static std::string
make_valid_identifier (const std::string& nm)
{
  std::string retval;

  size_t nm_len = nm.length ();

  if (nm_len > 0)
    {
      if (! isalpha (nm[0]))
	retval += '_';

      for (size_t i = 0; i < nm_len; i++)
	{
	  char c = nm[i];
	  retval += (isalnum (c) || c == '_') ? c : '_';
	}
    }

  return retval;
}

// Define this to 1 if/when HDF5 supports automatic conversion between
// integer and floating-point binary data:
#define HAVE_HDF5_INT2FLOAT_CONVERSIONS 0

// Given two compound types t1 and t2, determine whether they 
// are compatible for reading/writing.  This function only
// works for non-nested types composed of simple elements (ints, floats...),
// which is all we need it for

bool
hdf5_types_compatible (hid_t t1, hid_t t2)
{
  int n;
  if ((n = H5Tget_nmembers (t1)) != H5Tget_nmembers (t2))
    return false;

  for (int i = 0; i < n; ++i)
    {
      hid_t mt1 = H5Tget_member_type (t1, i);
      hid_t mt2 = H5Tget_member_type (t2, i);

      if (H5Tget_class (mt1) != H5Tget_class (mt2))
	return false;

      H5Tclose (mt2);
      H5Tclose (mt1);
    }

  return true;
}

// Return true if loc_id has the attribute named attr_name, and false
// otherwise.

bool
hdf5_check_attr (hid_t loc_id, const char *attr_name)
{
  bool retval = false;

  // we have to pull some shenanigans here to make sure
  // HDF5 doesn't print out all sorts of error messages if we
  // call H5Aopen for a non-existing attribute

  H5E_auto_t err_func;
  void *err_func_data;

  // turn off error reporting temporarily, but save the error
  // reporting function:

  H5Eget_auto (&err_func, &err_func_data);
  H5Eset_auto (0, 0);

  hid_t attr_id = H5Aopen_name (loc_id, attr_name);

  if (attr_id >= 0)
    {
      // successful
      retval = 1;
      H5Aclose (attr_id);
    }

  // restore error reporting:
  H5Eset_auto (err_func, err_func_data);

  return retval;
}

// The following subroutines creates an HDF5 representations of the way
// we will store Octave complex types (pairs of floating-point numbers).
// NUM_TYPE is the HDF5 numeric type to use for storage (e.g. 
// H5T_NATIVE_DOUBLE to save as 'double'). Note that any necessary 
// conversions are handled automatically by HDF5.

hid_t
hdf5_make_complex_type (hid_t num_type)
{
  hid_t type_id = H5Tcreate (H5T_COMPOUND, sizeof (double) * 2);

  H5Tinsert (type_id, "real", 0 * sizeof (double), num_type);
  H5Tinsert (type_id, "imag", 1 * sizeof (double), num_type);

  return type_id;
}

// This variable, set in read_hdf5_data(), tells whether we are using
// a version of HDF5 with a buggy H5Giterate (i.e. which neglects to
// increment the index parameter to the next unread item).
static bool have_h5giterate_bug = false;

// This function is designed to be passed to H5Giterate, which calls it
// on each data item in an HDF5 file.  For the item whose name is NAME in
// the group GROUP_ID, this function sets dv->tc to an Octave representation
// of that item.  (dv must be a pointer to hdf5_callback_data.)  (It also
// sets the other fields of dv).
//
// It returns 1 on success (in which case H5Giterate stops and returns),
// -1 on error, and 0 to tell H5Giterate to continue on to the next item
// (e.g. if NAME was a data type we don't recognize).

herr_t
hdf5_read_next_data (hid_t group_id, const char *name, void *dv)
{
  hdf5_callback_data *d = static_cast <hdf5_callback_data *> (dv);
  hid_t type_id = -1, type_class_id = -1, data_id = -1, subgroup_id = -1,
    space_id = -1;

  H5G_stat_t info;
  herr_t retval = 0;
  bool ident_valid = valid_identifier (name);

  std::string vname = name;

  // Allow identifiers as all digits so we can load lists saved by
  // earlier versions of Octave.

  if (! ident_valid )
    {
      // fix the identifier, replacing invalid chars with underscores
      vname = make_valid_identifier (vname);

      // check again (in case vname was null, empty, or some such thing):
      ident_valid = valid_identifier (vname); 
    }

  H5Gget_objinfo (group_id, name, 1, &info);

  if (info.type == H5G_GROUP && ident_valid)
    {
      subgroup_id = H5Gopen (group_id, name);

      if (subgroup_id < 0)
	{
	  retval = subgroup_id;
	  goto done;
	}

      if (hdf5_check_attr (subgroup_id, "OCTAVE_NEW_FORMAT"))
	{
	  data_id = H5Dopen (subgroup_id, "type");

	  if (data_id < 0)
	    {
	      retval = data_id;
	      goto done;
	    }

	  type_id = H5Dget_type (data_id);

	  type_class_id = H5Tget_class (type_id);

	  if (type_class_id != H5T_STRING)
	    goto done;
	  
	  space_id = H5Dget_space (data_id);
	  hsize_t rank = H5Sget_simple_extent_ndims (space_id);

	  if (rank != 0)
	    goto done;

	  int slen = H5Tget_size (type_id);
	  if (slen < 0)
	    goto done;

	  OCTAVE_LOCAL_BUFFER (char, typ, slen);

	  // create datatype for (null-terminated) string to read into:
	  hid_t st_id = H5Tcopy (H5T_C_S1);
	  H5Tset_size (st_id, slen);

	  if (H5Dread (data_id, st_id, H5S_ALL, H5S_ALL, H5P_DEFAULT, 
		       (void *) typ) < 0)
	    goto done;

	  H5Tclose (st_id);
	  H5Dclose (data_id);

	  d->tc = octave_value_typeinfo::lookup_type (typ);

	  retval = (d->tc.load_hdf5 (subgroup_id, "value", 
		have_h5giterate_bug) ? 1 : -1);

	  // check for OCTAVE_GLOBAL attribute:
	  d->global = hdf5_check_attr (subgroup_id, "OCTAVE_GLOBAL");

	  H5Gclose (subgroup_id);
	}
      else
	{
	  // an HDF5 group is treated as an octave structure by
	  // default (since that preserves name information), and an
	  // octave list otherwise.

	  if (hdf5_check_attr (subgroup_id, "OCTAVE_LIST"))
	    d->tc = octave_value_typeinfo::lookup_type ("list");
	  else
	    d->tc = octave_value_typeinfo::lookup_type ("cell");
	  
	  // check for OCTAVE_GLOBAL attribute:
	  d->global = hdf5_check_attr (subgroup_id, "OCTAVE_GLOBAL");

	  H5Gclose (subgroup_id);

	  retval = (d->tc.load_hdf5 (group_id, name, have_h5giterate_bug) 
		    ? 1 : -1);
	}

    }
  else if (info.type == H5G_DATASET && ident_valid)
    {
      // For backwards compatiability.
      data_id = H5Dopen (group_id, name);

      if (data_id < 0)
	{
	  retval = data_id;
	  goto done;
	}

      type_id = H5Dget_type (data_id);
      
      type_class_id = H5Tget_class (type_id);

#if HAVE_HDF5_INT2FLOAT_CONVERSIONS
      if (type_class_id == H5T_INTEGER || type_class_id == H5T_FLOAT)
#else
      // hdf5 doesn't (yet) support automatic float/integer conversions
      if (type_class_id == H5T_FLOAT)
#endif
	{
	  space_id = H5Dget_space (data_id);

	  hsize_t rank = H5Sget_simple_extent_ndims (space_id);
	  
	  if (rank == 0)
	    d->tc = octave_value_typeinfo::lookup_type ("scalar");
	  else
	    d->tc = octave_value_typeinfo::lookup_type ("matrix");

	  H5Sclose (space_id);
	}
      else if (type_class_id == H5T_STRING)
	d->tc = octave_value_typeinfo::lookup_type ("string");
      else if (type_class_id == H5T_COMPOUND)
	{
	  hid_t complex_type = hdf5_make_complex_type (H5T_NATIVE_DOUBLE);

	  if (hdf5_types_compatible (type_id, complex_type))
	    {
	      // read complex matrix or scalar variable
	      space_id = H5Dget_space (data_id);
	      hsize_t rank = H5Sget_simple_extent_ndims (space_id);
		  
	      if (rank == 0)
		d->tc = octave_value_typeinfo::lookup_type ("complex scalar");
	      else
		d->tc = octave_value_typeinfo::lookup_type ("complex matrix");

	      H5Sclose (space_id);
	    }
	  else
	    // Assume that if its not complex its a range. If its not
	    // it'll be rejected later in the range code
	    d->tc = octave_value_typeinfo::lookup_type ("range");

	  H5Tclose (complex_type);
	}
      else
	{
	  warning ("load: can't read `%s' (unknown datatype)", name);
	  retval = 0; // unknown datatype; skip
	}
      
      // check for OCTAVE_GLOBAL attribute:
      d->global = hdf5_check_attr (data_id, "OCTAVE_GLOBAL");

      H5Tclose (type_id);
      H5Dclose (data_id);

      retval = (d->tc.load_hdf5 (group_id, name, have_h5giterate_bug) 
		? 1 : -1);
    }

  if (!ident_valid)
    {
      // should we attempt to handle invalid identifiers by converting
      // bad characters to '_', say?
      warning ("load: skipping invalid identifier `%s' in hdf5 file",
	       name);
    }

 done:
  if (retval < 0)
    error ("load: error while reading hdf5 item %s", name);
  
  if (retval > 0)
    {
      // get documentation string, if any:
      int comment_length = H5Gget_comment (group_id, name, 0, 0);

      if (comment_length > 1)
	{
	  OCTAVE_LOCAL_BUFFER (char, tdoc, comment_length);
	  H5Gget_comment (group_id, name, comment_length, tdoc);
	  d->doc = tdoc;
	}
      else if (vname != name)
	{
	  // the name was changed; store the original name
	  // as the documentation string:
	  d->doc = name;
	}

      // copy name (actually, vname):
      d->name = vname;
    }

  return retval;
}

// Read the next Octave variable from the stream IS, which must really be
// an hdf5_ifstream.  Return the variable value in tc, its doc string
// in doc, and whether it is global in global.  The return value is
// the name of the variable, or NULL if none were found or there was
// and error.
std::string
read_hdf5_data (std::istream& is, const std::string& /* filename */, 
		bool& global, octave_value& tc, std::string& doc)
{
  std::string retval;

  doc.resize (0);

  hdf5_ifstream& hs = (hdf5_ifstream&) is;
  hdf5_callback_data d;

  // Versions of HDF5 prior to 1.2.2 had a bug in H5Giterate where it
  // would return the index of the last item processed instead of the
  // next item to be processed, forcing us to increment the index manually.

  unsigned int vers_major, vers_minor, vers_release;

  H5get_libversion (&vers_major, &vers_minor, &vers_release);

  // XXX FIXME XXX -- this test looks wrong.
  have_h5giterate_bug
    = (vers_major < 1
       || (vers_major == 1 && (vers_minor < 2
			       || (vers_minor == 2 && vers_release < 2))));

  herr_t H5Giterate_retval = -1;

#ifdef HAVE_H5GGET_NUM_OBJS
  hsize_t num_obj = 0;
  H5Gget_num_objs (hs.file_id, &num_obj);
  if (hs.current_item < static_cast<int> (num_obj))
#endif
    H5Giterate_retval = H5Giterate (hs.file_id, "/", &hs.current_item,
				    hdf5_read_next_data, &d);

  if (have_h5giterate_bug)
    {
      // H5Giterate sets current_item to the last item processed; we want
      // the index of the next item (for the next call to read_hdf5_data)

      hs.current_item++;
    }

  if (H5Giterate_retval > 0)
    {
      global = d.global;
      tc = d.tc;
      doc = d.doc;
    }
  else
    {
      // an error occurred (H5Giterate_retval < 0) or there are no
      // more datasets print an error message if retval < 0?
      // hdf5_read_next_data already printed one, probably.
    }

  if (! d.name.empty ())
    retval = d.name;

  return retval;
}

// Add an attribute named attr_name to loc_id (a simple scalar
// attribute with value 1).  Return value is >= 0 on success.
static herr_t
hdf5_add_attr (hid_t loc_id, const char *attr_name)
{
  herr_t retval = 0;

  hid_t as_id = H5Screate (H5S_SCALAR);

  if (as_id >= 0)
    {
      hid_t a_id = H5Acreate (loc_id, attr_name,
			      H5T_NATIVE_UCHAR, as_id, H5P_DEFAULT);

      if (a_id >= 0)
	{
	  unsigned char attr_val = 1;

	  retval = H5Awrite (a_id, H5T_NATIVE_UCHAR, (void*) &attr_val);

	  H5Aclose (a_id);
	}
      else
	retval = a_id;

      H5Sclose (as_id);
    }
  else
    retval = as_id;

  return retval;
}

// Save an empty matrix, if needed. Returns
//    > 0  Saved empty matrix
//    = 0  Not an empty matrix; did nothing
//    < 0  Error condition
int
save_hdf5_empty (hid_t loc_id, const char *name, const dim_vector d)
{
  hsize_t sz = d.length ();
  int dims[sz];
  bool empty = false;
  hid_t space_hid = -1, data_hid = -1;
  int retval;
  for (hsize_t i = 0; i < sz; i++)
    {
      dims[i] = d(i);
      if (dims[i] < 1)
	empty = true;
    }

  if (!empty)
    return 0;

  space_hid = H5Screate_simple (1, &sz, (hsize_t *) 0);
  if (space_hid < 0) return space_hid;

  data_hid = H5Dcreate (loc_id, name, H5T_NATIVE_INT, space_hid, 
			H5P_DEFAULT);
  if (data_hid < 0)
    {
      H5Sclose (space_hid);
      return data_hid;
    }
  
  retval = H5Dwrite (data_hid, H5T_NATIVE_INT, H5S_ALL, H5S_ALL,
		     H5P_DEFAULT, (void*) dims) >= 0;

  H5Dclose (data_hid);
  H5Sclose (space_hid);

  if (retval >= 0)
    retval = hdf5_add_attr (loc_id, "OCTAVE_EMPTY_MATRIX");
  
  return (retval == 0 ? 1 : retval);
}

// Load an empty matrix, if needed. Returns
//    > 0  loaded empty matrix, dimensions returned
//    = 0  Not an empty matrix; did nothing
//    < 0  Error condition
int
load_hdf5_empty (hid_t loc_id, const char *name, dim_vector &d)
{
  if (!hdf5_check_attr(loc_id, "OCTAVE_EMPTY_MATRIX"))
    return 0;

  hsize_t hdims, maxdims;
  hid_t data_hid = H5Dopen (loc_id, name);
  hid_t space_id = H5Dget_space (data_hid);
  H5Sget_simple_extent_dims (space_id, &hdims, &maxdims);
  int dims[hdims];
  int retval;

  retval = H5Dread (data_hid, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, 
		    H5P_DEFAULT, (void *) dims);
  if (retval >= 0)
    {
      d.resize (hdims);
      for (hsize_t i = 0; i < hdims; i++)
	d(i) = dims[i];
    }

  H5Sclose (space_id);
  H5Dclose (data_hid);

  return (retval == 0 ? hdims : retval);
}

// save_type_to_hdf5 is not currently used, since hdf5 doesn't yet support
// automatic float<->integer conversions:

#if HAVE_HDF5_INT2FLOAT_CONVERSIONS

// return the HDF5 type id corresponding to the Octave save_type

hid_t
save_type_to_hdf5 (save_type st)
{
  switch (st)
    {
    case LS_U_CHAR:
      return H5T_NATIVE_UCHAR;

    case LS_U_SHORT:
      return H5T_NATIVE_USHORT;

    case LS_U_INT:
      return H5T_NATIVE_UINT;

    case LS_CHAR:
      return H5T_NATIVE_CHAR;

    case LS_SHORT:
      return H5T_NATIVE_SHORT;

    case LS_INT:
      return H5T_NATIVE_INT;

    case LS_FLOAT:
      return H5T_NATIVE_FLOAT;

    case LS_DOUBLE:
    default:
      return H5T_NATIVE_DOUBLE;
    }
}
#endif /* HAVE_HDF5_INT2FLOAT_CONVERSIONS */

// Add the data from TC to the HDF5 location loc_id, which could
// be either a file or a group within a file.  Return true if
// successful.  This function calls itself recursively for lists
// (stored as HDF5 groups).

bool
add_hdf5_data (hid_t loc_id, const octave_value& tc,
	       const std::string& name, const std::string& doc,
	       bool mark_as_global, bool save_as_floats)
{
  hsize_t dims[3];
  hid_t type_id = -1, space_id = -1, data_id = -1, data_type_id = -1;
  bool retval = false;
  octave_value val = tc;
  std::string t = tc.type_name();

  data_id = H5Gcreate (loc_id, name.c_str (), 0);
  if (data_id < 0)
    goto error_cleanup;

  // attach the type of the variable
  type_id = H5Tcopy (H5T_C_S1); H5Tset_size (type_id, t.length () + 1);
  if (type_id < 0)
    goto error_cleanup;

  dims[0] = 0;
  space_id = H5Screate_simple (0 , dims, (hsize_t*) 0);
  if (space_id < 0)
    goto error_cleanup;

  data_type_id = H5Dcreate (data_id, "type",  type_id, space_id, H5P_DEFAULT);
  if (data_type_id < 0 || H5Dwrite (data_type_id, type_id, H5S_ALL, H5S_ALL, 
				    H5P_DEFAULT, (void*) t.c_str ()) < 0)
    goto error_cleanup;

  // Now call the real function to save the variable
  retval = val.save_hdf5 (data_id, "value", save_as_floats);

  // attach doc string as comment:
  if (retval && doc.length () > 0
      && H5Gset_comment (loc_id, name.c_str (), doc.c_str ()) < 0)
    retval = false;

  // if it's global, add an attribute "OCTAVE_GLOBAL" with value 1
  if (retval && mark_as_global)
    retval = hdf5_add_attr (data_id, "OCTAVE_GLOBAL") >= 0;

  // We are saving in the new variable format, so mark it
  if (retval)
    retval = hdf5_add_attr (data_id, "OCTAVE_NEW_FORMAT") >= 0;

 error_cleanup:

  if (data_type_id >= 0)
    H5Dclose (data_type_id);

  if (type_id >= 0)
    H5Tclose (type_id);

  if (space_id >= 0)
    H5Sclose (space_id);

  if (data_id >= 0)
    H5Gclose (data_id);

  if (! retval)
    error ("save: error while writing `%s' to hdf5 file", name.c_str ());

  return retval;
}

// Write data from TC in HDF5 (binary) format to the stream OS,
// which must be an hdf5_ofstream, returning true on success.

bool
save_hdf5_data (std::ostream& os, const octave_value& tc,
		const std::string& name, const std::string& doc,
		bool mark_as_global, bool save_as_floats)
{
  hdf5_ofstream& hs = (hdf5_ofstream&) os;

  return add_hdf5_data (hs.file_id, tc, name, doc,
			mark_as_global, save_as_floats);
}

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
