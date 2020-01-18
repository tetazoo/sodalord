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

#if !defined (octave_HESS_h)
#define octave_HESS_h 1

#if defined (__GNUG__)
#pragma interface
#endif

#include <iostream>

#include "dMatrix.h"

class
HESS
{
public:

  HESS (void) : hess_mat (), unitary_hess_mat () { }

  HESS (const Matrix& a) { init (a); }

  HESS (const Matrix& a, int& info) { info = init (a); }

  HESS (const HESS& a)
    : hess_mat (a.hess_mat), unitary_hess_mat (a.unitary_hess_mat) { }

  HESS& operator = (const HESS& a)
    {
      if (this != &a)
	{
	  hess_mat = a.hess_mat;
	  unitary_hess_mat = a.unitary_hess_mat;
	}
      return *this;
    }

  ~HESS (void) { }

  Matrix hess_matrix (void) const { return hess_mat; }

  Matrix unitary_hess_matrix (void) const { return unitary_hess_mat; }

  friend std::ostream& operator << (std::ostream& os, const HESS& a);

private:

  Matrix hess_mat;
  Matrix unitary_hess_mat;

  int init (const Matrix& a);
};

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
