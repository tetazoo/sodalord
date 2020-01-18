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

#if !defined (octave_DASSL_h)
#define octave_DASSL_h 1

#if defined (__GNUG__) && defined (USE_PRAGMA_INTERFACE_IMPLEMENTATION)
#pragma interface
#endif

#include <cfloat>
#include <cmath>

#include "DASSL-opts.h"

class
DASSL : public DAE, public DASSL_options
{
public:

  DASSL (void) : DAE (), DASSL_options (), initialized (false) { }

  DASSL (const ColumnVector& s, double tm, DAEFunc& f)
    : DAE (s, tm, f), DASSL_options (), initialized (false) { }

  DASSL (const ColumnVector& s, const ColumnVector& deriv,
	 double tm, DAEFunc& f)
    : DAE (s, deriv, tm, f), DASSL_options (), initialized (false) { }

  ~DASSL (void) { }

  ColumnVector do_integrate (double t);

  Matrix do_integrate (const ColumnVector& tout);

  Matrix do_integrate (const ColumnVector& tout, const ColumnVector& tcrit); 

  Matrix integrate (const ColumnVector& tout, Matrix& xdot_out);

  Matrix integrate (const ColumnVector& tout, Matrix& xdot_out,
		    const ColumnVector& tcrit); 

  std::string error_message (void) const;

private:

  bool initialized;

  int liw;  
  int lrw;

  Array<int> info;
  Array<int> iwork;

  Array<double> rwork;

  Array<double> abs_tol;
  Array<double> rel_tol;

  double *px;
  double *pxdot;
  double *pabs_tol;
  double *prel_tol;
  int *pinfo;
  int *piwork;
  double *prwork;
};

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
