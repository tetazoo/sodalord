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

#if !defined (octave_Array2_h)
#define octave_Array2_h 1

#if defined (__GNUG__) && defined (USE_PRAGMA_INTERFACE_IMPLEMENTATION)
#pragma interface
#endif

#include <cassert>
#include <climits>
#include <cmath>
#include <cstdlib>

#include "Array.h"
#include "lo-error.h"

class idx_vector;

// Two dimensional array class.

template <class T>
class
Array2 : public Array<T>
{
protected:

  static int get_size (int r, int c) { return Array<T>::get_size (r, c); }

  Array2 (T *d, int r, int c) : Array<T> (d, dim_vector (r, c)) { }

public:

  Array2 (void) : Array<T> (dim_vector (0, 0)) { }

  Array2 (int r, int c) : Array<T> (dim_vector (r, c)) { }

  Array2 (int r, int c, const T& val)
    : Array<T> (dim_vector (r, c), val) { }

  Array2 (const Array2<T>& a) : Array<T> (a, a.dims ()) { }

  Array2 (const Array<T>& a, int r, int c)
    : Array<T> (a, dim_vector (r, c)) { }

  ~Array2 (void) { }

  Array2<T>& operator = (const Array2<T>& a)
    {
      if (this != &a)
	Array<T>::operator = (a);

      return *this;
    }

  void resize (int r, int c) { this->resize_no_fill (r, c); }

  void resize (int r, int c, const T& val)
    { this->resize_and_fill (r, c, val); }

  Array2<T>& insert (const Array2<T>& a, int r, int c)
    {
      Array<T>::insert (a, r, c);
      return *this;
    }

  Array2<T> transpose (void) const
    {
      Array<T> tmp = Array<T>::transpose ();
      return Array2<T> (tmp, tmp.rows (), tmp.columns ());
    }

  Array2<T> index (idx_vector& i, int resize_ok = 0,
		   const T& rfv = resize_fill_value (T ())) const
    {
      Array<T> tmp = Array<T>::index (i, resize_ok, rfv);
      return Array2<T> (tmp, tmp.rows (), tmp.columns ());
    }

  Array2<T> index (idx_vector& i, idx_vector& j, int resize_ok = 0,
		   const T& rfv = resize_fill_value (T ())) const
    {
      Array<T> tmp = Array<T>::index (i, j, resize_ok, rfv);
      return Array2<T> (tmp, tmp.rows (), tmp.columns ());
    }
};

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
