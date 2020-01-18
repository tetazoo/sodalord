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

#include "dbleHESS.h"
#include "f77-fcn.h"
#include "lo-error.h"

extern "C"
{
  F77_RET_T
  F77_FUNC (dgebal, DGEBAL) (F77_CONST_CHAR_ARG_DECL,
			     const int&, double*, const int&, int&,
			     int&, double*, int&
			     F77_CHAR_ARG_LEN_DECL);

  F77_RET_T
  F77_FUNC (dgehrd, DGEHRD) (const int&, const int&, const int&,
			     double*, const int&, double*, double*,
			     const int&, int&);

  F77_RET_T
  F77_FUNC (dorghr, DORGHR) (const int&, const int&, const int&,
			     double*, const int&, double*, double*,
			     const int&, int&);

  F77_RET_T
  F77_FUNC (dgebak, DGEBAK) (F77_CONST_CHAR_ARG_DECL,
			     F77_CONST_CHAR_ARG_DECL,
			     const int&, const int&, const int&, double*,
			     const int&, double*, const int&, int&
			     F77_CHAR_ARG_LEN_DECL
			     F77_CHAR_ARG_LEN_DECL);
}

int
HESS::init (const Matrix& a)
{
  int a_nr = a.rows ();
  int a_nc = a.cols ();

  if (a_nr != a_nc)
    {
      (*current_liboctave_error_handler) ("HESS requires square matrix");
      return -1;
    }

  char job = 'N';
  char side = 'R';

  int n = a_nc;
  int lwork = 32 * n;
  int info;
  int ilo;
  int ihi;

  hess_mat = a;
  double *h = hess_mat.fortran_vec ();

  Array<double> scale (n);
  double *pscale = scale.fortran_vec ();

  F77_XFCN (dgebal, DGEBAL, (F77_CONST_CHAR_ARG2 (&job, 1),
			     n, h, n, ilo, ihi, pscale, info
			     F77_CHAR_ARG_LEN (1)));

  if (f77_exception_encountered)
    (*current_liboctave_error_handler) ("unrecoverable error in dgebal");
  else
    {
      Array<double> tau (n-1);
      double *ptau = tau.fortran_vec ();

      Array<double> work (lwork);
      double *pwork = work.fortran_vec ();

      F77_XFCN (dgehrd, DGEHRD, (n, ilo, ihi, h, n, ptau, pwork,
				 lwork, info));

      if (f77_exception_encountered)
	(*current_liboctave_error_handler) ("unrecoverable error in dgehrd");
      else
	{
	  unitary_hess_mat = hess_mat;
	  double *z = unitary_hess_mat.fortran_vec ();

	  F77_XFCN (dorghr, DORGHR, (n, ilo, ihi, z, n, ptau, pwork,
				     lwork, info));

	  if (f77_exception_encountered)
	    (*current_liboctave_error_handler)
	      ("unrecoverable error in dorghr");
	  else
	    {
	      F77_XFCN (dgebak, DGEBAK, (F77_CONST_CHAR_ARG2 (&job, 1),
					 F77_CONST_CHAR_ARG2 (&side, 1),
					 n, ilo, ihi, pscale, n, z,
					 n, info
					 F77_CHAR_ARG_LEN (1)
					 F77_CHAR_ARG_LEN (1)));

	      if (f77_exception_encountered)
		(*current_liboctave_error_handler)
		  ("unrecoverable error in dgebak");
	      else
		{
		  // If someone thinks of a more graceful way of doing
		  // this (or faster for that matter :-)), please let
		  // me know!

		  if (n > 2)
		    for (int j = 0; j < a_nc; j++)
		      for (int i = j+2; i < a_nr; i++)
			hess_mat.elem (i, j) = 0;
		}
	    }
	}
    }

  return info;
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
