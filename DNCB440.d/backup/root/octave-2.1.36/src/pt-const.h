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

#if !defined (octave_tree_const_h)
#define octave_tree_const_h 1

#if defined (__GNUG__)
#pragma interface
#endif

#include <iostream>
#include <string>

#include "oct-alloc.h"

#include "pt-bp.h"
#include "pt-exp.h"

class octave_value_list;

class tree_walker;

#include "ov.h"

class
tree_constant : public tree_expression
{
public:

  tree_constant (int l = -1, int c = -1)
    : tree_expression (l, c), val (), orig_text () { }

  tree_constant (const octave_value& v, int l = -1, int c = -1)
    : tree_expression (l, c), val (v), orig_text () { }

  ~tree_constant (void) { }

  void *operator new (size_t size)
    { return allocator.alloc (size); }

  void operator delete (void *p, size_t size)
    { allocator.free (p, size); }

  // Type.  It would be nice to eliminate the need for this.

  bool is_constant (void) const
    { return true; }

  void maybe_mutate (void)
    { val.maybe_mutate (); }

  void print (std::ostream& os, bool pr_as_read_syntax = false,
	      bool pr_orig_txt = true);

  void print_raw (std::ostream& os, bool pr_as_read_syntax = false,
		  bool pr_orig_txt = true);

  bool rvalue_ok (void) const
    { return true; }

  octave_value rvalue (void)
    {
      MAYBE_DO_BREAKPOINT;
      return val;
    }

  octave_value_list rvalue (int nargout);

  void accept (tree_walker& tw);

  // Store the original text corresponding to this constant for later
  // pretty printing.

  void stash_original_text (const std::string& s)
    { orig_text = s; }

  std::string original_text (void) const
    { return orig_text; }

private:

  // For custom memory management.
  static octave_allocator allocator;

  // The actual value that this constant refers to.
  octave_value val;

  // The original text form of this constant.
  std::string orig_text;

  // No copying!

  tree_constant (const tree_constant&);

  tree_constant& operator = (const tree_constant&);
};

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
