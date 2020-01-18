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

#if !defined (octave_scalar_h)
#define octave_scalar_h 1

#if defined (__GNUG__) && defined (USE_PRAGMA_INTERFACE_IMPLEMENTATION)
#pragma interface
#endif

#include <cstdlib>

#include <iostream>
#include <string>

#include "lo-mappers.h"
#include "lo-utils.h"
#include "mx-base.h"
#include "oct-alloc.h"
#include "str-vec.h"

#include "ov-base.h"
#include "ov-re-mat.h"
#include "ov-base-scalar.h"
#include "ov-typeinfo.h"

class Octave_map;
class octave_value_list;

class tree_walker;

// Real scalar values.

class
octave_scalar : public octave_base_scalar<double>
{
public:

  octave_scalar (void)
    : octave_base_scalar<double> (0.0) { }

  octave_scalar (double d)
    : octave_base_scalar<double> (d) { }

  octave_scalar (const octave_scalar& s)
    : octave_base_scalar<double> (s) { }

  ~octave_scalar (void) { }

  octave_value *clone (void) const { return new octave_scalar (*this); }

  // We return an octave_matrix here instead of an octave_scalar so
  // that in expressions like A(2,2,2) = 2 (for A previously
  // undefined), A will be empty instead of a 1x1 object.
  octave_value *empty_clone (void) const { return new octave_matrix (); }

  octave_value do_index_op (const octave_value_list& idx, int resize_ok);

  idx_vector index_vector (void) const { return idx_vector (scalar); }

  bool is_real_scalar (void) const { return true; }

  bool is_real_type (void) const { return true; }

  bool valid_as_scalar_index (void) const
    { return (! xisnan (scalar) && NINT (scalar) == 1); }

  bool valid_as_zero_index (void) const
    { return (! xisnan (scalar) && NINT (scalar) == 0); }

  double double_value (bool = false) const { return scalar; }

  double scalar_value (bool = false) const { return scalar; }

  Matrix matrix_value (bool = false) const
    { return Matrix (1, 1, scalar); }

  NDArray array_value (bool = false) const
    { return NDArray (dim_vector (1, 1), scalar); }

  Complex complex_value (bool = false) const { return scalar; }

  ComplexMatrix complex_matrix_value (bool = false) const
    { return  ComplexMatrix (1, 1, Complex (scalar)); }

  ComplexNDArray complex_array_value (bool = false) const
    { return ComplexNDArray (dim_vector (1, 1), Complex (scalar)); }

  std::streamoff streamoff_value (void) const;

  streamoff_array streamoff_array_value (void) const;

  octave_value convert_to_str_internal (bool pad, bool force) const;

  void increment (void) { ++scalar; }

  void decrement (void) { --scalar; }

  bool save_ascii (std::ostream& os, bool& infnan_warned,
		 bool strip_nan_and_inf);

  bool load_ascii (std::istream& is);

  bool save_binary (std::ostream& os, bool& save_as_floats);

  bool load_binary (std::istream& is, bool swap, 
		    oct_mach_info::float_format fmt);

#if defined (HAVE_HDF5)
  bool save_hdf5 (hid_t loc_id, const char *name, bool save_as_floats);

  bool load_hdf5 (hid_t loc_id, const char *name, bool have_h5giterate_bug);
#endif

private:

  DECLARE_OCTAVE_ALLOCATOR

  DECLARE_OV_TYPEID_FUNCTIONS_AND_DATA
};

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
