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

#if !defined (octave_ODE_h)
#define octave_ODE_h 1

#include "ODEFunc.h"
#include "base-de.h"

class
ODE : public base_diff_eqn, public ODEFunc
{
public:

  ODE (void)
    : base_diff_eqn (), ODEFunc () { }

  ODE (const ColumnVector& state, double time, const ODEFunc& f)
    : base_diff_eqn (state, time), ODEFunc (f) { }

  ODE (const ODE& a)
    : base_diff_eqn (a), ODEFunc (a) { }

  ODE& operator = (const ODE& a)
    {
      if (this != &a)
	{
	  base_diff_eqn::operator = (a);
	  ODEFunc::operator = (a);
	}
      return *this;
    }

  ~ODE (void) { }
};

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
