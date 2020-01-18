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

#include "defun.h"
#include "gripes.h"
#include "oct-obj.h"
#include "ov-scalar.h"
#include "ov-base.h"
#include "ov-base-scalar.h"
#include "ov-base-scalar.cc"
#include "ov-re-mat.h"
#include "ov-typeinfo.h"
#include "pr-output.h"
#include "xdiv.h"
#include "xpow.h"

#include "ls-oct-ascii.h"
#include "ls-hdf5.h"

template class octave_base_scalar<double>;

DEFINE_OCTAVE_ALLOCATOR (octave_scalar);

DEFINE_OV_TYPEID_FUNCTIONS_AND_DATA (octave_scalar, "scalar", "double");

octave_value
octave_scalar::do_index_op (const octave_value_list& idx, int resize_ok)
{
  octave_value retval;

  if (idx.valid_scalar_indices ())
    retval = scalar;
  else
    {
      // XXX FIXME XXX -- this doesn't solve the problem of
      //
      //   a = 1; a([1,1], [1,1], [1,1])
      //
      // and similar constructions.  Hmm...

      // XXX FIXME XXX -- using this constructor avoids narrowing the
      // 1x1 matrix back to a scalar value.  Need a better solution
      // to this problem.

      octave_value tmp (new octave_matrix (matrix_value ()));

      retval = tmp.do_index_op (idx, resize_ok);
    }

  return retval;
}

std::streamoff
octave_scalar::streamoff_value (void) const
{
  std::streamoff retval (-1);

  if (D_NINT (scalar) == scalar)
    retval = std::streamoff (static_cast<long> (scalar));
  else
    error ("conversion to streamoff value failed");

  return retval;
}

streamoff_array
octave_scalar::streamoff_array_value (void) const
{
  streamoff_array retval;

  std::streamoff soff = streamoff_value ();

  if (! error_state)
    retval = streamoff_array (dim_vector (1, 1), soff);

  return retval;
}

octave_value
octave_scalar::convert_to_str_internal (bool, bool) const
{
  octave_value retval;

  if (xisnan (scalar))
    ::error ("invalid conversion from NaN to character");
  else
    {
      int ival = NINT (scalar);

      if (ival < 0 || ival > UCHAR_MAX)
	{
	  // XXX FIXME XXX -- is there something better we could do?

	  ival = 0;

	  ::warning ("range error for conversion to character value");
	}

      retval = octave_value (std::string (1, static_cast<char> (ival)));
    }

  return retval;
}

bool 
octave_scalar::save_ascii (std::ostream& os, bool& infnan_warned, 
			   bool strip_nan_and_inf)
{
  double d = double_value ();

  if (strip_nan_and_inf)
    {
      if (xisnan (d))
	{
	  error ("only value to plot is NaN");
	  return false;
	}
      else
	{
	  d = xisinf (d) ? (d > 0 ? OCT_RBV : -OCT_RBV) : d;
	  octave_write_double (os, d);
	  os << "\n";
	}
    }
  else
    {
      if (! infnan_warned && (xisnan (d) || xisinf (d)))
	{
	  warning ("save: Inf or NaN values may not be reloadable");
	  infnan_warned = true;
	}

      octave_write_double (os, d);
      os << "\n";
    }

  return true;
}

bool 
octave_scalar::load_ascii (std::istream& is)
{
  scalar = octave_read_double (is);
  if (!is)
    {
      error ("load: failed to load scalar constant");
      return false;
    }

  return true;
}

bool 
octave_scalar::save_binary (std::ostream& os, bool& /* save_as_floats */)
{
  char tmp = (char) LS_DOUBLE;
  os.write (X_CAST (char *, &tmp), 1);
  double dtmp = double_value ();
  os.write (X_CAST (char *, &dtmp), 8);

  return true;
}

bool 
octave_scalar::load_binary (std::istream& is, bool swap,
			    oct_mach_info::float_format fmt)
{
  char tmp;
  if (! is.read (X_CAST (char *, &tmp), 1))
    return false;

  double dtmp;
  read_doubles (is, &dtmp, X_CAST (save_type, tmp), 1, swap, fmt);
  if (error_state || ! is)
    return false;

  scalar = dtmp;
  return true;
}

#if defined (HAVE_HDF5)
bool
octave_scalar::save_hdf5 (hid_t loc_id, const char *name,
			  bool /* save_as_floats */)
{
  hsize_t dimens[3];
  hid_t space_hid = -1, data_hid = -1;
  bool retval = true;

  space_hid = H5Screate_simple (0, dimens, 0);
  if (space_hid < 0) return false;

  data_hid = H5Dcreate (loc_id, name, H5T_NATIVE_DOUBLE, space_hid, 
			H5P_DEFAULT);
  if (data_hid < 0) 
    {
      H5Sclose (space_hid);
      return false;
    }

  double tmp = double_value ();
  retval = H5Dwrite (data_hid, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL,
		     H5P_DEFAULT, &tmp) >= 0;

  H5Dclose (data_hid);
  H5Sclose (space_hid);

  return retval;
}

bool
octave_scalar::load_hdf5 (hid_t loc_id, const char *name,
			  bool /* have_h5giterate_bug */)
{
  hid_t data_hid = H5Dopen (loc_id, name);
  hid_t space_id = H5Dget_space (data_hid);

  hsize_t rank = H5Sget_simple_extent_ndims (space_id);

  if (rank != 0)
    { 
      H5Dclose (data_hid);
      return false;
    }

  double dtmp;
  if (H5Dread (data_hid, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, 
	       H5P_DEFAULT, &dtmp) < 0)
    { 
      H5Dclose (data_hid);
      return false;
    }

  scalar = dtmp;

  H5Dclose (data_hid);

  return true;
}
#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
