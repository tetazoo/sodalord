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

#if !defined (octave_QR_h)
#define octave_QR_h 1

#if defined (__GNUG__) && defined (USE_PRAGMA_INTERFACE_IMPLEMENTATION)
#pragma interface
#endif

#include <iostream>

#include "dMatrix.h"

class
QR
{
public:

  enum type
    {
      std,
      raw,
      economy
    };

  QR (void) : q (), r () { }

  QR (const Matrix&, QR::type = QR::std);

  QR (const QR& a) : q (a.q), r (a.r) { }

  QR& operator = (const QR& a)
    {
      if (this != &a)
	{
	  q = a.q;
	  r = a.r;
	}
      return *this;
    }

  ~QR (void) { }

  void init (const Matrix&, QR::type);

  Matrix Q (void) const { return q; }

  Matrix R (void) const { return r; }

  friend std::ostream&  operator << (std::ostream&, const QR&);

protected:

  Matrix q;
  Matrix r;
};

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
