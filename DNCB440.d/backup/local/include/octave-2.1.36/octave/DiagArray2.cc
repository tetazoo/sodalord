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

#if defined (__GNUG__)
#pragma implementation
#endif

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <cassert>

#include <iostream>

#include "DiagArray2.h"

#include "lo-error.h"

// A two-dimensional array with diagonal elements only.

#if 0
template <class T>
T&
DiagArray2<T>::elem (int r, int c)
{
  static T foo (0);
  return (r == c) ? Array<T>::xelem (r) : foo;
}

template <class T>
T&
DiagArray2<T>::checkelem (int r, int c)
{
  static T foo (0);
  if (r < 0 || c < 0 || r >= nr || c >= nc)
    {
      (*current_liboctave_error_handler) ("range error");
      return foo;
    }
  return (r == c) ? Array<T>::xelem (r) : foo;
}

template <class T>
T&
DiagArray2<T>::operator () (int r, int c)
{
  static T foo (0);
  if (r < 0 || c < 0 || r >= nr || c >= nc)
    {
      (*current_liboctave_error_handler) ("range error");
      return foo;
    }
  return (r == c) ? Array<T>::xelem (r) : foo;
}
#endif

template <class T>
T
DiagArray2<T>::elem (int r, int c) const
{
  return (r == c) ? Array<T>::xelem (r) : T (0);
}

template <class T>
T
DiagArray2<T>::checkelem (int r, int c) const
{
  if (r < 0 || c < 0 || r >= nr || c >= nc)
    {
      (*current_liboctave_error_handler) ("range error");
      return T ();
    }
  return (r == c) ? Array<T>::xelem (r) : T (0);
}

template <class T>
T
DiagArray2<T>::operator () (int r, int c) const
{
  if (r < 0 || c < 0 || r >= nr || c >= nc)
    {
      (*current_liboctave_error_handler) ("range error");
      return T ();
    }
  return (r == c) ? Array<T>::xelem (r) : T (0);
}

template <class T>
T&
DiagArray2<T>::xelem (int r, int c)
{
  static T foo (0);
  return (r == c) ? Array<T>::xelem (r) : foo;
}

template <class T>
T
DiagArray2<T>::xelem (int r, int c) const
{
  return (r == c) ? Array<T>::xelem (r) : T (0);
}

template <class T>
void
DiagArray2<T>::resize (int r, int c)
{
  if (r < 0 || c < 0)
    {
      (*current_liboctave_error_handler) ("can't resize to negative dimensions");
      return;
    }

  if (r == dim1 () && c == dim2 ())
    return;

  ArrayRep *old_rep = rep;
  const T *old_data = data ();
  int old_len = length ();

  int new_len = r < c ? r : c;

  rep = new ArrayRep (new_len);

  nr = r;
  nc = c;

  if (old_data && old_len > 0)
    {
      int min_len = old_len < new_len ? old_len : new_len;

      for (int i = 0; i < min_len; i++)
	xelem (i, i) = old_data[i];
    }

  if (--old_rep->count <= 0)
    delete old_rep;
}

template <class T>
void
DiagArray2<T>::resize (int r, int c, const T& val)
{
  if (r < 0 || c < 0)
    {
      (*current_liboctave_error_handler) ("can't resize to negative dimensions");
      return;
    }

  if (r == dim1 () && c == dim2 ())
    return;

  ArrayRep *old_rep = rep;
  const T *old_data = data ();
  int old_len = length ();

  int new_len = r < c ? r : c;

  rep = new ArrayRep (new_len);

  nr = r;
  nc = c;

  int min_len = old_len < new_len ? old_len : new_len;

  if (old_data && old_len > 0)
    {
      for (int i = 0; i < min_len; i++)
	xelem (i, i) = old_data[i];
    }

  for (int i = min_len; i < new_len; i++)
    xelem (i, i) = val;

  if (--old_rep->count <= 0)
    delete old_rep;
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
