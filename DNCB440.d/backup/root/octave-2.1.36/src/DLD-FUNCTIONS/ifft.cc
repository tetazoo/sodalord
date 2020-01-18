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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "lo-mappers.h"

#include "defun-dld.h"
#include "error.h"
#include "gripes.h"
#include "oct-obj.h"
#include "utils.h"

// This function should be merged with Ffft.

DEFUN_DLD (ifft, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} ifft (@var{a}, @var{n})\n\
Compute the inverse FFT of @var{a} using subroutines from @sc{Fftpack}.  If\n\
@var{a} is a matrix, @code{fft} computes the inverse FFT for each column\n\
of @var{a}.\n\
\n\
If called with two arguments, @var{n} is expected to be an integer\n\
specifying the number of elements of @var{a} to use.  If @var{a} is a\n\
matrix, @var{n} specifies the number of rows of @var{a} to use.  If\n\
@var{n} is larger than the size of @var{a}, @var{a} is resized and\n\
padded with zeros.\n\
@end deftypefn")
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin < 1 || nargin > 2)
    {
      print_usage ("ifft");
      return retval;
    }

  octave_value arg = args(0);
    
  int n_points = arg.rows ();
  if (n_points == 1)
    n_points = arg.columns ();

  if (nargin == 2)
    {
      double dval = args(1).double_value ();
      if (xisnan (dval))
	error ("fft: NaN is invalid as the N_POINTS");
      else
	n_points = NINT (dval);
    }

  if (error_state)
    return retval;

  if (n_points < 0)
    {
      error ("ifft: number of points must be greater than zero");
      return retval;
    }

  int arg_is_empty = empty_arg ("ifft", arg.rows (), arg.columns ());

  if (arg_is_empty < 0)
    return retval;
  else if (arg_is_empty || n_points == 0)
    return Matrix ();

  if (arg.is_real_type ())
    {
      Matrix m = arg.matrix_value ();

      if (! error_state)
	{
	  if (m.rows () == 1)
	    m.resize (1, n_points, 0.0);
	  else
	    m.resize (n_points, m.columns (), 0.0);
	  retval = m.ifourier ();
	}
    }
  else if (arg.is_complex_type ())
    {
      ComplexMatrix m = arg.complex_matrix_value ();

      if (! error_state)
	{
	  if (m.rows () == 1)
	    m.resize (1, n_points, 0.0);
	  else
	    m.resize (n_points, m.columns (), 0.0);
	  retval = m.ifourier ();
	}
    }
  else
    {
      gripe_wrong_type_arg ("ifft", arg);
    }

  return retval;
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
