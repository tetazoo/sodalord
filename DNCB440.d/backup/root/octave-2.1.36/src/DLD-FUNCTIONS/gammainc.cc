/*

Copyright (C) 1997 John W. Eaton

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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "lo-specfun.h"

#include "defun-dld.h"
#include "error.h"
#include "gripes.h"
#include "oct-obj.h"
#include "utils.h"

DEFUN_DLD (gammainc, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} gammainc (@var{x}, @var{a})\n\
Computes the incomplete gamma function,\n\
@iftex\n\
@tex\n\
$$\n\
 \\gamma (x, a) = {\\displaystyle\\int_0^x e^{-t} t^{a-1} dt \\over \\Gamma (a)}\n\
$$\n\
@end tex\n\
@end iftex\n\
@ifinfo\n\
\n\
@smallexample\n\
                                x\n\
                      1        /\n\
gammainc (x, a) = ---------    | exp (-t) t^(a-1) dt\n\
                  gamma (a)    /\n\
                            t=0\n\
@end smallexample\n\
@end ifinfo\n\
\n\
If @var{a} is scalar, then @code{gammainc (@var{x}, @var{a})} is returned\n\
for each element of @var{x} and vice versa.\n\
\n\
If neither @var{x} nor @var{a} is scalar, the sizes of @var{x} and\n\
@var{a} must agree, and @var{gammainc} is applied element-by-element.\n\
@end deftypefn\n\
@seealso{gamma and lgamma}")
{
  octave_value retval;

  int nargin = args.length ();

  if (nargin == 2)
    {
      octave_value x_arg = args(0);
      octave_value a_arg = args(1);

      if (x_arg.is_scalar_type ())
	{
	  double x = x_arg.double_value ();

	  if (! error_state)
	    {
	      if (a_arg.is_scalar_type ())
		{
		  double a = a_arg.double_value ();

		  if (! error_state)
		    retval = gammainc (x, a);
		}
	      else
		{
		  Matrix a = a_arg.matrix_value ();

		  if (! error_state)
		    retval = gammainc (x, a);
		}
	    }
	}
      else
	{
	  Matrix x = x_arg.matrix_value ();

	  if (! error_state)
	    {
	      if (a_arg.is_scalar_type ())
		{
		  double a = a_arg.double_value ();

		  if (! error_state)
		    retval = gammainc (x, a);
		}
	      else
		{
		  Matrix a = a_arg.matrix_value ();

		  if (! error_state)
		    retval = gammainc (x, a);
		}
	    }
	}
    }
  else
    print_usage ("gammainc");

  return retval;
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/

