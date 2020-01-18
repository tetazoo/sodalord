// ColumnVector manipulations.
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

#include "f77-fcn.h"
#include "lo-error.h"
#include "mx-base.h"
#include "mx-inlines.cc"
#include "oct-cmplx.h"

// Fortran functions we call.

extern "C"
{
  int F77_FUNC (zgemv, ZGEMV) (const char*, const int&, const int&,
			      const Complex&, const Complex*,
			      const int&, const Complex*, const int&,
			      const Complex&, Complex*, const int&,
			      long);
}

// Complex Column Vector class

ComplexColumnVector::ComplexColumnVector (const ColumnVector& a)
   : MArray<Complex> (a.length ())
{
  for (int i = 0; i < length (); i++)
    elem (i) = a.elem (i);
}

bool
ComplexColumnVector::operator == (const ComplexColumnVector& a) const
{
  int len = length ();
  if (len != a.length ())
    return 0;
  return mx_inline_equal (data (), a.data (), len);
}

bool
ComplexColumnVector::operator != (const ComplexColumnVector& a) const
{
  return !(*this == a);
}

// destructive insert/delete/reorder operations

ComplexColumnVector&
ComplexColumnVector::insert (const ColumnVector& a, int r)
{
  int a_len = a.length ();
  if (r < 0 || r + a_len > length ())
    {
      (*current_liboctave_error_handler) ("range error for insert");
      return *this;
    }

  for (int i = 0; i < a_len; i++)
    elem (r+i) = a.elem (i);

  return *this;
}

ComplexColumnVector&
ComplexColumnVector::insert (const ComplexColumnVector& a, int r)
{
  int a_len = a.length ();
  if (r < 0 || r + a_len > length ())
    {
      (*current_liboctave_error_handler) ("range error for insert");
      return *this;
    }

  for (int i = 0; i < a_len; i++)
    elem (r+i) = a.elem (i);

  return *this;
}

ComplexColumnVector&
ComplexColumnVector::fill (double val)
{
  int len = length ();
  if (len > 0)
    for (int i = 0; i < len; i++)
      elem (i) = val;
  return *this;
}

ComplexColumnVector&
ComplexColumnVector::fill (const Complex& val)
{
  int len = length ();
  if (len > 0)
    for (int i = 0; i < len; i++)
      elem (i) = val;
  return *this;
}

ComplexColumnVector&
ComplexColumnVector::fill (double val, int r1, int r2)
{
  int len = length ();
  if (r1 < 0 || r2 < 0 || r1 >= len || r2 >= len)
    {
      (*current_liboctave_error_handler) ("range error for fill");
      return *this;
    }

  if (r1 > r2) { int tmp = r1; r1 = r2; r2 = tmp; }

  for (int i = r1; i <= r2; i++)
    elem (i) = val;

  return *this;
}

ComplexColumnVector&
ComplexColumnVector::fill (const Complex& val, int r1, int r2)
{
  int len = length ();
  if (r1 < 0 || r2 < 0 || r1 >= len || r2 >= len)
    {
      (*current_liboctave_error_handler) ("range error for fill");
      return *this;
    }

  if (r1 > r2) { int tmp = r1; r1 = r2; r2 = tmp; }

  for (int i = r1; i <= r2; i++)
    elem (i) = val;

  return *this;
}

ComplexColumnVector
ComplexColumnVector::stack (const ColumnVector& a) const
{
  int len = length ();
  int nr_insert = len;
  ComplexColumnVector retval (len + a.length ());
  retval.insert (*this, 0);
  retval.insert (a, nr_insert);
  return retval;
}

ComplexColumnVector
ComplexColumnVector::stack (const ComplexColumnVector& a) const
{
  int len = length ();
  int nr_insert = len;
  ComplexColumnVector retval (len + a.length ());
  retval.insert (*this, 0);
  retval.insert (a, nr_insert);
  return retval;
}

ComplexRowVector
ComplexColumnVector::hermitian (void) const
{
  int len = length ();
  return ComplexRowVector (mx_inline_conj_dup (data (), len), len);
}

ComplexRowVector
ComplexColumnVector::transpose (void) const
{
  return ComplexRowVector (*this);
}

ComplexColumnVector
conj (const ComplexColumnVector& a)
{
  int a_len = a.length ();
  ComplexColumnVector retval;
  if (a_len > 0)
    retval = ComplexColumnVector (mx_inline_conj_dup (a.data (), a_len), a_len);
  return retval;
}

// resize is the destructive equivalent for this one

ComplexColumnVector
ComplexColumnVector::extract (int r1, int r2) const
{
  if (r1 > r2) { int tmp = r1; r1 = r2; r2 = tmp; }

  int new_r = r2 - r1 + 1;

  ComplexColumnVector result (new_r);

  for (int i = 0; i < new_r; i++)
    result.elem (i) = elem (r1+i);

  return result;
}

// column vector by column vector -> column vector operations

ComplexColumnVector&
ComplexColumnVector::operator += (const ColumnVector& a)
{
  int len = length ();

  int a_len = a.length ();

  if (len != a_len)
    {
      gripe_nonconformant ("operator +=", len, a_len);
      return *this;
    }

  if (len == 0)
    return *this;

  Complex *d = fortran_vec (); // Ensures only one reference to my privates!

  mx_inline_add2 (d, a.data (), len);
  return *this;
}

ComplexColumnVector&
ComplexColumnVector::operator -= (const ColumnVector& a)
{
  int len = length ();

  int a_len = a.length ();

  if (len != a_len)
    {
      gripe_nonconformant ("operator -=", len, a_len);
      return *this;
    }

  if (len == 0)
    return *this;

  Complex *d = fortran_vec (); // Ensures only one reference to my privates!

  mx_inline_subtract2 (d, a.data (), len);
  return *this;
}

// matrix by column vector -> column vector operations

ComplexColumnVector
operator * (const ComplexMatrix& m, const ColumnVector& a)
{
  ComplexColumnVector tmp (a);
  return m * tmp;
}

ComplexColumnVector
operator * (const ComplexMatrix& m, const ComplexColumnVector& a)
{
  ComplexColumnVector retval;

  int nr = m.rows ();
  int nc = m.cols ();

  int a_len = a.length ();

  if (nc != a_len)
    gripe_nonconformant ("operator *", nr, nc, a_len, 1);
  else
    {
      if (nc == 0 || nr == 0)
	retval.resize (nr, 0.0);
      else
	{
	  int ld = nr;

	  retval.resize (nr);
	  Complex *y = retval.fortran_vec ();

	  F77_XFCN (zgemv, ZGEMV, ("N", nr, nc, 1.0, m.data (), ld,
				   a.data (), 1, 0.0, y, 1, 1L));

	  if (f77_exception_encountered)
	    (*current_liboctave_error_handler)
	      ("unrecoverable error in zgemv");
	}
    }

  return retval;
}

// matrix by column vector -> column vector operations

ComplexColumnVector
operator * (const Matrix& m, const ComplexColumnVector& a)
{
  ComplexMatrix tmp (m);
  return tmp * a;
}

// diagonal matrix by column vector -> column vector operations

ComplexColumnVector
operator * (const DiagMatrix& m, const ComplexColumnVector& a)
{
  int nr = m.rows ();
  int nc = m.cols ();

  int a_len = a.length ();

  if (nc != a_len)
    {
      gripe_nonconformant ("operator *", nr, nc, a_len, 1);
      return ComplexColumnVector ();
    }

  if (nc == 0 || nr == 0)
    return ComplexColumnVector (0);

  ComplexColumnVector result (nr);

  for (int i = 0; i < a_len; i++)
    result.elem (i) = a.elem (i) * m.elem (i, i);

  for (int i = a_len; i < nr; i++)
    result.elem (i) = 0.0;

  return result;
}

ComplexColumnVector
operator * (const ComplexDiagMatrix& m, const ColumnVector& a)
{
  int nr = m.rows ();
  int nc = m.cols ();

  int a_len = a.length ();

  if (nc != a_len)
    {
      gripe_nonconformant ("operator *", nr, nc, a_len, 1);
      return ComplexColumnVector ();
    }

  if (nc == 0 || nr == 0)
    return ComplexColumnVector (0);

  ComplexColumnVector result (nr);

  for (int i = 0; i < a_len; i++)
    result.elem (i) = a.elem (i) * m.elem (i, i);

  for (int i = a_len; i < nr; i++)
    result.elem (i) = 0.0;

  return result;
}

ComplexColumnVector
operator * (const ComplexDiagMatrix& m, const ComplexColumnVector& a)
{
  int nr = m.rows ();
  int nc = m.cols ();

  int a_len = a.length ();

  if (nc != a_len)
    {
      gripe_nonconformant ("operator *", nr, nc, a_len, 1);
      return ComplexColumnVector ();
    }

  if (nc == 0 || nr == 0)
    return ComplexColumnVector (0);

  ComplexColumnVector result (nr);

  for (int i = 0; i < a_len; i++)
    result.elem (i) = a.elem (i) * m.elem (i, i);

  for (int i = a_len; i < nr; i++)
    result.elem (i) = 0.0;

  return result;
}

// other operations

ComplexColumnVector
ComplexColumnVector::map (c_c_Mapper f) const
{
  ComplexColumnVector b (*this);
  return b.apply (f);
}

ColumnVector
ComplexColumnVector::map (d_c_Mapper f) const
{
  const Complex *d = data ();

  int len = length ();

  ColumnVector retval (len);

  double *r = retval.fortran_vec ();

  for (int i = 0; i < len; i++)
    r[i] = f (d[i]);

  return retval;
}

ComplexColumnVector&
ComplexColumnVector::apply (c_c_Mapper f)
{
  Complex *d = fortran_vec (); // Ensures only one reference to my privates!

  for (int i = 0; i < length (); i++)
    d[i] = f (d[i]);

  return *this;
}

Complex
ComplexColumnVector::min (void) const
{
  int len = length ();
  if (len == 0)
    return 0.0;

  Complex res = elem (0);
  double absres = abs (res);

  for (int i = 1; i < len; i++)
    if (abs (elem (i)) < absres)
      {
	res = elem (i);
	absres = abs (res);
      }

  return res;
}

Complex
ComplexColumnVector::max (void) const
{
  int len = length ();
  if (len == 0)
    return 0.0;

  Complex res = elem (0);
  double absres = abs (res);

  for (int i = 1; i < len; i++)
    if (abs (elem (i)) > absres)
      {
	res = elem (i);
	absres = abs (res);
      }

  return res;
}

// i/o

std::ostream&
operator << (std::ostream& os, const ComplexColumnVector& a)
{
//  int field_width = os.precision () + 7;
  for (int i = 0; i < a.length (); i++)
    os << /* setw (field_width) << */ a.elem (i) << "\n";
  return os;
}

std::istream&
operator >> (std::istream& is, ComplexColumnVector& a)
{
  int len = a.length();

  if (len < 1)
    is.clear (std::ios::badbit);
  else
    {
      double tmp;
      for (int i = 0; i < len; i++)
        {
          is >> tmp;
          if (is)
            a.elem (i) = tmp;
          else
            break;
        }
    }
  return is;
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
