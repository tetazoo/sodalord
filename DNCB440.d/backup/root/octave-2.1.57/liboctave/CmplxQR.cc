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

#include "CmplxQR.h"
#include "f77-fcn.h"
#include "lo-error.h"

extern "C"
{
  F77_RET_T
  F77_FUNC (zgeqrf, ZGEQRF) (const int&, const int&, Complex*,
			     const int&, Complex*, Complex*,
			     const int&, int&); 

  F77_RET_T
  F77_FUNC (zungqr, ZUNGQR) (const int&, const int&, const int&,
			     Complex*, const int&, Complex*,
			     Complex*, const int&, int&);
}

ComplexQR::ComplexQR (const ComplexMatrix& a, QR::type qr_type)
  : q (), r ()
{
  init (a, qr_type);
}

void
ComplexQR::init (const ComplexMatrix& a, QR::type qr_type)
{
  int m = a.rows ();
  int n = a.cols ();

  if (m == 0 || n == 0)
    {
      (*current_liboctave_error_handler)
	("ComplexQR must have non-empty matrix");
      return;
    }

  int min_mn = m < n ? m : n;

  Array<Complex> tau (min_mn);
  Complex *ptau = tau.fortran_vec ();

  int lwork = 32*n;
  Array<Complex> work (lwork);
  Complex *pwork = work.fortran_vec ();

  int info = 0;

  ComplexMatrix A_fact;
  if (m > n && qr_type != QR::economy)
    {
      A_fact.resize (m, m);
      A_fact.insert (a, 0, 0);
    }
  else
    A_fact = a;

  Complex *tmp_data = A_fact.fortran_vec ();

  F77_XFCN (zgeqrf, ZGEQRF, (m, n, tmp_data, m, ptau, pwork, lwork, info));

  if (f77_exception_encountered)
    (*current_liboctave_error_handler) ("unrecoverable error in zgeqrf");
  else
    {
      if (qr_type == QR::raw)
	{
	  for (int j = 0; j < min_mn; j++)
	    {
	      int limit = j < min_mn - 1 ? j : min_mn - 1;
	      for (int i = limit + 1; i < m; i++)
		A_fact.elem (i, j) *= tau.elem (j);
	    }

	  r = A_fact;

	  if (m > n)
	    r.resize (m, n);
	}
      else
	{
	  int n2 = (qr_type == QR::economy) ? min_mn : m;

	  if (qr_type == QR::economy && m > n)
	    r.resize (n, n, 0.0);
	  else
	    r.resize (m, n, 0.0);

	  for (int j = 0; j < n; j++)
	    {
	      int limit = j < min_mn-1 ? j : min_mn-1;
	      for (int i = 0; i <= limit; i++)
		r.elem (i, j) = A_fact.elem (i, j);
	    }

	  lwork = 32 * n2;
	  work.resize (lwork);
	  Complex *pwork2 = work.fortran_vec ();

	  F77_XFCN (zungqr, ZUNGQR, (m, n2, min_mn, tmp_data, m, ptau,
				     pwork2, lwork, info));

	  if (f77_exception_encountered)
	    (*current_liboctave_error_handler)
	      ("unrecoverable error in zungqr");
	  else
	    {
	      q = A_fact;
	      q.resize (m, n2);
	    }
	}
    }
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
