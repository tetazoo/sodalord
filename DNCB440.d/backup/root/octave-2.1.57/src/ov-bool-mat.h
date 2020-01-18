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

#if !defined (octave_bool_matrix_h)
#define octave_bool_matrix_h 1

#if defined (__GNUG__) && defined (USE_PRAGMA_INTERFACE_IMPLEMENTATION)
#pragma interface
#endif

#include <cstdlib>

#include <iostream>
#include <string>

#include "mx-base.h"
#include "oct-alloc.h"

#include "error.h"
#include "ov-base.h"
#include "ov-base-mat.h"
#include "ov-typeinfo.h"

class Octave_map;
class octave_value_list;

class tree_walker;

// Character matrix values.

class
octave_bool_matrix : public octave_base_matrix<boolNDArray>
{
public:

  octave_bool_matrix (void)
    : octave_base_matrix<boolNDArray> () { }

  octave_bool_matrix (const boolNDArray& bnda)
    : octave_base_matrix<boolNDArray> (bnda) { }

  octave_bool_matrix (const boolMatrix& bm)
    : octave_base_matrix<boolNDArray> (bm) { }

  octave_bool_matrix (const Array2<bool>& a)
    : octave_base_matrix<boolNDArray> (a) { }

  octave_bool_matrix (const octave_bool_matrix& bm)
    : octave_base_matrix<boolNDArray> (bm) { }

  ~octave_bool_matrix (void) { }

  octave_value *clone (void) const { return new octave_bool_matrix (*this); }
  octave_value *empty_clone (void) const { return new octave_bool_matrix (); }

  type_conv_fcn numeric_conversion_function (void) const;

  octave_value *try_narrowing_conversion (void);

  idx_vector index_vector (void) const { return idx_vector (matrix); }

  size_t byte_size (void) const { return numel () * sizeof (bool); }

  bool is_bool_matrix (void) const { return true; }

  bool is_bool_type (void) const { return true; }

  bool is_real_type (void) const { return true; }

  bool valid_as_scalar_index (void) const;

  double double_value (bool = false) const;

  double scalar_value (bool frc_str_conv = false) const
    { return double_value (frc_str_conv); }

  Matrix matrix_value (bool = false) const
    { return Matrix (matrix.matrix_value ()); }

  NDArray array_value (bool = false) const
    { return NDArray (matrix); }

  Complex complex_value (bool = false) const;

  ComplexMatrix complex_matrix_value (bool = false) const
    { return ComplexMatrix (matrix.matrix_value ( )); }

  ComplexNDArray complex_array_value (bool = false) const
    { return ComplexNDArray (matrix.matrix_value ()); }

  boolMatrix bool_matrix_value (void) const
    { return matrix.matrix_value (); }

  boolNDArray bool_array_value (void) const
    { return matrix; }

  octave_value convert_to_str_internal (bool pad, bool force) const;

  void print_raw (std::ostream& os, bool pr_as_read_syntax = false) const;

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

protected:

  DECLARE_OCTAVE_ALLOCATOR

  DECLARE_OV_TYPEID_FUNCTIONS_AND_DATA
};

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
