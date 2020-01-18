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

#if !defined (octave_Quad_h)
#define octave_Quad_h 1

#if defined (__GNUG__) && defined (USE_PRAGMA_INTERFACE_IMPLEMENTATION)
#pragma interface
#endif

#include <cfloat>
#include <cmath>

#include "dColVector.h"

#if !defined (octave_Quad_typedefs)
#define octave_Quad_typedefs 1

typedef double (*integrand_fcn) (double x);

#endif

// XXX FIXME XXX -- would be nice to not have to have this global
// variable.
// Nonzero means an error occurred in the calculation of the integrand
// function, and the user wants us to quit.
extern int quad_integration_error;

#include "Quad-opts.h"

class
Quad : public Quad_options
{
 public:

  Quad (integrand_fcn fcn)
    : Quad_options (), f (fcn) { }

  virtual ~Quad (void) { }

  virtual double integrate (void)
    {
      int ier, neval;
      double abserr;
      return do_integrate (ier, neval, abserr);
    }

  virtual double integrate (int& ier)
    {
      int neval;
      double abserr;
      return do_integrate (ier, neval, abserr);
    }

  virtual double integrate (int& ier, int& neval)
    {
      double abserr;
      return do_integrate (ier, neval, abserr);
    }

  virtual double integrate (int& ier, int& neval, double& abserr)
    {
      return do_integrate (ier, neval, abserr);
    }

  virtual double do_integrate (int& ier, int& neval, double& abserr) = 0;

 protected:

  integrand_fcn f;
};

class
DefQuad : public Quad
{
 public:

  DefQuad (integrand_fcn fcn)
    : Quad (fcn), lower_limit (0.0), upper_limit (1.0), singularities () { }

  DefQuad (integrand_fcn fcn, double ll, double ul)
    : Quad (fcn), lower_limit (ll), upper_limit (ul), singularities () { }

  DefQuad (integrand_fcn fcn, double ll, double ul,
	   const ColumnVector& sing)
    : Quad (fcn), lower_limit (ll), upper_limit (ul),
      singularities (sing) { }

  DefQuad (integrand_fcn fcn, const ColumnVector& sing)
    : Quad (fcn), lower_limit (0.0), upper_limit (1.0),
      singularities (sing) { }

  ~DefQuad (void) { }

  double do_integrate (int& ier, int& neval, double& abserr);

 private:

  double lower_limit;
  double upper_limit;

  ColumnVector singularities;
};

class
IndefQuad : public Quad
{
 public:

  enum IntegralType { bound_to_inf, neg_inf_to_bound, doubly_infinite };

  IndefQuad (integrand_fcn fcn)
    : Quad (fcn), bound (0.0), type (bound_to_inf) { }

  IndefQuad (integrand_fcn fcn, double b, IntegralType t)
    : Quad (fcn), bound (b), type (t) { }

  ~IndefQuad (void) { }

  double do_integrate (int& ier, int& neval, double& abserr);

 private:

  double bound;
  IntegralType type;
  int integration_error;
};

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
