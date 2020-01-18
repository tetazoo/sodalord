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

#if !defined (octave_tree_unop_h)
#define octave_tree_unop_h 1

#if defined (__GNUG__) && defined (USE_PRAGMA_INTERFACE_IMPLEMENTATION)
#pragma interface
#endif

#include <string>

class tree_walker;

class octave_value;
class octave_value_list;
class octave_lvalue;

#include "pt-exp.h"

// Unary expressions.

class
tree_unary_expression : public tree_expression
{
public:

  tree_unary_expression (int l = -1, int c = -1,
			 octave_value::unary_op t
			   = octave_value::unknown_unary_op)
    : tree_expression (l, c), op (0), etype (t)  { }

  tree_unary_expression (tree_expression *e, int l = -1, int c = -1,
			 octave_value::unary_op t
			   = octave_value::unknown_unary_op)
    : tree_expression (l, c), op (e), etype (t) { }

  ~tree_unary_expression (void) { delete op; }

  bool has_magic_end (void) const { return (op && op->has_magic_end ()); }

  tree_expression *operand (void) { return op; }

  std::string oper (void) const;

protected:

  // The operand for the expression.
  tree_expression *op;

  // The type of the expression.
  octave_value::unary_op etype;

private:

  // No copying!

  tree_unary_expression (const tree_unary_expression&);

  tree_unary_expression& operator = (const tree_unary_expression&);
};

// Prefix expressions.

class
tree_prefix_expression : public tree_unary_expression
{
public:

  tree_prefix_expression (int l = -1, int c = -1)
    : tree_unary_expression (l, c, octave_value::unknown_unary_op) { }

  tree_prefix_expression (tree_expression *e, int l = -1, int c = -1,
			  octave_value::unary_op t
			    = octave_value::unknown_unary_op)
    : tree_unary_expression (e, l, c, t) { }

  ~tree_prefix_expression (void) { }

  bool rvalue_ok (void) const { return true; }

  octave_value rvalue (void);

  octave_value_list rvalue (int nargout);

  void eval_error (void);

  void accept (tree_walker& tw);

private:

  // No copying!

  tree_prefix_expression (const tree_prefix_expression&);

  tree_prefix_expression& operator = (const tree_prefix_expression&);
};

// Postfix expressions.

class
tree_postfix_expression : public tree_unary_expression
{
public:

  tree_postfix_expression (int l = -1, int c = -1)
    : tree_unary_expression (l, c, octave_value::unknown_unary_op) { }

  tree_postfix_expression (tree_expression *e, int l = -1, int c = -1,
			   octave_value::unary_op t
			     = octave_value::unknown_unary_op)
    : tree_unary_expression (e, l, c, t) { }

  ~tree_postfix_expression (void) { }

  bool rvalue_ok (void) const { return true; }

  octave_value rvalue (void);

  octave_value_list rvalue (int nargout);

  void eval_error (void);

  void accept (tree_walker& tw);

private:

  // No copying!

  tree_postfix_expression (const tree_postfix_expression&);

  tree_postfix_expression& operator = (const tree_postfix_expression&);
};

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
