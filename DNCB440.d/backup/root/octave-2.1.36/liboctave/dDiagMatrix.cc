// DiagMatrix manipulations.
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

#if defined (__GNUG__)
#pragma implementation
#endif

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>

#include "lo-error.h"
#include "mx-base.h"
#include "mx-inlines.cc"
#include "oct-cmplx.h"

// Diagonal Matrix class.

bool
DiagMatrix::operator == (const DiagMatrix& a) const
{
  if (rows () != a.rows () || cols () != a.cols ())
    return 0;

  return mx_inline_equal (data (), a.data (), length ());
}

bool
DiagMatrix::operator != (const DiagMatrix& a) const
{
  return !(*this == a);
}

DiagMatrix&
DiagMatrix::fill (double val)
{
  for (int i = 0; i < length (); i++)
    elem (i, i) = val;
  return *this;
}

DiagMatrix&
DiagMatrix::fill (double val, int beg, int end)
{
  if (beg < 0 || end >= length () || end < beg)
    {
      (*current_liboctave_error_handler) ("range error for fill");
      return *this;
    }

  for (int i = beg; i <= end; i++)
    elem (i, i) = val;

  return *this;
}

DiagMatrix&
DiagMatrix::fill (const ColumnVector& a)
{
  int len = length ();
  if (a.length () != len)
    {
      (*current_liboctave_error_handler) ("range error for fill");
      return *this;
    }

  for (int i = 0; i < len; i++)
    elem (i, i) = a.elem (i);

  return *this;
}

DiagMatrix&
DiagMatrix::fill (const RowVector& a)
{
  int len = length ();
  if (a.length () != len)
    {
      (*current_liboctave_error_handler) ("range error for fill");
      return *this;
    }

  for (int i = 0; i < len; i++)
    elem (i, i) = a.elem (i);

  return *this;
}

DiagMatrix&
DiagMatrix::fill (const ColumnVector& a, int beg)
{
  int a_len = a.length ();
  if (beg < 0 || beg + a_len >= length ())
    {
      (*current_liboctave_error_handler) ("range error for fill");
      return *this;
    }

  for (int i = 0; i < a_len; i++)
    elem (i+beg, i+beg) = a.elem (i);

  return *this;
}

DiagMatrix&
DiagMatrix::fill (const RowVector& a, int beg)
{
  int a_len = a.length ();
  if (beg < 0 || beg + a_len >= length ())
    {
      (*current_liboctave_error_handler) ("range error for fill");
      return *this;
    }

  for (int i = 0; i < a_len; i++)
    elem (i+beg, i+beg) = a.elem (i);

  return *this;
}

DiagMatrix
DiagMatrix::transpose (void) const
{
  return DiagMatrix (mx_inline_dup (data (), length ()), cols (), rows ());
}

DiagMatrix
real (const ComplexDiagMatrix& a)
{
  DiagMatrix retval;
  int a_len = a.length ();
  if (a_len > 0)
    retval = DiagMatrix (mx_inline_real_dup (a.data (), a_len), a.rows (),
			 a.cols ());
  return retval;
}

DiagMatrix
imag (const ComplexDiagMatrix& a)
{
  DiagMatrix retval;
  int a_len = a.length ();
  if (a_len > 0)
    retval = DiagMatrix (mx_inline_imag_dup (a.data (), a_len), a.rows (),
			 a.cols ());
  return retval;
}

Matrix
DiagMatrix::extract (int r1, int c1, int r2, int c2) const
{
  if (r1 > r2) { int tmp = r1; r1 = r2; r2 = tmp; }
  if (c1 > c2) { int tmp = c1; c1 = c2; c2 = tmp; }

  int new_r = r2 - r1 + 1;
  int new_c = c2 - c1 + 1;

  Matrix result (new_r, new_c);

  for (int j = 0; j < new_c; j++)
    for (int i = 0; i < new_r; i++)
      result.elem (i, j) = elem (r1+i, c1+j);

  return result;
}

// extract row or column i.

RowVector
DiagMatrix::row (int i) const
{
  int r = rows ();
  int c = cols ();
  if (i < 0 || i >= r)
    {
      (*current_liboctave_error_handler) ("invalid row selection");
      return RowVector (); 
    }

  RowVector retval (c, 0.0);
  if (r <= c || (r > c && i < c))
    retval.elem (i) = elem (i, i);

  return retval;
}

RowVector
DiagMatrix::row (char *s) const
{
  if (! s)
    {
      (*current_liboctave_error_handler) ("invalid row selection");
      return RowVector (); 
    }

  char c = *s;
  if (c == 'f' || c == 'F')
    return row (0);
  else if (c == 'l' || c == 'L')
    return row (rows () - 1);
  else
    {
      (*current_liboctave_error_handler) ("invalid row selection");
      return RowVector (); 
    }
}

ColumnVector
DiagMatrix::column (int i) const
{
  int r = rows ();
  int c = cols ();
  if (i < 0 || i >= c)
    {
      (*current_liboctave_error_handler) ("invalid column selection");
      return ColumnVector (); 
    }

  ColumnVector retval (r, 0.0);
  if (r >= c || (r < c && i < r))
    retval.elem (i) = elem (i, i);

  return retval;
}

ColumnVector
DiagMatrix::column (char *s) const
{
  if (! s)
    {
      (*current_liboctave_error_handler) ("invalid column selection");
      return ColumnVector (); 
    }

  char c = *s;
  if (c == 'f' || c == 'F')
    return column (0);
  else if (c == 'l' || c == 'L')
    return column (cols () - 1);
  else
    {
      (*current_liboctave_error_handler) ("invalid column selection");
      return ColumnVector (); 
    }
}

DiagMatrix
DiagMatrix::inverse (void) const
{
  int info;
  return inverse (info);
}

DiagMatrix
DiagMatrix::inverse (int &info) const
{
  int r = rows ();
  int c = cols ();
  int len = length ();
  if (r != c)
    {
      (*current_liboctave_error_handler) ("inverse requires square matrix");
      return DiagMatrix ();
    }

  DiagMatrix retval (r, c);

  info = 0;
  for (int i = 0; i < len; i++)
    {
      if (elem (i, i) == 0.0)
	{
	  info = -1;
	  return *this;
	}
      else
	retval.elem (i, i) = 1.0 / elem (i, i);
    }

  return retval;
}

// diagonal matrix by diagonal matrix -> diagonal matrix operations

// diagonal matrix by diagonal matrix -> diagonal matrix operations

DiagMatrix
operator * (const DiagMatrix& a, const DiagMatrix& b)
{
  int a_nr = a.rows ();
  int a_nc = a.cols ();

  int b_nr = b.rows ();
  int b_nc = b.cols ();

  if (a_nc != b_nr)
    {
      gripe_nonconformant ("operaotr *", a_nr, a_nc, b_nr, b_nc);
      return DiagMatrix ();
    }

  if (a_nr == 0 || a_nc == 0 || b_nc == 0)
    return DiagMatrix (a_nr, a_nc, 0.0);

  DiagMatrix c (a_nr, b_nc);

  int len = a_nr < b_nc ? a_nr : b_nc;

  for (int i = 0; i < len; i++)
    {
      double a_element = a.elem (i, i);
      double b_element = b.elem (i, i);

      if (a_element == 0.0 || b_element == 0.0)
        c.elem (i, i) = 0.0;
      else if (a_element == 1.0)
        c.elem (i, i) = b_element;
      else if (b_element == 1.0)
        c.elem (i, i) = a_element;
      else
        c.elem (i, i) = a_element * b_element;
    }

  return c;
}

// other operations

ColumnVector
DiagMatrix::diag (void) const
{
  return diag (0);
}

// Could be optimized...

ColumnVector
DiagMatrix::diag (int k) const
{
  int nnr = rows ();
  int nnc = cols ();
  if (k > 0)
    nnc -= k;
  else if (k < 0)
    nnr += k;

  ColumnVector d;

  if (nnr > 0 && nnc > 0)
    {
      int ndiag = (nnr < nnc) ? nnr : nnc;

      d.resize (ndiag);

      if (k > 0)
	{
	  for (int i = 0; i < ndiag; i++)
	    d.elem (i) = elem (i, i+k);
	}
      else if ( k < 0)
	{
	  for (int i = 0; i < ndiag; i++)
	    d.elem (i) = elem (i-k, i);
	}
      else
	{
	  for (int i = 0; i < ndiag; i++)
	    d.elem (i) = elem (i, i);
	}
    }
  else
    std::cerr << "diag: requested diagonal out of range\n";

  return d;
}

std::ostream&
operator << (std::ostream& os, const DiagMatrix& a)
{
//  int field_width = os.precision () + 7;

  for (int i = 0; i < a.rows (); i++)
    {
      for (int j = 0; j < a.cols (); j++)
	{
	  if (i == j)
	    os << " " /* setw (field_width) */ << a.elem (i, i);
	  else
	    os << " " /* setw (field_width) */ << 0.0;
	}
      os << "\n";
    }
  return os;
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
