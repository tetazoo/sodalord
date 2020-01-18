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

#if defined (__GNUG__) && defined (USE_PRAGMA_INTERFACE_IMPLEMENTATION)
#pragma interface
#endif

#if !defined (octave_MArrayN_h)
#define octave_MArrayN_h 1

#include "ArrayN.h"
#include "MArray2.h"
#include "dim-vector.h"

// N-dimensional array with math ops.

// But first, some preprocessor abuse...

#include "MArray-defs.h"

MARRAY_OPS_FORWARD_DECLS (MArrayN)

template <class T>
class
MArrayN : public ArrayN<T>
{
protected:

  MArrayN (T *d, const dim_vector& dv) : ArrayN<T> (d, dv) { }

public:
  
  MArrayN (void) : ArrayN<T> () {}
  
  MArrayN (const dim_vector& dv) : ArrayN<T> (dv) { }
  
  MArrayN (const dim_vector& dv, const T& val) : ArrayN<T> (dv, val) { }

  MArrayN (const Array2<T>& a) : ArrayN<T> (a) { }

  MArrayN (const ArrayN<T>& a) : ArrayN<T> (a) { }

  MArrayN (const MArrayN<T>& a) : ArrayN<T> (a) { }

  ~MArrayN (void) { }

  MArrayN<T>& operator = (const MArrayN<T>& a)
    {
      ArrayN<T>::operator = (a);
      return *this;
    }
};

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
