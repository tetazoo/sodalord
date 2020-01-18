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

#include <cmath>

#include "lo-ieee.h"
#include "lo-mappers.h"

#include "defun-dld.h"
#include "error.h"
#include "gripes.h"
#include "oct-obj.h"

// XXX FIXME XXX -- it would be nice to share code among the min/max
// functions below.

#define EMPTY_RETURN_CHECK(T) \
  if (nr == 0 || nc == 0) \
    return T (nr, nc);

static Matrix
min (double d, const Matrix& m)
{
  int nr = m.rows ();
  int nc = m.columns ();

  EMPTY_RETURN_CHECK (Matrix);

  Matrix result (nr, nc);

  for (int j = 0; j < nc; j++)
    for (int i = 0; i < nr; i++)
      result (i, j) = xmin (d, m (i, j));

  return result;
}

static Matrix
min (const Matrix& m, double d)
{
  int nr = m.rows ();
  int nc = m.columns ();

  EMPTY_RETURN_CHECK (Matrix);

  Matrix result (nr, nc);

  for (int j = 0; j < nc; j++)
    for (int i = 0; i < nr; i++)
      result (i, j) = xmin (m (i, j), d);

  return result;
}

static ComplexMatrix
min (const Complex& c, const ComplexMatrix& m)
{
  int nr = m.rows ();
  int nc = m.columns ();

  EMPTY_RETURN_CHECK (ComplexMatrix);

  ComplexMatrix result (nr, nc);

  for (int j = 0; j < nc; j++)
    for (int i = 0; i < nr; i++)
      result (i, j) = xmin (c, m (i, j));

  return result;
}

static ComplexMatrix
min (const ComplexMatrix& m, const Complex& c)
{
  int nr = m.rows ();
  int nc = m.columns ();

  EMPTY_RETURN_CHECK (ComplexMatrix);

  ComplexMatrix result (nr, nc);

  for (int j = 0; j < nc; j++)
    for (int i = 0; i < nr; i++)
      result (i, j) = xmin (m (i, j), c);

  return result;
}

static Matrix
min (const Matrix& a, const Matrix& b)
{
  int nr = a.rows ();
  int nc = a.columns ();

  if (nr != b.rows () || nc != b.columns ())
    {
      error ("two-arg min expecting args of same size");
      return Matrix ();
    }

  EMPTY_RETURN_CHECK (Matrix);

  Matrix result (nr, nc);

  for (int j = 0; j < nc; j++)
    for (int i = 0; i < nr; i++)
      result (i, j) = xmin (a (i, j), b (i, j));

  return result;
}

static ComplexMatrix
min (const ComplexMatrix& a, const ComplexMatrix& b)
{
  int nr = a.rows ();
  int nc = a.columns ();

  if (nr != b.rows () || nc != b.columns ())
    {
      error ("two-arg min expecting args of same size");
      return ComplexMatrix ();
    }

  EMPTY_RETURN_CHECK (ComplexMatrix);

  ComplexMatrix result (nr, nc);

  for (int j = 0; j < nc; j++)
    {
      int columns_are_real_only = 1;
      for (int i = 0; i < nr; i++)
	if (imag (a (i, j)) != 0.0 || imag (b (i, j)) != 0.0)
	  {
	    columns_are_real_only = 0;
	    break;
	  }

      if (columns_are_real_only)
	{
	  for (int i = 0; i < nr; i++)
	    result (i, j) = xmin (real (a (i, j)), real (b (i, j)));
	}
      else
	{
	  for (int i = 0; i < nr; i++)
	    result (i, j) = xmin (a (i, j), b (i, j));
	}
    }

  return result;
}

static Matrix
max (double d, const Matrix& m)
{
  int nr = m.rows ();
  int nc = m.columns ();

  EMPTY_RETURN_CHECK (Matrix);

  Matrix result (nr, nc);

  for (int j = 0; j < nc; j++)
    for (int i = 0; i < nr; i++)
      result (i, j) = xmax (d, m (i, j));

  return result;
}

static Matrix
max (const Matrix& m, double d)
{
  int nr = m.rows ();
  int nc = m.columns ();

  EMPTY_RETURN_CHECK (Matrix);

  Matrix result (nr, nc);

  for (int j = 0; j < nc; j++)
    for (int i = 0; i < nr; i++)
      result (i, j) = xmax (m (i, j), d);

  return result;
}

static ComplexMatrix
max (const Complex& c, const ComplexMatrix& m)
{
  int nr = m.rows ();
  int nc = m.columns ();

  EMPTY_RETURN_CHECK (ComplexMatrix);

  ComplexMatrix result (nr, nc);

  for (int j = 0; j < nc; j++)
    for (int i = 0; i < nr; i++)
      result (i, j) = xmax (c, m (i, j));

  return result;
}

static ComplexMatrix
max (const ComplexMatrix& m, const Complex& c)
{
  int nr = m.rows ();
  int nc = m.columns ();

  EMPTY_RETURN_CHECK (ComplexMatrix);

  ComplexMatrix result (nr, nc);

  for (int j = 0; j < nc; j++)
    for (int i = 0; i < nr; i++)
      result (i, j) = xmax (m (i, j), c);

  return result;
}

static Matrix
max (const Matrix& a, const Matrix& b)
{
  int nr = a.rows ();
  int nc = a.columns ();

  if (nr != b.rows () || nc != b.columns ())
    {
      error ("two-arg max expecting args of same size");
      return Matrix ();
    }

  EMPTY_RETURN_CHECK (Matrix);

  Matrix result (nr, nc);

  for (int j = 0; j < nc; j++)
    for (int i = 0; i < nr; i++)
      result (i, j) = xmax (a (i, j), b (i, j));

  return result;
}

static ComplexMatrix
max (const ComplexMatrix& a, const ComplexMatrix& b)
{
  int nr = a.rows ();
  int nc = a.columns ();

  if (nr != b.rows () || nc != b.columns ())
    {
      error ("two-arg max expecting args of same size");
      return ComplexMatrix ();
    }

  EMPTY_RETURN_CHECK (ComplexMatrix);

  ComplexMatrix result (nr, nc);

  for (int j = 0; j < nc; j++)
    {
      int columns_are_real_only = 1;
      for (int i = 0; i < nr; i++)
	if (imag (a (i, j)) != 0.0 || imag (b (i, j)) != 0.0)
	  {
	    columns_are_real_only = 0;
	    break;
	  }

      if (columns_are_real_only)
	{
	  for (int i = 0; i < nr; i++)
	    result (i, j) = xmax (real (a (i, j)), real (b (i, j)));
	}
      else
	{
	  for (int i = 0; i < nr; i++)
	    result (i, j) = xmax (a (i, j), b (i, j));
	}
    }

  return result;
}

#define MINMAX_BODY(FCN) \
 \
  octave_value_list retval;  \
 \
  int nargin = args.length (); \
 \
  if (nargin < 1 || nargin > 2 || nargout > 2) \
    { \
      print_usage (#FCN); \
      return retval; \
    } \
 \
  octave_value arg1; \
  octave_value arg2; \
 \
  switch (nargin) \
    { \
    case 2: \
      arg2 = args(1); \
 \
    case 1: \
      arg1 = args(0); \
      break; \
 \
    default: \
      panic_impossible (); \
      break; \
    } \
 \
  if (nargin == 1 && (nargout == 1 || nargout == 0)) \
    { \
      if (arg1.is_real_type ()) \
	{ \
	  Matrix m = arg1.matrix_value (); \
 \
	  if (! error_state) \
	    { \
	      if (m.rows () == 1) \
		retval(0) = m.row_ ## FCN (); \
	      else \
		{ \
		  if (m.rows () == 0 || m.columns () == 0) \
		    retval(0) = Matrix (); \
		  else \
		    retval(0) = m.column_ ## FCN (); \
		} \
	    } \
	} \
      else if (arg1.is_complex_type ()) \
	{ \
	  ComplexMatrix m = arg1.complex_matrix_value (); \
 \
	  if (! error_state) \
	    { \
	      if (m.rows () == 1) \
		retval(0) = m.row_ ## FCN (); \
	      else \
		{ \
		  if (m.rows () == 0 || m.columns () == 0) \
		    retval(0) = Matrix (); \
		  else \
		    retval(0) = m.column_ ## FCN (); \
		} \
	    } \
	} \
      else \
	gripe_wrong_type_arg (#FCN, arg1); \
    } \
  else if (nargin == 1 && nargout == 2) \
    { \
      Array<int> index; \
 \
      if (arg1.is_real_type ()) \
	{ \
	  Matrix m = arg1.matrix_value (); \
 \
	  if (! error_state) \
	    { \
	      retval.resize (2); \
 \
	      if (m.rows () == 1) \
		retval(0) = m.row_ ## FCN (index); \
	      else \
		{ \
		  if (m.rows () == 0 || m.columns () == 0) \
		    retval(0) = Matrix (); \
		  else \
		    retval(0) = m.column_ ## FCN (index); \
		} \
	    } \
	} \
      else if (arg1.is_complex_type ()) \
	{ \
	  ComplexMatrix m = arg1.complex_matrix_value (); \
 \
	  if (! error_state) \
	    { \
	      retval.resize (2); \
 \
	      if (m.rows () == 1) \
		retval(0) = m.row_ ## FCN (index); \
	      else \
		{ \
		  if (m.rows () == 0 || m.columns () == 0) \
		    retval(0) = Matrix (); \
		  else \
		    retval(0) = m.column_ ## FCN (index); \
		} \
	    } \
	} \
      else \
	gripe_wrong_type_arg (#FCN, arg1); \
 \
      int len = index.length (); \
 \
      if (len > 0) \
	{ \
	  RowVector idx (len); \
 \
	  for (int i = 0; i < len; i++) \
	    { \
	      int tmp = index.elem (i) + 1; \
	      idx.elem (i) = (tmp <= 0) \
		? octave_NaN : static_cast<double> (tmp); \
	    } \
 \
	  retval(1) = idx; \
	} \
      else \
	retval(1) = Matrix (); \
    } \
  else if (nargin == 2) \
    { \
      int arg1_is_scalar = arg1.is_scalar_type (); \
      int arg2_is_scalar = arg2.is_scalar_type (); \
 \
      int arg1_is_complex = arg1.is_complex_type (); \
      int arg2_is_complex = arg2.is_complex_type (); \
 \
      if (arg1_is_scalar) \
	{ \
	  if (arg1_is_complex || arg2_is_complex) \
	    { \
	      Complex c1 = arg1.complex_value (); \
	      ComplexMatrix m2 = arg2.complex_matrix_value (); \
	      if (! error_state) \
		{ \
		  ComplexMatrix result = FCN (c1, m2); \
		  if (! error_state) \
		    retval(0) = result; \
		} \
	    } \
	  else \
	    { \
	      double d1 = arg1.double_value (); \
	      Matrix m2 = arg2.matrix_value (); \
 \
	      if (! error_state) \
		{ \
		  Matrix result = FCN (d1, m2); \
		  if (! error_state) \
		    retval(0) = result; \
		} \
	    } \
	} \
      else if (arg2_is_scalar) \
	{ \
	  if (arg1_is_complex || arg2_is_complex) \
	    { \
	      ComplexMatrix m1 = arg1.complex_matrix_value (); \
 \
	      if (! error_state) \
		{ \
		  Complex c2 = arg2.complex_value (); \
		  ComplexMatrix result = FCN (m1, c2); \
		  if (! error_state) \
		    retval(0) = result; \
		} \
	    } \
	  else \
	    { \
	      Matrix m1 = arg1.matrix_value (); \
 \
	      if (! error_state) \
		{ \
		  double d2 = arg2.double_value (); \
		  Matrix result = FCN (m1, d2); \
		  if (! error_state) \
		    retval(0) = result; \
		} \
	    } \
	} \
      else \
	{ \
	  if (arg1_is_complex || arg2_is_complex) \
	    { \
	      ComplexMatrix m1 = arg1.complex_matrix_value (); \
 \
	      if (! error_state) \
		{ \
		  ComplexMatrix m2 = arg2.complex_matrix_value (); \
 \
		  if (! error_state) \
		    { \
		      ComplexMatrix result = FCN (m1, m2); \
		      if (! error_state) \
			retval(0) = result; \
		    } \
		} \
	    } \
	  else \
	    { \
	      Matrix m1 = arg1.matrix_value (); \
 \
	      if (! error_state) \
		{ \
		  Matrix m2 = arg2.matrix_value (); \
 \
		  if (! error_state) \
		    { \
		      Matrix result = FCN (m1, m2); \
		      if (! error_state) \
			retval(0) = result; \
		    } \
		} \
	    } \
	} \
    } \
  else \
    panic_impossible (); \
 \
  return retval

DEFUN_DLD (min, args, nargout,
  "-*- texinfo -*-\n\
For a vector argument, return the minimum value.  For a matrix\n\
argument, return the minimum value from each column, as a row\n\
vector.  Thus,\n\
\n\
@example\n\
min (min (@var{x}))\n\
@end example\n\
\n\
@noindent\n\
returns the smallest element of @var{x}.\n\
\n\
For complex arguments, the magnitude of the elements are used for\n\
comparison.\n\
\n\
If called with two output arguments, also returns the index of the\n\
minimum value(s). Thus,\n\
@example\n\
[x, ix] = min ([1, 3, 0, 2, 5])\n\
@end example\n\
\n\
@noindent\n\
returns @var{x} = 0 and @var{ix} = 3.")
{
  MINMAX_BODY (min);
}

DEFUN_DLD (max, args, nargout,
  "-*- texinfo -*-\n\
For a vector argument, return the maximum value.  For a matrix\n\
argument, return the maximum value from each column, as a row\n\
vector.  Thus,\n\
\n\
@example\n\
max (max (@var{x}))\n\
@end example\n\
\n\
@noindent\n\
returns the largest element of @var{x}.\n\
\n\
For complex arguments, the magnitude of the elements are used for\n\
comparison.\n\
\n\
If called with two output arguments, also returns the index of the\n\
maximum value(s). Thus,\n\
@example\n\
[x, ix] = max([1, 3, 5, 2, 5])\n\
@end example\n\
\n\
@noindent\n\
returns @var{x} = 5 and @var{ix} = 3.")
{
  MINMAX_BODY (max);
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
