/*

Copyright (C) 2004 David Bateman
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

// This function should be merged with Fifft.

#if defined (HAVE_FFTW3)
#define FFTSRC "@sc{Fftw}"
#else
#define FFTSRC "@sc{Fftpack}"
#endif

static octave_value
do_fft2 (const octave_value_list &args, const char *fcn, int type)
{
  octave_value retval;

  int nargin = args.length ();

  if (nargin < 1 || nargin > 3)
    {
      print_usage (fcn);
      return retval;
    }

  octave_value arg = args(0);
  dim_vector dims = arg.dims ();
  int n_rows = -1;
  
  if (nargin > 1)
    {
      double dval = args(1).double_value ();
      if (xisnan (dval))
	error ("%s: NaN is invalid as the N_ROWS", fcn);
      else
	{
	  n_rows = NINT (dval);
	  if (n_rows < 0)
	    error ("%s: number of rows must be greater than zero", fcn);
	}
    }

  if (error_state)
    return retval;

  int n_cols = -1;
  if (nargin > 2)
    {
      double dval = args(2).double_value ();
      if (xisnan (dval))
	error ("%s: NaN is invalid as the N_COLS", fcn);
      else
	{
	  n_cols = NINT (dval);
	  if (n_cols < 0)
	    error ("%s: number of columns must be greater than zero", fcn);
	}
    }

  if (error_state)
    return retval;

  for (int i = 0; i < dims.length (); i++)
    if (dims(i) < 0)
      return retval;

  if (n_rows < 0)
    n_rows = dims (0);
  else
    dims (0) = n_rows;

  if (n_cols < 0)
    n_cols = dims (1);
  else
    dims (1) = n_cols;

  if (dims.all_zero () || n_rows == 0 || n_cols == 0)
    return octave_value (Matrix ());

  if (arg.is_real_type ())
    {
      NDArray nda = arg.array_value ();

      if (! error_state)
	{
	  nda.resize (dims, 0.0);
	  retval = (type != 0 ? nda.ifourier2d () : nda.fourier2d ());
	}
    }
  else if (arg.is_complex_type ())
    {
      ComplexNDArray cnda = arg.complex_array_value ();

      if (! error_state)
	{
	  cnda.resize (dims, 0.0);
	  retval = (type != 0 ? cnda.ifourier2d () : cnda.fourier2d ());
	}
    }
  else
    {
      gripe_wrong_type_arg (fcn, arg);
    }

  return retval;
}

DEFUN_DLD (fft2, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} fft2 (@var{a}, @var{n}, @var{m})\n\
Compute the two dimensional FFT of @var{a} using subroutines from\n"
FFTSRC
". The optional arguments @var{n} and @var{m} may be used specify the\n\
number of rows and columns of @var{a} to use.  If either of these is\n\
larger than the size of @var{a}, @var{a} is resized and padded with\n\
zeros.\n\
\n\
If @var{a} is a multi-dimensional matrix, each two-dimensional sub-matrix\n\
of @var{a} is treated seperately\n\
@end deftypefn\n\
@seealso {ifft2, fft, fftn fftw_wisdom}")
{
  return do_fft2 (args, "fft2", 0);
}


DEFUN_DLD (ifft2, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} fft2 (@var{a}, @var{n}, @var{m})\n\
Compute the inverse two dimensional FFT of @var{a} using subroutines from\n"
FFTSRC
". The optional arguments @var{n} and @var{m} may be used specify the\n\
number of rows and columns of @var{a} to use.  If either of these is\n\
larger than the size of @var{a}, @var{a} is resized and padded with\n\
zeros.\n\
\n\
If @var{a} is a multi-dimensional matrix, each two-dimensional sub-matrix\n\
of @var{a} is treated seperately\n\
@end deftypefn\n\
@seealso {fft2, ifft, ifftn, fftw_wisdom}")
{
  return do_fft2 (args, "ifft2", 1);
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
