/*

Copyright (C) 2002 John W. Eaton

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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <float.h>
#include <math.h>

#if defined (HAVE_FLOATINGPOINT_H)
#include <floatingpoint.h>
#endif

#if defined (HAVE_IEEEFP_H)
#include <ieeefp.h>
#endif

#if defined (HAVE_NAN_H)
#if defined (SCO)
#define _IEEE 1
#endif
#include <nan.h>
#if defined (SCO)
#undef _IEEE
#endif
#endif

#include "lo-ieee.h"

#if defined (_AIX) && defined (__GNUG__)
#undef finite
#define finite(x) ((x) < DBL_MAX && (x) > -DBL_MAX)
#endif

/* Octave's idea of infinity.  */
double octave_Inf;

/* Octave's idea of a missing value.  */
double octave_NA;

/* Octave's idea of not a number.  */
double octave_NaN;

int lo_ieee_hw;
int lo_ieee_lw;

#if defined (SCO)

int
isnan (double x)
{
  return (IsNANorINF (x) && NaN (x) && ! IsINF (x)) ? 1 : 0;
}

int
isinf (double x)
{
  return (IsNANorINF (x) && IsINF (x)) ? 1 : 0;
}

#endif

int
lo_ieee_isnan (double x)
{
#if defined (HAVE_ISNAN)
  return isnan (x) ? ! lo_ieee_is_NA (x) : 0;
#else
  return 0;
#endif
}

int
lo_ieee_finite (double x)
{
#if defined (HAVE_FINITE)
  return finite (x) != 0 && ! lo_ieee_is_NaN_or_NA (x);
#elif defined (HAVE_ISINF)
  return (! isinf (x) && ! lo_ieee_is_NaN_or_NA (x));
#else
  return ! lo_ieee_is_NaN_or_NA (x);
#endif
}

int
lo_ieee_isinf (double x)
{
#if defined (HAVE_ISINF)
  return isinf (x);
#elif defined (HAVE_FINITE)
  return (! (finite (x) || lo_ieee_is_NaN_or_NA (x)));
#else
  return 0;
#endif
}

int
lo_ieee_is_NA (double x)
{
#if defined HAVE_ISNAN
  lo_ieee_double t;
  t.value = x;
  return (isnan (x) && t.word[lo_ieee_lw] == LO_IEEE_NA_LW) ? 1 : 0;
#else
  return 0;
#endif
}

int
lo_ieee_is_NaN_or_NA (double x)
{
  /* Although NA really is an IEEE NaN value, lo_ieee_isnan pretends
     it is not, so we much check both...  */

  return lo_ieee_isnan (x) || lo_ieee_is_NA (x);
}

double
lo_ieee_inf_value (void)
{
  return octave_Inf;
}

double
lo_ieee_na_value (void)
{
  return octave_NA;
}

double
lo_ieee_nan_value (void)
{
  return octave_NaN;
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
