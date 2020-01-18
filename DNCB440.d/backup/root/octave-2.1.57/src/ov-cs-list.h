/*

Copyright (C) 2002 John W. Eaton

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

#if !defined (octave_cs_list_h)
#define octave_cs_list_h 1

#if defined (__GNUG__) && defined (USE_PRAGMA_INTERFACE_IMPLEMENTATION)
#pragma interface
#endif

#include <cstdlib>

#include <iostream>
#include <string>

#include "mx-base.h"
#include "str-vec.h"

#include "Cell.h"
#include "error.h"
#include "oct-alloc.h"
#include "oct-obj.h"
#include "ov-list.h"
#include "ov-typeinfo.h"

class tree_walker;

// Lists.

class
octave_cs_list : public octave_base_value
{
public:

  octave_cs_list (void)
    : octave_base_value (), lst () { }

  octave_cs_list (const octave_value_list& l)
    : octave_base_value (), lst (l) { }

  octave_cs_list (const Cell& c);

  octave_cs_list (const octave_cs_list& l)
    : octave_base_value (), lst (l) { }

  ~octave_cs_list (void) { }

  octave_value *clone (void) const { return new octave_cs_list (*this); }
  octave_value *empty_clone (void) const { return new octave_cs_list (); }

  dim_vector dims (void) const { return dim_vector (1, lst.length ()); }

  bool is_defined (void) const { return true; }

  bool is_constant (void) const { return true; }

  bool is_cs_list (void) const { return true; }

  octave_value_list list_value (void) const { return lst; }

  void print (std::ostream& os, bool) const;

  void print_raw (std::ostream& os, bool pr_as_read_syntax = false) const;

private:

  // The list of Octave values.
  octave_value_list lst;

  DECLARE_OCTAVE_ALLOCATOR

  DECLARE_OV_TYPEID_FUNCTIONS_AND_DATA
};

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
