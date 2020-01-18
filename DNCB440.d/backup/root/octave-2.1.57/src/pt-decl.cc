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

#include "defun.h"
#include "error.h"
#include "pt-cmd.h"
#include "ov.h"
#include "oct-lvalue.h"
#include "pt-decl.h"
#include "pt-exp.h"
#include "pt-id.h"
#include "pt-walk.h"
#include "utils.h"
#include "variables.h"

// Declarations (global, static, etc.).

tree_decl_elt::~tree_decl_elt (void)
{
  delete id;
  delete expr;
}

void
tree_decl_elt::accept (tree_walker& tw)
{
  tw.visit_decl_elt (*this);
}

// Initializer lists for declaration statements.

void
tree_decl_init_list::eval (tree_decl_elt::eval_fcn f)
{
  for (iterator p = begin (); p != end (); p++)
    {
      tree_decl_elt *elt = *p;

      f (*elt);

      if (error_state)
	break;
    }
}

void
tree_decl_init_list::accept (tree_walker& tw)
{
  tw.visit_decl_init_list (*this);
}

// Base class for declaration commands (global, static).

tree_decl_command::~tree_decl_command (void)
{
  delete init_list;
}

void
tree_decl_command::accept (tree_walker& tw)
{
  tw.visit_decl_command (*this);
}

// Global.

void
tree_global_command::do_init (tree_decl_elt& elt)
{
  tree_identifier *id = elt.ident ();

  if (id)
    {
      id->link_to_global ();

      if (! error_state)
	{
	  octave_lvalue ult = id->lvalue ();

	  if (ult.is_undefined ())
	    {
	      tree_expression *expr = elt.expression ();

	      octave_value init_val;

	      if (expr)
		init_val = expr->rvalue ();
	      else
		init_val = Matrix ();

	      ult.assign (octave_value::op_asn_eq, init_val);
	    }
	}
    }
}

void
tree_global_command::eval (void)
{
  if (init_list)
    {
      init_list->eval (do_init);

      initialized = true;
    }

  if (error_state)
    ::error ("evaluating global command near line %d, column %d",
	     line (), column ());
}

// Static.

void
tree_static_command::do_init (tree_decl_elt& elt)
{
  tree_identifier *id = elt.ident ();

  if (id)
    {
      id->mark_as_static ();

      tree_expression *expr = elt.expression ();

      if (expr)
	{
	  octave_value init_val = expr->rvalue ();

	  octave_lvalue ult = id->lvalue ();

	  ult.assign (octave_value::op_asn_eq, init_val);
	}
    }
}

void
tree_static_command::eval (void)
{
  // Static variables only need to be marked and initialized once.

  if (init_list && ! initialized)
    {
      init_list->eval (do_init);

      initialized = true;

      if (error_state)
	::error ("evaluating static command near line %d, column %d",
		 line (), column ());
    }
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
