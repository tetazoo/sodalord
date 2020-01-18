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

#if defined (__GNUG__) && defined (USE_PRAGMA_INTERFACE_IMPLEMENTATION)
#pragma implementation
#endif

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>
#include <vector>

#include "lo-ieee.h"
#include "mx-base.h"

#include "gripes.h"
#include "oct-obj.h"
#include "ops.h"
#include "ov-base.h"
#include "ov-base-mat.h"
#include "ov-base-mat.cc"
#include "ov-bool.h"
#include "ov-bool-mat.h"
#include "ov-re-mat.h"
#include "pr-output.h"

#include "byte-swap.h"
#include "ls-oct-ascii.h"
#include "ls-hdf5.h"
#include "ls-utils.h"

template class octave_base_matrix<boolNDArray>;

DEFINE_OCTAVE_ALLOCATOR (octave_bool_matrix);

DEFINE_OV_TYPEID_FUNCTIONS_AND_DATA (octave_bool_matrix,
				     "bool matrix", "logical");

static octave_value *
default_numeric_conversion_function (const octave_value& a)
{
  CAST_CONV_ARG (const octave_bool_matrix&);

  return new octave_matrix (NDArray (v.bool_array_value ()));
}

type_conv_fcn
octave_bool_matrix::numeric_conversion_function (void) const
{
  return default_numeric_conversion_function;
}

octave_value *
octave_bool_matrix::try_narrowing_conversion (void)
{
  octave_value *retval = 0;

  if (matrix.ndims () == 2)
    {
      boolMatrix bm = matrix.matrix_value ();

      int nr = bm.rows ();
      int nc = bm.cols ();

      if (nr == 1 && nc == 1)
	retval = new octave_bool (bm (0, 0));
    }

  return retval;
}

bool
octave_bool_matrix::valid_as_scalar_index (void) const
{
  // XXX FIXME XXX
  return false;
}

double
octave_bool_matrix::double_value (bool) const
{
  double retval = lo_ieee_nan_value ();

  // XXX FIXME XXX -- maybe this should be a function, valid_as_scalar()
  if (rows () > 0 && columns () > 0)
    {
      // XXX FIXME XXX -- is warn_fortran_indexing the right variable here?
      if (Vwarn_fortran_indexing)
	gripe_implicit_conversion ("bool matrix", "real scalar");

      retval = matrix (0, 0);
    }
  else
    gripe_invalid_conversion ("bool matrix", "real scalar");

  return retval;
}

Complex
octave_bool_matrix::complex_value (bool) const
{
  double tmp = lo_ieee_nan_value ();

  Complex retval (tmp, tmp);

  // XXX FIXME XXX -- maybe this should be a function, valid_as_scalar()
  if (rows () > 0 && columns () > 0)
    {
      // XXX FIXME XXX -- is warn_fortran_indexing the right variable here?
      if (Vwarn_fortran_indexing)
	gripe_implicit_conversion ("bool matrix", "complex scalar");

      retval = matrix (0, 0);
    }
  else
    gripe_invalid_conversion ("bool matrix", "complex scalar");

  return retval;
}

octave_value
octave_bool_matrix::convert_to_str_internal (bool pad, bool force) const
{
  octave_value tmp = octave_value (matrix_value ());
  return tmp.convert_to_str (pad, force);
}

void
octave_bool_matrix::print_raw (std::ostream& os,
			       bool pr_as_read_syntax) const
{
  octave_print_internal (os, matrix, pr_as_read_syntax,
			 current_print_indent_level ());
}

bool 
octave_bool_matrix::save_ascii (std::ostream& os, bool& /* infnan_warned */,
				bool /* strip_nan_and_inf */)
{
  dim_vector d = dims ();
  if (d.length () > 2)
    {
      NDArray tmp = array_value ();
      os << "# ndims: " << d.length () << "\n";

      for (int i=0; i < d.length (); i++)
	os << " " << d (i);

      os << "\n" << tmp;
    }
  else
    {
      // Keep this case, rather than use generic code above for backward 
      // compatiability. Makes load_ascii much more complex!!
      os << "# rows: " << rows () << "\n"
	 << "# columns: " << columns () << "\n";

      Matrix tmp = matrix_value ();

      os << tmp;
    }

  return true;
}

bool 
octave_bool_matrix::load_ascii (std::istream& is)
{
  int mdims = 0;
  bool success = true;
  std::streampos pos = is.tellg ();

  if (extract_keyword (is, "ndims", mdims, true))
    {
      if (mdims >= 0)
	{
	  dim_vector dv;
	  dv.resize (mdims);

	  for (int i = 0; i < mdims; i++)
	    is >> dv(i);

	  NDArray tmp(dv);
	  is >> tmp;

	  if (!is) 
	    {
	      error ("load: failed to load matrix constant");
	      success = false;
	    }

	  boolNDArray btmp (dv);
	  for (int i = 0; i < btmp.nelem (); i++)
	      btmp.elem (i) = (tmp.elem (i) != 0.);
	  
	  matrix = btmp;
	}
      else
	{
	  error ("load: failed to extract number of rows and columns");
	  success = false;
	}
    }
  else
    {
      int nr = 0;
      int nc = 0;

      // re-read the same line again
      is.clear ();
      is.seekg (pos);

      if (extract_keyword (is, "rows", nr) && nr >= 0
	  && extract_keyword (is, "columns", nc) && nc >= 0)
	{
	  if (nr > 0 && nc > 0)
	    {
	      Matrix tmp (nr, nc);
	      is >> tmp;
	      if (!is) 
		{
		  error ("load: failed to load matrix constant");
		  success = false;
		}

	      boolMatrix btmp (nr,nc);
	      for (int j = 0; j < nc; j++)
		for (int i = 0; i < nr; i++)
		  btmp.elem (i,j) = (tmp.elem (i, j) != 0.);
	      
	      matrix = btmp;
	    }
	  else if (nr == 0 || nc == 0)
	    matrix = boolMatrix (nr, nc);
	  else
	    panic_impossible ();
	}
      else 
	{
	  error ("load: failed to extract number of rows and columns");
	  success = false;
	}
    }

  return success;
}

bool 
octave_bool_matrix::save_binary (std::ostream& os, bool& /* save_as_floats */)
{

  dim_vector d = dims ();
  if (d.length() < 1)
    return false;

  // Use negative value for ndims to differentiate with old format!!
  FOUR_BYTE_INT tmp = - d.length();
  os.write (X_CAST (char *, &tmp), 4);
  for (int i=0; i < d.length (); i++)
    {
      tmp = d(i);
      os.write (X_CAST (char *, &tmp), 4);
    }

  boolNDArray m = bool_array_value ();
  bool *mtmp = m.fortran_vec ();
  int nel = m.nelem ();
  OCTAVE_LOCAL_BUFFER (char, htmp, nel);

  for (int i = 0; i < nel; i++)
    htmp[i] = (mtmp[i] ? 1 : 0);

  os.write (htmp, nel);

  return true;
}

bool 
octave_bool_matrix::load_binary (std::istream& is, bool swap,
				 oct_mach_info::float_format /* fmt */)
{
  FOUR_BYTE_INT mdims;
  if (! is.read (X_CAST (char *, &mdims), 4))
    return false;
  if (swap)
    swap_4_bytes (X_CAST (char *, &mdims));
  if (mdims >= 0)
    return false;

  // mdims is negative for consistency with other matrices, where it is
  // negative to allow the positive value to be used for rows/cols for
  // backward compatibility
  mdims = - mdims;
  FOUR_BYTE_INT di;
  dim_vector dv;
  dv.resize (mdims);

  for (int i = 0; i < mdims; i++)
    {
      if (! is.read (X_CAST (char *, &di), 4))
	return false;
      if (swap)
	swap_4_bytes (X_CAST (char *, &di));
      dv(i) = di;
    }
  
  int nel = dv.numel ();
  OCTAVE_LOCAL_BUFFER (char, htmp, nel);
  if (! is.read (htmp, nel))
    return false;
  boolNDArray m(dv);
  bool *mtmp = m.fortran_vec ();
  for (int i = 0; i < nel; i++)
    mtmp[i] = (htmp[i] ? 1 : 0);
  matrix = m;

  return true;
}

#if defined (HAVE_HDF5)
bool
octave_bool_matrix::save_hdf5 (hid_t loc_id, const char *name,
			       bool /* save_as_floats */)
{
  dim_vector dv = dims ();
  int empty = save_hdf5_empty (loc_id, name, dv);
  if (empty)
    return (empty > 0);

  int rank = dv.length ();
  hid_t space_hid = -1, data_hid = -1;
  bool retval = true;
  boolNDArray m = bool_array_value ();

  OCTAVE_LOCAL_BUFFER (hsize_t, hdims, rank);

  // Octave uses column-major, while HDF5 uses row-major ordering
  for (int i = 0; i < rank; i++)
    hdims[i] = dv (rank-i-1);

  space_hid = H5Screate_simple (rank, hdims, 0);
  if (space_hid < 0) return false;

  data_hid = H5Dcreate (loc_id, name, H5T_NATIVE_HBOOL, space_hid, 
			H5P_DEFAULT);
  if (data_hid < 0)
    {
      H5Sclose (space_hid);
      return false;
    }

  int nel = m.nelem ();
  bool *mtmp = m.fortran_vec ();
  hbool_t htmp[nel];
  
  for (int i = 0; i < nel; i++)
    htmp[i] = mtmp[i];

  retval = H5Dwrite (data_hid, H5T_NATIVE_HBOOL, H5S_ALL, H5S_ALL,
		     H5P_DEFAULT, htmp) >= 0;

  H5Dclose (data_hid);
  H5Sclose (space_hid);

  return retval;
}

bool
octave_bool_matrix::load_hdf5 (hid_t loc_id, const char *name,
			       bool /* have_h5giterate_bug */)
{
  bool retval = false;

  dim_vector dv;
  int empty = load_hdf5_empty (loc_id, name, dv);
  if (empty > 0)
    matrix.resize(dv);
  if (empty)
    return (empty > 0);

  hid_t data_hid = H5Dopen (loc_id, name);
  hid_t space_id = H5Dget_space (data_hid);

  hsize_t rank = H5Sget_simple_extent_ndims (space_id);
  
  if (rank < 1)
    {
      H5Dclose (data_hid);
      return false;
    }

  OCTAVE_LOCAL_BUFFER (hsize_t, hdims, rank);
  OCTAVE_LOCAL_BUFFER (hsize_t, maxdims, rank);

  H5Sget_simple_extent_dims (space_id, hdims, maxdims);

  // Octave uses column-major, while HDF5 uses row-major ordering
  if (rank == 1)
    {
      dv.resize (2);
      dv(0) = 1;
      dv(1) = hdims[0];
    }
  else
    {
      dv.resize (rank);
      for (hsize_t i = 0, j = rank - 1; i < rank; i++, j--)
	dv(j) = hdims[i];
    }

  int nel = dv.numel ();
  hbool_t htmp[nel];
  if (H5Dread (data_hid, H5T_NATIVE_HBOOL, H5S_ALL, H5S_ALL, 
	       H5P_DEFAULT, htmp) >= 0) 
    {
      retval = true;

      boolNDArray btmp (dv);
      for (int i = 0; i < nel; i++)
	  btmp.elem (i) = htmp[i];

      matrix = btmp;
    }

  H5Dclose (data_hid);

  return retval;
}
#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
