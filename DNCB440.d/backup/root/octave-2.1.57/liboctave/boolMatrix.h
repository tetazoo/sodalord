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

#if !defined (octave_boolMatrix_int_h)
#define octave_boolMatrix_int_h 1

#if defined (__GNUG__) && defined (USE_PRAGMA_INTERFACE_IMPLEMENTATION)
#pragma interface
#endif

#include "Array2.h"

#include "mx-defs.h"
#include "mx-op-defs.h"

class
boolMatrix : public Array2<bool>
{
public:

  boolMatrix (void) : Array2<bool> () { }
  boolMatrix (int r, int c) : Array2<bool> (r, c) { }
  boolMatrix (int r, int c, bool val) : Array2<bool> (r, c, val) { }
  boolMatrix (const Array2<bool>& a) : Array2<bool> (a) { }
  boolMatrix (const boolMatrix& a) : Array2<bool> (a) { }

  boolMatrix& operator = (const boolMatrix& a)
    {
      Array2<bool>::operator = (a);
      return *this;
    }

  bool operator == (const boolMatrix& a) const;
  bool operator != (const boolMatrix& a) const;

  boolMatrix transpose (void) const { return Array2<bool>::transpose (); }

  // destructive insert/delete/reorder operations

  boolMatrix& insert (const boolMatrix& a, int r, int c);

  // unary operations

  boolMatrix operator ! (void) const;

  // other operations

  boolMatrix all (int dim = -1) const;
  boolMatrix any (int dim = -1) const;

#if 0
  // i/o

  friend std::ostream& operator << (std::ostream& os, const Matrix& a);
  friend std::istream& operator >> (std::istream& is, Matrix& a);
#endif

  static bool resize_fill_value (void) { return false; }

private:

  boolMatrix (bool *b, int r, int c) : Array2<bool> (b, r, c) { }
};

MM_CMP_OP_DECLS (boolMatrix, boolMatrix)

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
