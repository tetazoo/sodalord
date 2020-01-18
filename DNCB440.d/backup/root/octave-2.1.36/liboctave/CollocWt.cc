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

#include "CollocWt.h"
#include "f77-fcn.h"
#include "lo-error.h"

extern "C"
{
  int F77_FUNC (jcobi, JCOBI) (int&, int&, int&, int&, double&,
			      double&, double*, double*, double*,
			      double*);

  int F77_FUNC (dfopr, DFOPR) (int&, int&, int&, int&, int&, int&,
			      double*, double*, double*, double*,
			      double*);
}

// Error handling.

void
CollocWt::error (const char* msg)
{
  (*current_liboctave_error_handler) ("fatal CollocWt error: %s", msg);
}

CollocWt&
CollocWt::set_left (double val)
{
  if (val >= rb)
    {
      error ("left bound greater than right bound");
      return *this;
    }

  lb = val;
  initialized = 0;
  return *this;
}

CollocWt&
CollocWt::set_right (double val)
{
  if (val <= lb)
    {
      error ("right bound less than left bound");
      return *this;
    }

  rb = val;
  initialized = 0;
  return *this;
}

void
CollocWt::init (void)
{
  // Check for possible errors.

  double wid = rb - lb;
  if (wid <= 0.0)
    {
      error ("width less than or equal to zero");
      return;
    }

  int nt = n + inc_left + inc_right;

  if (nt < 0)
    {
      error ("total number of collocation points less than zero");
      return;
    }
  else if (nt == 0)
    return;

  Array<double> dif1 (nt);
  double *pdif1 = dif1.fortran_vec ();

  Array<double> dif2 (nt);
  double *pdif2 = dif2.fortran_vec ();

  Array<double> dif3 (nt);
  double *pdif3 = dif3.fortran_vec ();

  Array<double> vect (nt);
  double *pvect = vect.fortran_vec ();

  r.resize (nt);
  q.resize (nt);
  A.resize (nt, nt);
  B.resize (nt, nt);

  double *pr = r.fortran_vec ();

  // Compute roots.

  F77_FUNC (jcobi, JCOBI) (nt, n, inc_left, inc_right, Alpha, Beta,
			  pdif1, pdif2, pdif3, pr);

  int id;

  // First derivative weights.

  id = 1;
  for (int i = 1; i <= nt; i++)
    {
      F77_FUNC (dfopr, DFOPR) (nt, n, inc_left, inc_right, i, id, pdif1,
			      pdif2, pdif3, pr, pvect); 

      for (int j = 0; j < nt; j++)
	A (i-1, j) = vect.elem (j);
    }

  // Second derivative weights.

  id = 2;
  for (int i = 1; i <= nt; i++)
    {
      F77_FUNC (dfopr, DFOPR) (nt, n, inc_left, inc_right, i, id, pdif1,
			      pdif2, pdif3, pr, pvect); 

      for (int j = 0; j < nt; j++)
	B (i-1, j) = vect.elem (j);
    }

  // Gaussian quadrature weights.

  id = 3;
  double *pq = q.fortran_vec ();
  F77_FUNC (dfopr, DFOPR) (nt, n, inc_left, inc_right, id, id, pdif1,
			  pdif2, pdif3, pr, pq);

  initialized = 1;
}

std::ostream&
operator << (std::ostream& os, const CollocWt& a)
{
  if (a.left_included ())
    os << "left  boundary is included\n";
  else
    os << "left  boundary is not included\n";

  if (a.right_included ())
    os << "right boundary is included\n";
  else
    os << "right boundary is not included\n";

  os << "\n";

  os << a.Alpha << " " << a.Beta << "\n\n"
     << a.r << "\n\n"
     << a.q << "\n\n"
     << a.A << "\n"
     << a.B << "\n";

  return os;
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
