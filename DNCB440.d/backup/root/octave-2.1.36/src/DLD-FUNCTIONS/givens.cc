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

// Originally written by A. S. Hodel <scotte@eng.auburn.edu>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "defun-dld.h"
#include "error.h"
#include "oct-obj.h"

DEFUN_DLD (givens, args, nargout,
  "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {@var{g} =} givens (@var{x}, @var{y})\n\
@deftypefnx {Loadable Function} {[@var{c}, @var{s}] =} givens (@var{x}, @var{y})\n\
@iftex\n\
@tex\n\
Return a $2\\times 2$ orthogonal matrix\n\
$$\n\
 G = \\left[\\matrix{c & s\\cr -s'& c\\cr}\\right]\n\
$$\n\
such that\n\
$$\n\
 G \\left[\\matrix{x\\cr y}\\right] = \\left[\\matrix{\\ast\\cr 0}\\right]\n\
$$\n\
with $x$ and $y$ scalars.\n\
@end tex\n\
@end iftex\n\
@ifinfo\n\
Return a 2 by 2 orthogonal matrix\n\
@code{@var{g} = [@var{c} @var{s}; -@var{s}' @var{c}]} such that\n\
@code{@var{g} [@var{x}; @var{y}] = [*; 0]} with @var{x} and @var{y} scalars.\n\
@end ifinfo\n\
\n\
For example,\n\
\n\
@example\n\
@group\n\
givens (1, 1)\n\
     @result{}   0.70711   0.70711\n\
         -0.70711   0.70711\n\
@end group\n\
@end example\n\
@end deftypefn")
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin != 2 || nargout > 2)
    {
      print_usage ("givens");
      return retval;
    }
  else
    {
      if (args(0).is_complex_type () || args(1).is_complex_type ())
	{
	  Complex cx = args(0).complex_value ();
	  Complex cy = args(1).complex_value ();

	  if (! error_state)
	    {
	      ComplexMatrix result = Givens (cx, cy);

	      if (! error_state)
		{
		  switch (nargout)
		    {
		    case 0:
		    case 1:
		      retval(0) = result;
		      break;
   
		    case 2:
		      retval(1) = result (0, 1);
		      retval(0) = result (0, 0);
		      break;

		    default:
		      error ("givens: invalid number of output arguments");
		      break;
		    }
		}
	    }
	}
      else
	{
	  double x = args(0).double_value ();
	  double y = args(1).double_value ();

	  if (! error_state)
	    {
	      Matrix result = Givens (x, y);

	      if (! error_state)
		{
		  switch (nargout)
		    {
		    case 0:
		    case 1:
		      retval(0) = result;
		      break;
   
		    case 2:
		      retval(1) = result (0, 1);
		      retval(0) = result (0, 0);
		      break;

		    default:
		      error ("givens: invalid number of output arguments");
		      break;
		    }
		}
	    }
	}
    }

  return retval;
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
