// Template array classes
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

#if !defined (octave_Array3_h)
#define octave_Array3_h 1

#if defined (__GNUG__) && defined (USE_PRAGMA_INTERFACE_IMPLEMENTATION)
#pragma interface
#endif

#include <cassert>
#include <cstdlib>

#include "Array.h"
#include "lo-error.h"

class idx_vector;

// Three dimensional array class.

template <class T>
class
Array3 : public Array<T>
{
protected:

  static int get_size (int r, int c, int p)
    { return Array<T>::get_size (r, c, p); }

  Array3 (T *d, int r, int c, int p) : Array<T> (d, dim_vector (r, c, p)) { }

public:

  Array3 (void) : Array<T> (dim_vector (0, 0, 0)) { }

  Array3 (int r, int c, int p) : Array<T> (dim_vector (r, c, p)) { }

  Array3 (int r, int c, int p, const T& val)
    : Array<T> (dim_vector (r, c, p), val) { }

  Array3 (const Array3<T>& a)
    : Array<T> (a, a.dims ()) { }

  Array3 (const Array<T>& a, int r, int c, int p)
    : Array<T> (a, dim_vector (r, c, p)) { }

  ~Array3 (void) { }

  Array3<T>& operator = (const Array3<T>& a)
    {
      if (this != &a)
	Array<T>::operator = (a);

      return *this;
    }

  void resize (int r, int c, int p) { this->resize_no_fill (r, c, p); }

  void resize (int r, int c, int p, const T& val)
    { this->resize_and_fill (r, c, p, val); }
};

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
