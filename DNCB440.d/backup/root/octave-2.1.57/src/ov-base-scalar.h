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

#if !defined (octave_base_scalar_h)
#define octave_base_scalar_h 1

#if defined (__GNUG__) && defined (USE_PRAGMA_INTERFACE_IMPLEMENTATION)
#pragma interface
#endif

#include <cstdlib>

#include <iostream>
#include <string>

#include "lo-mappers.h"
#include "lo-utils.h"
#include "oct-alloc.h"
#include "str-vec.h"

#include "ov-base.h"
#include "ov-typeinfo.h"

// Real scalar values.

template <class ST>
class
octave_base_scalar : public octave_base_value
{
public:

  octave_base_scalar (void)
    : octave_base_value () { }

  octave_base_scalar (const ST& s)
    : octave_base_value (), scalar (s) { }

  octave_base_scalar (const octave_base_scalar& s)
    : octave_base_value (), scalar (s.scalar) { }

  ~octave_base_scalar (void) { }

  octave_value squeeze (void) const { return scalar; }

  octave_value subsref (const std::string& type,
			const std::list<octave_value_list>& idx);

  octave_value_list subsref (const std::string&,
			     const std::list<octave_value_list>&, int)
    {
      panic_impossible ();
      return octave_value_list ();
    }

  octave_value subsasgn (const std::string& type,
			 const std::list<octave_value_list>& idx,
			 const octave_value& rhs);

  bool is_constant (void) const { return true; }

  bool is_defined (void) const { return true; }

  dim_vector dims (void) const { static dim_vector dv (1, 1); return dv; }

  size_t byte_size (void) const { return sizeof (ST); }

  octave_value all (int = 0) const { return (scalar != 0.0); }

  octave_value any (int = 0) const { return (scalar != 0.0); }

  bool is_scalar_type (void) const { return true; }

  bool is_numeric_type (void) const { return true; }

  bool is_true (void) const { return (scalar != 0.0); }

  void print (std::ostream& os, bool pr_as_read_syntax = false) const;

  void print_raw (std::ostream& os, bool pr_as_read_syntax = false) const;

  bool print_name_tag (std::ostream& os, const std::string& name) const;

protected:

  // The value of this scalar.
  ST scalar;
};

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
