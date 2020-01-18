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

#if !defined (octave_LinConst_h)
#define octave_LinConst_h 1

#if defined (__GNUG__)
#pragma interface
#endif

#include <iostream>

class ColumnVector;

#include <cfloat>

#include "dMatrix.h"
#include "Bounds.h"

class
LinConst : public Bounds
{
public:

  LinConst (void)
    : Bounds (), A () { }

  LinConst (const ColumnVector& l, const Matrix& amat, const ColumnVector& u)
    : Bounds (l, u), A (amat)
      {
	if (Bounds::size () != amat.rows ())
	  error ("nonconformant constraint matrix and bounds vectors");
      }

  LinConst (const LinConst& a)
    : Bounds (a.lb, a.ub), A (a.A) { }

  LinConst& operator = (const LinConst& a)
    {
      if (this != &a)
	{
	  Bounds::operator = (a);

	  A  = a.A;
	}
      return *this;
    }

  ~LinConst (void) { }

  Matrix constraint_matrix (void) const { return A; }

  LinConst& set_constraint_matrix (const Matrix& amat)
    {
      if (lb.capacity () != amat.rows ())
	error ("inconsistent size for new linear constraint matrix");

      A = amat;

      return *this;
    }

  friend std::ostream& operator << (std::ostream& os, const LinConst& b);

protected:

  Matrix A;

private:

  void error (const char *msg);
};

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
