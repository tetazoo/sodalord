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

#if !defined (octave_list_h)
#define octave_list_h 1

#if defined (__GNUG__)
#pragma interface
#endif

#include <cstdlib>

#include <iostream>
#include <string>

#include "mx-base.h"
#include "str-vec.h"

#include "error.h"
#include "oct-alloc.h"
#include "oct-obj.h"
#include "ov-base.h"
#include "ov-typeinfo.h"

class tree_walker;

// Lists.

class
octave_list : public octave_base_value
{
public:

  octave_list (void)
    : octave_base_value () { }

  octave_list (const octave_value_list& l)
    : octave_base_value (), lst (l) { }

  octave_list (const octave_list& l)
    : octave_base_value (), lst (l.lst) { }

  ~octave_list (void) { }

  octave_value *clone (void) { return new octave_list (*this); }

  octave_value do_index_op (const octave_value_list& idx);

  void assign (const octave_value_list& idx, const octave_value& rhs);

  int length (void) const { return lst.length (); }

  bool is_defined (void) const { return true; }

  bool is_constant (void) const { return true; }

  bool is_list (void) const { return true; }

  octave_value_list list_value (void) const { return lst; }

  void print (std::ostream& os, bool pr_as_read_syntax = false) const;

  void print_raw (std::ostream& os, bool pr_as_read_syntax = false) const;

  bool print_name_tag (std::ostream& os, const std::string& name) const;

private:

  // The list of Octave values.
  octave_value_list lst;

  DECLARE_OV_TYPEID_FUNCTIONS_AND_DATA

  DECLARE_OCTAVE_ALLOCATOR
};

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
