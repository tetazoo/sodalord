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

#if !defined (octave_range_h)
#define octave_range_h 1

#if defined (__GNUG__)
#pragma interface
#endif

#include <cstdlib>

#include <iostream>
#include <string>

#include "Range.h"

#include "lo-mappers.h"
#include "lo-utils.h"
#include "mx-base.h"
#include "oct-alloc.h"
#include "str-vec.h"

#include "error.h"
#include "ov-base.h"
#include "ov-typeinfo.h"

class Octave_map;
class octave_value_list;

class tree_walker;

// Range values.

class
octave_range : public octave_base_value
{
public:

  octave_range (void)
    : octave_base_value () { }

  octave_range (double base, double limit, double inc)
    : octave_base_value (), range (base, limit, inc)
      {
	if (range.nelem () < 0)
	  ::error ("invalid range");
      }

  octave_range (const Range& r)
    : octave_base_value (), range (r)
      {
	if (range.nelem () < 0)
	  ::error ("invalid range");
      }

  octave_range (const octave_range& r)
    : octave_base_value (), range (r.range) { }

  ~octave_range (void) { }

  octave_value *clone (void) { return new octave_range (*this); }

  type_conv_fcn numeric_conversion_function (void) const;

  octave_value *try_narrowing_conversion (void);

  octave_value do_index_op (const octave_value_list& idx);

  idx_vector index_vector (void) const { return idx_vector (range); }

  int rows (void) const { return (columns () > 0); }
  int columns (void) const { return range.nelem (); }

  int length (void) const { return range.nelem (); }

  bool is_defined (void) const { return true; }

  bool is_constant (void) const { return true; }

  bool is_range (void) const { return true; }

  // XXX DO ME XXX
  octave_value all (void) const;
  octave_value any (void) const;

  bool is_real_type (void) const { return true; }

  bool valid_as_scalar_index (void) const
    {
      return (range.nelem () == 1
	      && ! xisnan (range.base ())
	      && NINT (range.base ()) == 1);
    }

  bool valid_as_zero_index (void) const
    {
      return (range.nelem () == 1
	      && ! xisnan (range.base ())
	      && NINT (range.base ()) == 0);
    }

  bool is_numeric_type (void) const { return true; }

  // XXX DO ME XXX
  bool is_true (void) const;

  double double_value (bool = false) const;

  double scalar_value (bool frc_str_conv = false) const
    { return double_value (frc_str_conv); }

  Matrix matrix_value (bool = false) const
    { return range.matrix_value (); }

  Complex complex_value (bool = false) const;

  ComplexMatrix complex_matrix_value (bool = false) const
    { return ComplexMatrix (range.matrix_value ()); }

  Range range_value (void) const { return range; }

  octave_value convert_to_str (void) const;

  void print (std::ostream& os, bool pr_as_read_syntax = false) const;

  void print_raw (std::ostream& os, bool pr_as_read_syntax = false) const;

  bool print_name_tag (std::ostream& os, const std::string& name) const;

private:

  Range range;

  DECLARE_OV_TYPEID_FUNCTIONS_AND_DATA

  DECLARE_OCTAVE_ALLOCATOR
};

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
