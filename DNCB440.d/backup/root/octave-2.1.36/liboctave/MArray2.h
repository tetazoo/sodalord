// Template array classes with like-type math ops
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
#pragma interface
#endif

#if !defined (octave_MArray2_h)
#define octave_MArray2_h 1

#include "Array2.h"

// Two dimensional array with math ops.

// But first, some preprocessor abuse...

#include "MArray-defs.h"

MARRAY_OPS_FORWARD_DECLS (MArray2)

template <class T>
class
MArray2 : public Array2<T>
{
protected:

  MArray2 (T *d, int n, int m) : Array2<T> (d, n, m) { }

public:

  MArray2 (void) : Array2<T> () { }

  MArray2 (int n, int m) : Array2<T> (n, m) { }

  MArray2 (int n, int m, const T& val) : Array2<T> (n, m, val) { }

  MArray2 (const MArray2<T>& a) : Array2<T> (a) { }

  MArray2 (const Array2<T>& a) : Array2<T> (a) { }

  ~MArray2 (void) { }

  MArray2<T>& operator = (const MArray2<T>& a)
    {
      Array2<T>::operator = (a);
      return *this;
    }

  MArray2<T>& insert (const Array2<T>& a, int r, int c)
  {
    Array2<T>::insert (a, r, c);
    return *this;
  }

  MArray2<T> transpose (void) const { return Array2<T>::transpose (); }

  // Currently, the OPS functions don't need to be friends, but that
  // may change.

  // MARRAY_OPS_FRIEND_DECLS (MArray2)
};

extern void
gripe_nonconformant (const char *op, int op1_nr, int op1_nc,
		     int op2_nr, int op2_nc);

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
