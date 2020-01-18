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

#include "CmplxLU.h"
#include "f77-fcn.h"
#include "lo-error.h"

// Instantiate the base LU class for the types we need.

#include <base-lu.h>
#include <base-lu.cc>

template class base_lu <ComplexMatrix, Complex, Matrix, double>;

// Define the constructor for this particular derivation.

extern "C"
{
  F77_RET_T
  F77_FUNC (zgetrf, ZGETRF) (const int&, const int&, Complex*,
			     const int&, int*, int&);
}

ComplexLU::ComplexLU (const ComplexMatrix& a)
{
  int a_nr = a.rows ();
  int a_nc = a.cols ();
  int mn = (a_nr < a_nc ? a_nr : a_nc);

  ipvt.resize (mn);
  int *pipvt = ipvt.fortran_vec ();

  a_fact = a;
  Complex *tmp_data = a_fact.fortran_vec ();

  int info = 0;

  F77_XFCN (zgetrf, ZGETRF, (a_nr, a_nc, tmp_data, a_nr, pipvt, info));

  if (f77_exception_encountered)
    (*current_liboctave_error_handler) ("unrecoverable error in zgetrf");
  else
    ipvt -= 1;
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
