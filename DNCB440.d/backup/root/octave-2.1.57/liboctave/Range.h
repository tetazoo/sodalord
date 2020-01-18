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

#if !defined (octave_Range_h)
#define octave_Range_h 1

#if defined (__GNUG__) && defined (USE_PRAGMA_INTERFACE_IMPLEMENTATION)
#pragma interface
#endif

#include <iostream>
#include "dMatrix.h"

class
Range
{
 public:

  Range (void)
    : rng_base (-1), rng_limit (-1), rng_inc (-1), rng_nelem (-1), cache () { }

  Range (const Range& r)
    : rng_base (r.rng_base), rng_limit (r.rng_limit), rng_inc (r.rng_inc),
      rng_nelem (r.rng_nelem), cache () { }

  Range (double b, double l)
    : rng_base (b), rng_limit (l), rng_inc (1),
      rng_nelem (nelem_internal ()), cache () { }

  Range (double b, double l, double i)
    : rng_base (b), rng_limit (l), rng_inc (i),
      rng_nelem (nelem_internal ()), cache () { }

  double base (void) const { return rng_base; }
  double limit (void) const { return rng_limit; }
  double inc (void) const { return rng_inc; }
  int nelem (void) const { return rng_nelem; }

  bool all_elements_are_ints (void) const;

  Matrix matrix_value (void) const;

  double min (void) const;
  double max (void) const;

  void sort (void);

  void set_base (double b)
  {
    if (rng_base != b)
      {
	rng_base = b;
	clear_cache ();
      }
  }

  void set_limit (double l)
  {
    if (rng_limit != l)
      {
	rng_limit = l;
	clear_cache ();
      }
  }

  void set_inc (double i)
  {
    if (rng_inc != i)
      {
	rng_inc = i;
	clear_cache ();
      }
  }

  friend std::ostream& operator << (std::ostream& os, const Range& r);
  friend std::istream& operator >> (std::istream& is, Range& r);

  void print_range (void);

 private:

  double rng_base;
  double rng_limit;
  double rng_inc;

  int rng_nelem;

  mutable Matrix cache;

  int nelem_internal (void) const;

  void clear_cache (void) const { cache.resize (0, 0); }
};

extern Range operator - (const Range& r);

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
