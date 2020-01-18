/*

Copyright (C) 1999 John W. Eaton

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

#include <iostream>

#include "Cell.h"
#include "defun.h"
#include "error.h"
#include "oct-obj.h"
#include "pt-arg-list.h"
#include "pt-bp.h"
#include "pt-exp.h"
#include "pt-cell.h"
#include "pt-walk.h"
#include "utils.h"
#include "ov.h"
#include "variables.h"

octave_value
tree_cell::rvalue (void)
{
  octave_value retval;

  MAYBE_DO_BREAKPOINT;

  int nr = length ();
  int nc = -1;

  Cell val;

  int i = 0;

  for (iterator p = begin (); p != end (); p++)
    {
      tree_argument_list *elt = *p;

      octave_value_list row = elt->convert_to_const_vector ();
      
      if (nc < 0)
	{
	  nc = row.length ();

	  val = Cell (nr, nc);
	}
      else
	{
	  int this_nc = row.length ();

	  if (nc != this_nc)
	    {
	      ::error ("number of columns must match");
	      return retval;
	    }
	}

      for (int j = 0; j < nc; j++)
	val(i,j) = row(j);

      i++;
    }

  retval = val;

  return retval;
}

octave_value_list
tree_cell::rvalue (int nargout)
{
  octave_value_list retval;

  if (nargout > 1)
    error ("invalid number of output arguments for cell array");
  else
    retval = rvalue ();

  return retval;
}

void
tree_cell::accept (tree_walker& tw)
{
  tw.visit_cell (*this);
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
