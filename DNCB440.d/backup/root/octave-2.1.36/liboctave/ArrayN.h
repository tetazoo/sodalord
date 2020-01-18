// Template array classes
/*

Copyright (C) 2000 John W. Eaton

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

#if !defined (octave_ArrayN_h)
#define octave_ArrayN_h 1

#if defined (__GNUG__)
#pragma interface
#endif

#include <iostream>

#include <cassert>
#include <climits>
#include <cmath>
#include <cstdlib>

#include "Array.h"
#include "lo-error.h"

class idx_vector;

// N-dimensional array class.

template <class T>
class
ArrayN : public Array<T>
{
protected:

  ArrayN (T *d, const Array<int>& dims) : Array<T> (d, get_size (dims))
    {
      dimensions = dims;
      set_max_indices (dimensions.length ());
    }

public:

  static int get_size (const Array<int>& dims);

  // These really need to be protected (and they will be in the
  // future, so don't depend on them being here!), but they can't be
  // until template friends work correctly in g++.

  Array<int> dimensions;

  ArrayN (void) : Array<T> () { }

  ArrayN (const Array<int>& dims) : Array<T> (get_size (dims))
    {
      dimensions = dims;
      set_max_indices (dimensions.length ());
    }

  ArrayN (const Array<int>& dims, const T& val)
    : Array<T> (get_size (dims), val)
    {
      dimensions = dims;
      set_max_indices (dimensions.length ());
    }

  ArrayN (const ArrayN<T>& a) : Array<T> (a)
    {
      dimensions = a.dimensions;
      set_max_indices (dimensions.length ());
    }

  ArrayN (const Array<T>& a, const Array<int>& dims) : Array<T> (a)
    {
      dimensions = dims;
      set_max_indices (dimensions.length ());
    }

  ~ArrayN (void) { }

  ArrayN<T>& operator = (const ArrayN<T>& a)
    {
      if (this != &a && rep != a.rep)
	{
	  Array<T>::operator = (a);
	  dimensions = a.dimensions;
	}

      return *this;
    }

  int compute_index (const Array<int>& idx) const;

  Array<int> dims (void) const { return dimensions; }

  T range_error (const char *fcn, const Array<int>& idx) const;
  T& range_error (const char *fcn, const Array<int>& idx);

  // No checking of any kind, ever.

  T& xelem (const Array<int>& idx)
    { return Array<T>::xelem (compute_index (idx)); }

  T xelem (const Array<int>& idx) const
    { return Array<T>::xelem (compute_index (idx)); }

  // Note that the following element selection methods don't use
  // xelem() because they need to make use of the code in
  // Array<T>::elem() that checks the reference count.

  T& checkelem (const Array<int>& idx)
    {
      int i = compute_index (idx);

      if (i < 0)
	return range_error ("ArrayN<T>::checkelem", idx);
      else
	return Array<T>::elem (i);
    }

  T& elem (const Array<int>& idx)
    {
      int i = compute_index (idx);

      return Array<T>::elem (i);
    }

#if defined (BOUNDS_CHECKING)
  T& operator () (const Array<int>& idx) { return checkelem (idx); }
#else
  T& operator () (const Array<int>& idx) { return elem (idx); }
#endif

  T checkelem (const Array<int>& idx) const
    {
      int i = compute_index (idx);

      if (i < 0)
	return range_error ("ArrayN<T>::checkelem", idx);
      else
	return Array<T>::elem (i);
    }

  T elem (const Array<int>& idx) const
    {
      int i = compute_index (idx);

      return Array<T>::elem (i);
    }

#if defined (BOUNDS_CHECKING)
  T operator () (const Array<int>& idx) const { return checkelem (idx); }
#else
  T operator () (const Array<int>& idx) const { return elem (idx); }
#endif

  void resize (const Array<int>& dims);
  void resize (const Array<int>& dims, const T& val);

  ArrayN<T>& insert (const ArrayN<T>& a, const Array<int>& dims);

#ifdef HEAVYWEIGHT_INDEXING
  void maybe_delete_elements (Array<idx_vector>& idx);

  ArrayN<T> value (void);

  ArrayN<T> index (idx_vector& idx) const;

  ArrayN<T> index (Array<idx_vector>& idx) const;
#endif
};

template <class LT, class RT>
int
assign (ArrayN<LT>& lhs, const ArrayN<RT>& rhs, const LT& resize_fill_value);

template <class LT, class RT>
int
assign (ArrayN<LT>& lhs, const ArrayN<RT>& rhs)
{
  return assign (lhs, rhs, static_cast<LT> (0));
}

template <class T>
std::ostream&
operator << (std::ostream&, const ArrayN<T>&);

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
