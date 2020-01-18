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

#if !defined (octave_DiagMatrix_h)
#define octave_DiagMatrix_h 1

#if defined (__GNUG__)
#pragma interface
#endif

#include "MDiagArray2.h"

#include "dRowVector.h"
#include "dColVector.h"

#include "mx-defs.h"

class
DiagMatrix : public MDiagArray2<double>
{
friend class SVD;
friend class ComplexSVD;

public:

  DiagMatrix (void) : MDiagArray2<double> () { }

  DiagMatrix (int r, int c) : MDiagArray2<double> (r, c) { }

  DiagMatrix (int r, int c, double val) : MDiagArray2<double> (r, c, val) { }

  DiagMatrix (const DiagMatrix& a) : MDiagArray2<double> (a) { }

  DiagMatrix (const MDiagArray2<double>& a) : MDiagArray2<double> (a) { }

  explicit DiagMatrix (const RowVector& a) : MDiagArray2<double> (a) { }

  explicit DiagMatrix (const ColumnVector& a) : MDiagArray2<double> (a) { }

  DiagMatrix& operator = (const DiagMatrix& a)
    {
      MDiagArray2<double>::operator = (a);
      return *this;
    }

  bool operator == (const DiagMatrix& a) const;
  bool operator != (const DiagMatrix& a) const;

  DiagMatrix& fill (double val);
  DiagMatrix& fill (double val, int beg, int end);
  DiagMatrix& fill (const ColumnVector& a);
  DiagMatrix& fill (const RowVector& a);
  DiagMatrix& fill (const ColumnVector& a, int beg);
  DiagMatrix& fill (const RowVector& a, int beg);

  DiagMatrix transpose (void) const;

  friend DiagMatrix real (const ComplexDiagMatrix& a);
  friend DiagMatrix imag (const ComplexDiagMatrix& a);

  // resize is the destructive analog for this one

  Matrix extract (int r1, int c1, int r2, int c2) const;

  // extract row or column i.

  RowVector row (int i) const;
  RowVector row (char *s) const;

  ColumnVector column (int i) const;
  ColumnVector column (char *s) const;

  DiagMatrix inverse (void) const;
  DiagMatrix inverse (int& info) const;

  // other operations

  ColumnVector diag (void) const;
  ColumnVector diag (int k) const;

  // i/o

  friend std::ostream& operator << (std::ostream& os, const DiagMatrix& a);

private:

  DiagMatrix (double *d, int nr, int nc) : MDiagArray2<double> (d, nr, nc) { }
};

// diagonal matrix by diagonal matrix -> diagonal matrix operations

DiagMatrix
operator * (const DiagMatrix& a, const DiagMatrix& b);

MDIAGARRAY2_FORWARD_DEFS (MDiagArray2, DiagMatrix, double)

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
