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

#if !defined (octave_CHOL_h)
#define octave_CHOL_h 1

#if defined (__GNUG__) && defined (USE_PRAGMA_INTERFACE_IMPLEMENTATION)
#pragma interface
#endif

#include <iostream>

#include "dMatrix.h"

class
CHOL
{
public:

  CHOL (void) : chol_mat () { }

  CHOL (const Matrix& a) { init (a); }

  CHOL (const Matrix& a, int& info) { info = init (a); }

  CHOL (const CHOL& a) : chol_mat (a.chol_mat) { }

  CHOL& operator = (const CHOL& a)
    {
      if (this != &a)
	chol_mat = a.chol_mat;

      return *this;
    }

  Matrix chol_matrix (void) const { return chol_mat; }

  friend std::ostream& operator << (std::ostream& os, const CHOL& a);

private:

  Matrix chol_mat;

  int init (const Matrix& a);
};

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
