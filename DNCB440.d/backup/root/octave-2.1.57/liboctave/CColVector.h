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

#if !defined (octave_ComplexColumnVector_h)
#define octave_ComplexColumnVector_h 1

#if defined (__GNUG__) && defined (USE_PRAGMA_INTERFACE_IMPLEMENTATION)
#pragma interface
#endif

#include "MArray.h"

#include "mx-defs.h"

class
ComplexColumnVector : public MArray<Complex>
{
friend class ComplexMatrix;
friend class ComplexRowVector;

public:

  ComplexColumnVector (void) : MArray<Complex> () { }

  explicit ComplexColumnVector (int n) : MArray<Complex> (n) { }

  ComplexColumnVector (int n, const Complex& val)
    : MArray<Complex> (n, val) { }

  ComplexColumnVector (const ComplexColumnVector& a) : MArray<Complex> (a) { }

  ComplexColumnVector (const MArray<Complex>& a) : MArray<Complex> (a) { }

  explicit ComplexColumnVector (const ColumnVector& a);

  ComplexColumnVector& operator = (const ComplexColumnVector& a)
    {
      MArray<Complex>::operator = (a);
      return *this;
    }

  bool operator == (const ComplexColumnVector& a) const;
  bool operator != (const ComplexColumnVector& a) const;

  // destructive insert/delete/reorder operations

  ComplexColumnVector& insert (const ColumnVector& a, int r);
  ComplexColumnVector& insert (const ComplexColumnVector& a, int r);

  ComplexColumnVector& fill (double val);
  ComplexColumnVector& fill (const Complex& val);
  ComplexColumnVector& fill (double val, int r1, int r2);
  ComplexColumnVector& fill (const Complex& val, int r1, int r2);

  ComplexColumnVector stack (const ColumnVector& a) const;
  ComplexColumnVector stack (const ComplexColumnVector& a) const;

  ComplexRowVector hermitian (void) const;  // complex conjugate transpose.
  ComplexRowVector transpose (void) const;

  friend ComplexColumnVector conj (const ComplexColumnVector& a);

  // resize is the destructive equivalent for this one

  ComplexColumnVector extract (int r1, int r2) const;

  ComplexColumnVector extract_n (int r1, int n) const;

  // column vector by column vector -> column vector operations

  ComplexColumnVector& operator += (const ColumnVector& a);
  ComplexColumnVector& operator -= (const ColumnVector& a);

  // matrix by column vector -> column vector operations

  friend ComplexColumnVector operator * (const ComplexMatrix& a,
					 const ColumnVector& b);

  friend ComplexColumnVector operator * (const ComplexMatrix& a,
					 const ComplexColumnVector& b);

  // matrix by column vector -> column vector operations

  friend ComplexColumnVector operator * (const Matrix& a,
					 const ComplexColumnVector& b);

  // diagonal matrix by column vector -> column vector operations

  friend ComplexColumnVector operator * (const DiagMatrix& a,
					 const ComplexColumnVector& b);

  friend ComplexColumnVector operator * (const ComplexDiagMatrix& a,
					 const ColumnVector& b);

  friend ComplexColumnVector operator * (const ComplexDiagMatrix& a,
					 const ComplexColumnVector& b);

  // other operations

  ComplexColumnVector map (c_c_Mapper f) const;
  ColumnVector map (d_c_Mapper f) const;

  ComplexColumnVector& apply (c_c_Mapper f);

  Complex min (void) const;
  Complex max (void) const;

  // i/o

  friend std::ostream& operator << (std::ostream& os, const ComplexColumnVector& a);
  friend std::istream& operator >> (std::istream& is, ComplexColumnVector& a);

private:

  ComplexColumnVector (Complex *d, int l) : MArray<Complex> (d, l) { }
};

MARRAY_FORWARD_DEFS (MArray, ComplexColumnVector, Complex)

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
