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

#include "EIG.h"
#include "dColVector.h"
#include "f77-fcn.h"
#include "lo-error.h"

extern "C"
{
  F77_RET_T
  F77_FUNC (dgeev, DGEEV) (F77_CONST_CHAR_ARG_DECL,
			   F77_CONST_CHAR_ARG_DECL,
			   const int&, double*, const int&, double*,
			   double*, double*, const int&, double*,
			   const int&, double*, const int&, int&
			   F77_CHAR_ARG_LEN_DECL
			   F77_CHAR_ARG_LEN_DECL);

  F77_RET_T
  F77_FUNC (zgeev, ZGEEV) (F77_CONST_CHAR_ARG_DECL,
			   F77_CONST_CHAR_ARG_DECL,
			   const int&, Complex*, const int&, Complex*,
			   Complex*, const int&, Complex*, const int&,
			   Complex*, const int&, double*, int&
			   F77_CHAR_ARG_LEN_DECL
			   F77_CHAR_ARG_LEN_DECL);

  F77_RET_T
  F77_FUNC (dsyev, DSYEV) (F77_CONST_CHAR_ARG_DECL,
			   F77_CONST_CHAR_ARG_DECL,
			   const int&, double*, const int&, double*,
			   double*, const int&, int&
			   F77_CHAR_ARG_LEN_DECL
			   F77_CHAR_ARG_LEN_DECL);

  F77_RET_T
  F77_FUNC (zheev, ZHEEV) (F77_CONST_CHAR_ARG_DECL,
			   F77_CONST_CHAR_ARG_DECL,
			   const int&, Complex*, const int&, double*,
			   Complex*, const int&, double*, int&
			   F77_CHAR_ARG_LEN_DECL
			   F77_CHAR_ARG_LEN_DECL);
}

int
EIG::init (const Matrix& a, bool calc_ev)
{
  if (a.is_symmetric ())
    return symmetric_init (a, calc_ev);

  int n = a.rows ();

  if (n != a.cols ())
    {
      (*current_liboctave_error_handler) ("EIG requires square matrix");
      return -1;
    }

  int info = 0;

  Matrix atmp = a;
  double *tmp_data = atmp.fortran_vec ();

  Array<double> wr (n);
  double *pwr = wr.fortran_vec ();

  Array<double> wi (n);
  double *pwi = wi.fortran_vec ();

  int nvr = calc_ev ? n : 0;
  Matrix vr (nvr, nvr);
  double *pvr = vr.fortran_vec ();

  int lwork = -1;
  double dummy_work;

  double *dummy = 0;
  int idummy = 1;

  F77_XFCN (dgeev, DGEEV, (F77_CONST_CHAR_ARG2 ("N", 1),
			   F77_CONST_CHAR_ARG2 (calc_ev ? "V" : "N", 1),
			   n, tmp_data, n, pwr, pwi, dummy,
			   idummy, pvr, n, &dummy_work, lwork, info
			   F77_CHAR_ARG_LEN (1)
			   F77_CHAR_ARG_LEN (1)));

  if (! f77_exception_encountered && info == 0)
    {
      lwork = static_cast<int> (dummy_work);
      Array<double> work (lwork);
      double *pwork = work.fortran_vec ();

      F77_XFCN (dgeev, DGEEV, (F77_CONST_CHAR_ARG2 ("N", 1),
			       F77_CONST_CHAR_ARG2 (calc_ev ? "V" : "N", 1),
			       n, tmp_data, n, pwr, pwi, dummy,
			       idummy, pvr, n, pwork, lwork, info
			       F77_CHAR_ARG_LEN (1)
			       F77_CHAR_ARG_LEN (1)));

      if (f77_exception_encountered || info < 0)
	{
	  (*current_liboctave_error_handler) ("unrecoverable error in dgeev");
	  return info;
	}

      if (info > 0)
	{
	  (*current_liboctave_error_handler) ("dgeev failed to converge");
	  return info;
	}

      lambda.resize (n);
      v.resize (nvr, nvr);

      for (int j = 0; j < n; j++)
	{
	  if (wi.elem (j) == 0.0)
	    {
	      lambda.elem (j) = Complex (wr.elem (j));
	      for (int i = 0; i < nvr; i++)
		v.elem (i, j) = vr.elem (i, j);
	    }
	  else
	    {
	      if (j+1 >= n)
		{
		  (*current_liboctave_error_handler) ("EIG: internal error");
		  return -1;
		}

	      lambda.elem(j) = Complex (wr.elem(j), wi.elem(j));
	      lambda.elem(j+1) = Complex (wr.elem(j+1), wi.elem(j+1));

	      for (int i = 0; i < nvr; i++)
		{
		  double real_part = vr.elem (i, j);
		  double imag_part = vr.elem (i, j+1);
		  v.elem (i, j) = Complex (real_part, imag_part);
		  v.elem (i, j+1) = Complex (real_part, -imag_part);
		}
	      j++;
	    }
	}
    }
  else
    (*current_liboctave_error_handler) ("dgeev workspace query failed");

  return info;
}

int
EIG::symmetric_init (const Matrix& a, bool calc_ev)
{
  int n = a.rows ();

  if (n != a.cols ())
    {
      (*current_liboctave_error_handler) ("EIG requires square matrix");
      return -1;
    }

  int info = 0;

  Matrix atmp = a;
  double *tmp_data = atmp.fortran_vec ();

  ColumnVector wr (n);
  double *pwr = wr.fortran_vec ();

  int lwork = -1;
  double dummy_work;

  F77_XFCN (dsyev, DSYEV, (F77_CONST_CHAR_ARG2 (calc_ev ? "V" : "N", 1),
			   F77_CONST_CHAR_ARG2 ("U", 1),
			   n, tmp_data, n, pwr, &dummy_work, lwork, info
			   F77_CHAR_ARG_LEN (1)
			   F77_CHAR_ARG_LEN (1)));

  if (! f77_exception_encountered && info == 0)
    {
      lwork = static_cast<int> (dummy_work);
      Array<double> work (lwork);
      double *pwork = work.fortran_vec ();

      F77_XFCN (dsyev, DSYEV, (F77_CONST_CHAR_ARG2 (calc_ev ? "V" : "N", 1),
			       F77_CONST_CHAR_ARG2 ("U", 1),
			       n, tmp_data, n, pwr, pwork, lwork, info
			       F77_CHAR_ARG_LEN (1)
			       F77_CHAR_ARG_LEN (1)));

      if (f77_exception_encountered || info < 0)
	{
	  (*current_liboctave_error_handler) ("unrecoverable error in dsyev");
	  return info;
	}

      if (info > 0)
	{
	  (*current_liboctave_error_handler) ("dsyev failed to converge");
	  return info;
	}

      lambda = ComplexColumnVector (wr);
      v = calc_ev ? ComplexMatrix (atmp) : ComplexMatrix ();
    }
  else
    (*current_liboctave_error_handler) ("dsyev workspace query failed");

  return info;
}

int
EIG::init (const ComplexMatrix& a, bool calc_ev)
{
  if (a.is_hermitian ())
    return hermitian_init (a, calc_ev);

  int n = a.rows ();

  if (n != a.cols ())
    {
      (*current_liboctave_error_handler) ("EIG requires square matrix");
      return -1;
    }

  int info = 0;

  ComplexMatrix atmp = a;
  Complex *tmp_data = atmp.fortran_vec ();

  ComplexColumnVector w (n);
  Complex *pw = w.fortran_vec ();

  int nvr = calc_ev ? n : 0;
  ComplexMatrix vtmp (nvr, nvr);
  Complex *pv = vtmp.fortran_vec ();

  int lwork = -1;
  Complex dummy_work;

  int lrwork = 2*n;
  Array<double> rwork (lrwork);
  double *prwork = rwork.fortran_vec ();

  Complex *dummy = 0;
  int idummy = 1;

  F77_XFCN (zgeev, ZGEEV, (F77_CONST_CHAR_ARG2 ("N", 1),
			   F77_CONST_CHAR_ARG2 (calc_ev ? "V" : "N", 1),
			   n, tmp_data, n, pw, dummy, idummy,
			   pv, n, &dummy_work, lwork, prwork, info
			   F77_CHAR_ARG_LEN (1)
			   F77_CHAR_ARG_LEN (1)));

  if (! f77_exception_encountered && info == 0)
    {
      lwork = static_cast<int> (dummy_work.real ());
      Array<Complex> work (lwork);
      Complex *pwork = work.fortran_vec ();

      F77_XFCN (zgeev, ZGEEV, (F77_CONST_CHAR_ARG2 ("N", 1),
			       F77_CONST_CHAR_ARG2 (calc_ev ? "V" : "N", 1),
			       n, tmp_data, n, pw, dummy, idummy,
			       pv, n, pwork, lwork, prwork, info
			       F77_CHAR_ARG_LEN (1)
			       F77_CHAR_ARG_LEN (1)));

      if (f77_exception_encountered || info < 0)
	{
	  (*current_liboctave_error_handler) ("unrecoverable error in zgeev");
	  return info;
	}

      if (info > 0)
	{
	  (*current_liboctave_error_handler) ("zgeev failed to converge");
	  return info;
	}

      lambda = w;
      v = vtmp;
    }
  else
    (*current_liboctave_error_handler) ("zgeev workspace query failed");

  return info;
}

int
EIG::hermitian_init (const ComplexMatrix& a, bool calc_ev)
{
  int n = a.rows ();

  if (n != a.cols ())
    {
      (*current_liboctave_error_handler) ("EIG requires square matrix");
      return -1;
    }

  int info = 0;

  ComplexMatrix atmp = a;
  Complex *tmp_data = atmp.fortran_vec ();

  ColumnVector wr (n);
  double *pwr = wr.fortran_vec ();

  int lwork = -1;
  Complex dummy_work;

  int lrwork = 3*n;
  Array<double> rwork (lrwork);
  double *prwork = rwork.fortran_vec ();

  F77_XFCN (zheev, ZHEEV, (F77_CONST_CHAR_ARG2 (calc_ev ? "V" : "N", 1),
			   F77_CONST_CHAR_ARG2 ("U", 1),
			   n, tmp_data, n, pwr, &dummy_work, lwork,
			   prwork, info
			   F77_CHAR_ARG_LEN (1)
			   F77_CHAR_ARG_LEN (1)));

  if (! f77_exception_encountered && info == 0)
    {
      lwork = static_cast<int> (dummy_work.real ());
      Array<Complex> work (lwork);
      Complex *pwork = work.fortran_vec ();

      F77_XFCN (zheev, ZHEEV, (F77_CONST_CHAR_ARG2 (calc_ev ? "V" : "N", 1),
			       F77_CONST_CHAR_ARG2 ("U", 1),
			       n, tmp_data, n, pwr, pwork, lwork, prwork, info
			       F77_CHAR_ARG_LEN (1)
			       F77_CHAR_ARG_LEN (1)));

      if (f77_exception_encountered || info < 0)
	{
	  (*current_liboctave_error_handler) ("unrecoverable error in zheev");
	  return info;
	}

      if (info > 0)
	{
	  (*current_liboctave_error_handler) ("zheev failed to converge");
	  return info;
	}

      lambda = ComplexColumnVector (wr);
      v = calc_ev ? ComplexMatrix (atmp) : ComplexMatrix ();
    }
  else
    (*current_liboctave_error_handler) ("zheev workspace query failed");

  return info;
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
