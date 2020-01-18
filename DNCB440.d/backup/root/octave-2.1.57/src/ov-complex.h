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

#if !defined (octave_complex_h)
#define octave_complex_h 1

#if defined (__GNUG__) && defined (USE_PRAGMA_INTERFACE_IMPLEMENTATION)
#pragma interface
#endif

#include <cstdlib>

#include <iostream>
#include <string>

#include "mx-base.h"
#include "oct-alloc.h"
#include "str-vec.h"

#include "error.h"
#include "ov-base.h"
#include "ov-cx-mat.h"
#include "ov-base-scalar.h"
#include "ov-typeinfo.h"

class Octave_map;
class octave_value_list;

class tree_walker;

// Complex scalar values.

class
octave_complex : public octave_base_scalar<Complex>
{
public:

  octave_complex (void)
    : octave_base_scalar<Complex> () { }

  octave_complex (const Complex& c)
    : octave_base_scalar<Complex> (c) { }

  octave_complex (const octave_complex& c)
    : octave_base_scalar<Complex> (c) { }

  ~octave_complex (void) { }

  octave_value *clone (void) const { return new octave_complex (*this); }

  // We return an octave_complex_matrix object here instead of an
  // octave_complex object so that in expressions like A(2,2,2) = 2
  // (for A previously undefined), A will be empty instead of a 1x1
  // object.
  octave_value *empty_clone (void) const
    { return new octave_complex_matrix (); }

  octave_value *try_narrowing_conversion (void);

  octave_value do_index_op (const octave_value_list& idx, int resize_ok);

  bool is_complex_scalar (void) const { return true; }

  bool is_complex_type (void) const { return true; }

  // XXX FIXME XXX ???
  bool valid_as_scalar_index (void) const { return false; }
  bool valid_as_zero_index (void) const { return false; }

  double double_value (bool = false) const;

  double scalar_value (bool frc_str_conv = false) const
    { return double_value (frc_str_conv); }

  Matrix matrix_value (bool = false) const;

  NDArray array_value (bool = false) const;

  Complex complex_value (bool = false) const;

  ComplexMatrix complex_matrix_value (bool = false) const;

  ComplexNDArray complex_array_value (bool = false) const;

  void increment (void) { scalar += 1.0; }

  void decrement (void) { scalar -= 1.0; }

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
