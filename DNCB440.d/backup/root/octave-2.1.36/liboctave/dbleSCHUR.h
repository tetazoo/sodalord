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

#if !defined (octave_SCHUR_h)
#define octave_SCHUR_h 1

#if defined (__GNUG__)
#pragma interface
#endif

#include <iostream>
#include <string>

#include "dMatrix.h"

class
SCHUR
{
public:

  SCHUR (void)
    : schur_mat (), unitary_mat () { }

  SCHUR (const Matrix& a, const std::string& ord)
    : schur_mat (), unitary_mat ()
      {
        init (a, ord);
      }

  SCHUR (const Matrix& a, const std::string& ord, int& info)
    : schur_mat (), unitary_mat ()
      {
        info = init (a, ord);
      }

  SCHUR (const SCHUR& a)
    : schur_mat (a.schur_mat), unitary_mat (a.unitary_mat) { }

  SCHUR& operator = (const SCHUR& a)
    {
      if (this != &a)
	{
	  schur_mat = a.schur_mat;
	  unitary_mat = a.unitary_mat;
	}
      return *this;
    }

  ~SCHUR (void) { }

  Matrix schur_matrix (void) const { return schur_mat; }

  Matrix unitary_matrix (void) const { return unitary_mat; }

  friend std::ostream& operator << (std::ostream& os, const SCHUR& a);

  typedef int (*select_function) (const double&, const double&);

private:

  Matrix schur_mat;
  Matrix unitary_mat;

  select_function selector;

  int init (const Matrix& a, const std::string& ord);
};

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
