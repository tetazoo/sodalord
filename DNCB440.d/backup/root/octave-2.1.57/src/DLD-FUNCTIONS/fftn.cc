/*

Copyright (C) 2004 David Bateman

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
do_fftn (const octave_value_list &args, const char *fcn, int type)
{
  octave_value retval;

  int nargin = args.length ();

  if (nargin < 1 || nargin > 2)
    {
      print_usage (fcn);
      return retval;
    }

  octave_value arg = args(0);
  dim_vector dims = arg.dims ();
  
  for (int i = 0; i < dims.length (); i++)
    if (dims(i) < 0)
      return retval;

  if (nargin > 1)
    {
      Matrix val = args(1).matrix_value ();
      if (val.rows () > val.columns ())
	val.transpose ();

      if (val.columns () != dims.length () || val.rows () != 1)
	error ("%s: second argument must be a vector of length dim", fcn);
      else
	{
	  for (int i = 0; i < dims.length (); i++)
	    {
	      if (xisnan (val(i,0)))
		error ("%s: NaN is invalid as a dimension", fcn);
	      else if (NINT (val(i,0)) < 0)
		error ("%s: all dimension must be greater than zero", fcn);
	      else
		{
		  dims(i) = NINT(val(i,0));
		}
	    }
	}
    }

  if (error_state)
    return retval;

  if (dims.all_zero ())
    return octave_value (Matrix ());

  if (arg.is_real_type ())
    {
      NDArray nda = arg.array_value ();

      if (! error_state)
	{
	  nda.resize (dims, 0.0);
	  retval = (type != 0 ? nda.ifourierNd () : nda.fourierNd ());
	}
    }
  else if (arg.is_complex_type ())
    {
      ComplexNDArray cnda = arg.complex_array_value ();

      if (! error_state)
	{
	  cnda.resize (dims, 0.0);
	  retval = (type != 0 ? cnda.ifourierNd () : cnda.fourierNd ());
	}
    }
  else
    {
      gripe_wrong_type_arg (fcn, arg);
    }

  return retval;
}

DEFUN_DLD (fftn, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} fftn (@var{a}, @var{size})\n\
Compute the N dimensional FFT of @var{a} using subroutines from\n"
FFTSRC
". The optional vector argument @var{size} may be used specify the\n\
dimensions of the array to be used. If an element of @var{size} is\n\
smaller than the corresponding dimension, then the dimension is\n\
truncated prior to performing the FFT. Otherwise if an element\n\
of @var{size} is larger than the corresponding dimension @var{a}\n\
is resized and padded with zeros.\n\
@end deftypefn\n\
@seealso {ifftn, fft, fft2, fftw_wisdom}")
{
  return do_fftn (args, "fftn", 0);
}

DEFUN_DLD (ifftn, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} ifftn (@var{a}, @var{size})\n\
Compute the invesre N dimensional FFT of @var{a} using subroutines from\n"
FFTSRC
". The optional vector argument @var{size} may be used specify the\n\
dimensions of the array to be used. If an element of @var{size} is\n\
smaller than the corresponding dimension, then the dimension is\n\
truncated prior to performing the inverse FFT. Otherwise if an element\n\
of @var{size} is larger than the corresponding dimension @var{a}\n\
is resized and padded with zeros.\n\
@end deftypefn\n\
@seealso {fftn, ifft, ifft2, fftw_wisdom}")
{
  return do_fftn (args, "ifftn", 1);
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
