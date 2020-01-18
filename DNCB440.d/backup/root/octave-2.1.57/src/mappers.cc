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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <cctype>
#include <cfloat>

#include "lo-ieee.h"
#include "lo-specfun.h"
#include "lo-mappers.h"

#include "defun.h"
#include "error.h"
#include "ov-mapper.h"
#include "variables.h"

// XXX FIXME XXX -- perhaps this could be avoided by determining
// whether the is* functions are actually functions or just macros.

static int
xabs (int c)
{
  return static_cast<unsigned char> (c);
}

static int
xisalnum (int c)
{
  return isalnum (c);
}

static int
xisalpha (int c)
{
  return isalpha (c);
}

static int
xisascii (int c)
{
  return isascii (c);
}

static int
xiscntrl (int c)
{
  return iscntrl (c);
}

static int
xisdigit (int c)
{
  return isdigit (c);
}

static int
xisgraph (int c)
{
  return isgraph (c);
}

static int
xislower (int c)
{
  return islower (c);
}

static int
xisprint (int c)
{
  return isprint (c);
}

static int
xispunct (int c)
{
  return ispunct (c);
}

static int
xisspace (int c)
{
  return isspace (c);
}

static int
xisupper (int c)
{
  return isupper (c);
}

static int
xisxdigit (int c)
{
  return isxdigit (c);
}

static int
xtoascii (int c)
{
  return toascii ((int) ((unsigned char) c));
}

static int
xtolower (int c)
{
  return tolower (c);
}

static int
xtoupper (int c)
{
  return toupper (c);
}

static double
xabs (const Complex& x)
{
  return (xisinf (x.real ()) || xisinf (x.imag ())) ? octave_Inf : abs (x);
}

static Complex
xconj (const Complex& x)
{
  return conj (x);
}

static double
xconj (double x)
{
  return x;
}

static double
ximag (const Complex& x)
{
  return x.imag ();
}

static double
xreal (const Complex& x)
{
  return x.real ();
}

void
install_mapper_functions (void)
{
  DEFUN_MAPPER (abs, xabs, 0, 0, fabs, xabs, 0, 0.0, 0.0, 1, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} abs (@var{z})\n\
Compute the magnitude of @var{z}, defined as\n\
@iftex\n\
@tex\n\
$|z| = \\sqrt{x^2 + y^2}$.\n\
@end tex\n\
@end iftex\n\
@ifinfo\n\
|@var{z}| = @code{sqrt (x^2 + y^2)}.\n\
@end ifinfo\n\
\n\
For example,\n\
\n\
@example\n\
@group\n\
abs (3 + 4i)\n\
     @result{} 5\n\
@end group\n\
@end example\n\
@end deftypefn");

  DEFUN_MAPPER (acos, 0, 0, 0, acos, 0, acos, -1.0, 1.0, 0, 1,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} acos (@var{x})\n\
Compute the inverse cosine of each element of @var{x}.\n\
@end deftypefn");

  DEFUN_MAPPER (acosh, 0, 0, 0, acosh, 0, acosh, 1.0, octave_Inf, 0, 1,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} acosh (@var{x})\n\
Compute the inverse hyperbolic cosine of each element of @var{x}.\n\
@end deftypefn");

  DEFUN_MAPPER (angle, 0, 0, 0, arg, arg, 0, 0.0, 0.0, 0, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} angle (@var{z})\n\
See arg.\n\
@end deftypefn");

  DEFUN_MAPPER (arg, 0, 0, 0, arg, arg, 0, 0.0, 0.0, 0, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} arg (@var{z})\n\
@deftypefnx {Mapping Function} {} angle (@var{z})\n\
Compute the argument of @var{z}, defined as\n\
@iftex\n\
@tex\n\
$\\theta = \\tan^{-1}(y/x)$.\n\
@end tex\n\
@end iftex\n\
@ifinfo\n\
@var{theta} = @code{atan (@var{y}/@var{x})}.\n\
@end ifinfo\n\
\n\
@noindent\n\
in radians. \n\
\n\
For example,\n\
\n\
@example\n\
@group\n\
arg (3 + 4i)\n\
     @result{} 0.92730\n\
@end group\n\
@end example\n\
@end deftypefn");

  DEFUN_MAPPER (asin, 0, 0, 0, asin, 0, asin, -1.0, 1.0, 0, 1,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} asin (@var{x})\n\
Compute the inverse sine of each element of @var{x}.\n\
@end deftypefn");

  DEFUN_MAPPER (asinh, 0, 0, 0, asinh, 0, asinh, 0.0, 0.0, 0, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} asinh (@var{x})\n\
Ompute the inverse hyperbolic sine of each element of @var{x}.\n\
@end deftypefn");

  DEFUN_MAPPER (atan, 0, 0, 0, atan, 0, atan, 0.0, 0.0, 0, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} atan (@var{x})\n\
Compute the inverse tangent of each element of @var{x}.\n\
@end deftypefn");

  DEFUN_MAPPER (atanh, 0, 0, 0, atanh, 0, atanh, -1.0, 1.0, 0, 1,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} atanh (@var{x})\n\
Compute the inverse hyperbolic tanget of each element of @var{x}.\n\
@end deftypefn");

  DEFUN_MAPPER (ceil, 0, 0, 0, ceil, 0, ceil, 0.0, 0.0, 0, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} ceil (@var{x})\n\
Return the smallest integer not less than @var{x}.  If @var{x} is\n\
complex, return @code{ceil (real (@var{x})) + ceil (imag (@var{x})) * I}.\n\
@end deftypefn");

  DEFUN_MAPPER (conj, 0, 0, 0, xconj, 0, xconj, 0.0, 0.0, 0, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} conj (@var{z})\n\
Return the complex conjugate of @var{z}, defined as\n\
@iftex\n\
@tex\n\
$\\bar{z} = x - iy$.\n\
@end tex\n\
@end iftex\n\
@ifinfo\n\
@code{conj (@var{z})} = @var{x} - @var{i}@var{y}.\n\
@end ifinfo\n\
@end deftypefn\n\
@seealso{real and imag}");

  DEFUN_MAPPER (cos, 0, 0, 0, cos, 0, cos, 0.0, 0.0, 0, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} cos (@var{x})\n\
Compute the cosine of each element of @var{x}.\n\
@end deftypefn");

  DEFUN_MAPPER (cosh, 0, 0, 0, cosh, 0, cosh, 0.0, 0.0, 0, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} cosh (@var{x})\n\
Compute the hyperbolic cosine of each element of @var{x}.\n\
@end deftypefn");

  DEFUN_MAPPER (erf, 0, 0, 0, erf, 0, 0, 0.0, 0.0, 0, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} erf (@var{z})\n\
Computes the error function,\n\
@iftex\n\
@tex\n\
$$\n\
 {\\rm erf} (z) = {2 \\over \\sqrt{\\pi}}\\int_0^z e^{-t^2} dt\n\
$$\n\
@end tex\n\
@end iftex\n\
@ifinfo\n\
\n\
@smallexample\n\
                         z\n\
                        /\n\
erf (z) = (2/sqrt (pi)) | e^(-t^2) dt\n\
                        /\n\
                     t=0\n\
@end smallexample\n\
@end ifinfo\n\
@end deftypefn\n\
@seealso{erfc and erfinv}");

  DEFUN_MAPPER (erfc, 0, 0, 0, erfc, 0, 0, 0.0, 0.0, 0, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} erfc (@var{z})\n\
Computes the complementary error function,\n\
@iftex\n\
@tex\n\
$1 - {\\rm erf} (z)$.\n\
@end tex\n\
@end iftex\n\
@ifinfo\n\
@code{1 - erf (@var{z})}.\n\
@end ifinfo\n\
@end deftypefn\n\
\n\
@seealso{erf and erfinv}");

  DEFUN_MAPPER (exp, 0, 0, 0, exp, 0, exp, 0.0, 0.0, 0, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} exp (@var{x})\n\
Compute the exponential of @var{x}.  To compute the matrix exponential,\n\
see @ref{Linear Algebra}.\n\
@end deftypefn");

  DEFUN_MAPPER (finite, 0, xfinite, xfinite, 0, 0, 0, 0.0, 0.0, 0, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} finite (@var{x})\n\
Return 1 for elements of @var{x} that are finite values and zero\n\
otherwise. For example,\n\
\n\
@example\n\
@group\n\
finite ([13, Inf, NaN])\n\
     @result{} [ 1, 0, 0 ]\n\
@end group\n\
@end example\n\
@end deftypefn");

  DEFUN_MAPPER (fix, 0, 0, 0, fix, 0, fix, 0.0, 0.0, 0, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} fix (@var{x})\n\
Truncate @var{x} toward zero.  If @var{x} is complex, return\n\
@code{fix (real (@var{x})) + fix (imag (@var{x})) * I}.\n\
@end deftypefn");

  DEFUN_MAPPER (floor, 0, 0, 0, floor, 0, floor, 0.0, 0.0, 0, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} floor (@var{x})\n\
Return the largest integer not greater than @var{x}.  If @var{x} is\n\
complex, return @code{floor (real (@var{x})) + floor (imag (@var{x})) * I}.\n\
@end deftypefn");

  DEFUN_MAPPER (gamma, 0, 0, 0, xgamma, 0, 0, 0.0, 0.0, 0, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} gamma (@var{z})\n\
Computes the Gamma function,\n\
@iftex\n\
@tex\n\
$$\n\
 \\Gamma (z) = \\int_0^\\infty t^{z-1} e^{-t} dt.\n\
$$\n\
@end tex\n\
@end iftex\n\
@ifinfo\n\
\n\
@example\n\
            infinity\n\
            /\n\
gamma (z) = | t^(z-1) exp (-t) dt.\n\
            /\n\
         t=0\n\
@end example\n\
@end ifinfo\n\
@end deftypefn\n\
\n\
@seealso{gammai and lgamma}");

  DEFUN_MAPPER (imag, 0, 0, 0, imag, ximag, 0, 0.0, 0.0, 0, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} imag (@var{z})\n\
Return the imaginary part of @var{z} as a real number.\n\
@end deftypefn\n\
\n\
@seealso{real and conj}");

  DEFUN_MAPPER (isalnum, xisalnum, 0, 0, 0, 0, 0, 0.0, 0.0, 0, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} isalnum (@var{s})\n\
Return 1 for characters that are letters or digits (@code{isalpha\n\
(@var{s})} or @code{isdigit (@var{s})} is true).\n\
@end deftypefn");

  DEFUN_MAPPER (isalpha, xisalpha, 0, 0, 0, 0, 0, 0.0, 0.0, 0, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} isalpha (@var{s})\n\
@deftypefnx {Mapping Function} {} isletter (@var{s})\n\
Return true for characters that are letters (@code{isupper (@var{s})}\n\
or @code{islower (@var{s})} is true).\n\
@end deftypefn");

  DEFUN_MAPPER (isascii, xisascii, 0, 0, 0, 0, 0, 0.0, 0.0, 0, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} isascii (@var{s})\n\
Return 1 for characters that are ASCII (in the range 0 to 127 decimal).\n\
@end deftypefn");

  DEFUN_MAPPER (iscntrl, xiscntrl, 0, 0, 0, 0, 0, 0.0, 0.0, 0, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} iscntrl (@var{s})\n\
Return 1 for control characters.\n\
@end deftypefn");

  DEFUN_MAPPER (isdigit, xisdigit, 0, 0, 0, 0, 0, 0.0, 0.0, 0, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} isdigit (@var{s})\n\
Return 1 for characters that are decimal digits.\n\
@end deftypefn");

  DEFUN_MAPPER (isinf, 0, xisinf, xisinf, 0, 0, 0, 0.0, 0.0, 0, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} isinf (@var{x})\n\
Return 1 for elements of @var{x} that are infinite and zero\n\
otherwise. For example,\n\
\n\
@example\n\
@group\n\
isinf ([13, Inf, NA, NaN])\n\
     @result{} [ 0, 1, 0, 0 ]\n\
@end group\n\
@end example\n\
@end deftypefn");

  DEFUN_MAPPER (isgraph, xisgraph, 0, 0, 0, 0, 0, 0.0, 0.0, 0, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} isgraph (@var{s})\n\
Return 1 for printable characters (but not the space character).\n\
@end deftypefn");

  DEFUN_MAPPER (islower, xislower, 0, 0, 0, 0, 0, 0.0, 0.0, 0, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} islower (@var{s})\n\
Return 1 for characters that are lower case letters.\n\
@end deftypefn");

  DEFUN_MAPPER (isna, 0, octave_is_NA, octave_is_NA, 0, 0, 0, 0.0, 0.0, 0, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} isna (@var{x})\n\
Return 1 for elements of @var{x} that are NA (missing) values and zero\n\
otherwise. For example,\n\
\n\
@example\n\
@group\n\
is_NA ([13, Inf, NA, NaN])\n\
     @result{} [ 0, 0, 1, 0 ]\n\
@end group\n\
@end example\n\
@end deftypefn");

  DEFUN_MAPPER (is_nan_or_na, 0, octave_is_NaN_or_NA,
		octave_is_NaN_or_NA, 0, 0, 0, 0.0, 0.0, 0, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} is_nan_or_na (@var{x})\n\
Return 1 for elements of @var{x} that are NaN or NA (missing) values\n\
and zero otherwise. For example,\n\
\n\
@example\n\
@group\n\
is_NAN_or_NA ([13, Inf, NA, NaN])\n\
     @result{} [ 0, 0, 1, 1 ]\n\
@end group\n\
@end example\n\
@end deftypefn");

  DEFUN_MAPPER (isnan, 0, xisnan, xisnan, 0, 0, 0, 0.0, 0.0, 0, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} isnan (@var{x})\n\
Return 1 for elements of @var{x} that are NaN values and zero\n\
otherwise. For example,\n\
\n\
@example\n\
@group\n\
isnan ([13, Inf, NA, NaN])\n\
     @result{} [ 0, 0, 0, 1 ]\n\
@end group\n\
@end example\n\
@end deftypefn");

  DEFUN_MAPPER (isprint, xisprint, 0, 0, 0, 0, 0, 0.0, 0.0, 0, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} isprint (@var{s})\n\
Return 1 for printable characters (including the space character).\n\
@end deftypefn");

  DEFUN_MAPPER (ispunct, xispunct, 0, 0, 0, 0, 0, 0.0, 0.0, 0, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} ispunct (@var{s})\n\
Return 1 for punctuation characters.\n\
@end deftypefn");

  DEFUN_MAPPER (isspace, xisspace, 0, 0, 0, 0, 0, 0.0, 0.0, 0, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} isspace (@var{s})\n\
Return 1 for whitespace characters (space, formfeed, newline,\n\
carriage return, tab, and vertical tab).\n\
@end deftypefn");

  DEFUN_MAPPER (isupper, xisupper, 0, 0, 0, 0, 0, 0.0, 0.0, 0, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} isupper (@var{s})\n\
Return 1 for upper case letters.\n\
@end deftypefn");

  DEFUN_MAPPER (isxdigit, xisxdigit, 0, 0, 0, 0, 0, 0.0, 0.0, 0, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} isxdigit (@var{s})\n\
Return 1 for characters that are hexadecimal digits.\n\
@end deftypefn");

  DEFUN_MAPPER (lgamma, 0, 0, 0, xlgamma, 0, 0, 0.0, 0.0, 0, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} lgamma (@var{a}, @var{x})\n\
@deftypefnx {Mapping Function} {} gammaln (@var{a}, @var{x})\n\
Return the natural logarithm of the gamma function.\n\
@end deftypefn\n\
@seealso{gamma and gammai}");

  DEFUN_MAPPER (log, 0, 0, 0, log, 0, log, 0.0, octave_Inf, 0, 1,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} log (@var{x})\n\
Compute the natural logarithm for each element of @var{x}.  To compute the\n\
matrix logarithm, see @ref{Linear Algebra}.\n\
@end deftypefn\n\
@seealso{log2, log10, logspace, and exp}");

  DEFUN_MAPPER (log10, 0, 0, 0, log10, 0, log10, 0.0, octave_Inf, 0, 1,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} log10 (@var{x})\n\
Compute the base-10 logarithm for each element of @var{x}.\n\
@end deftypefn\n\
@seealso{log, log2, logspace, and exp}");

  DEFUN_MAPPER (real, 0, 0, 0, real, xreal, 0, 0.0, 0.0, 0, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} real (@var{z})\n\
Return the real part of @var{z}.\n\
@end deftypefn\n\
@seealso{imag and conj}");

  DEFUN_MAPPER (round, 0, 0, 0, round, 0, round, 0.0, 0.0, 0, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} round (@var{x})\n\
Return the integer nearest to @var{x}.  If @var{x} is complex, return\n\
@code{round (real (@var{x})) + round (imag (@var{x})) * I}.\n\
@end deftypefn\n\
@seealso{rem}");

  DEFUN_MAPPER (sign, 0, 0, 0, signum, 0, signum, 0.0, 0.0, 0, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} sign (@var{x})\n\
Compute the @dfn{signum} function, which is defined as\n\
@iftex\n\
@tex\n\
$$\n\
{\\rm sign} (@var{x}) = \\cases{1,&$x>0$;\\cr 0,&$x=0$;\\cr -1,&$x<0$.\\cr}\n\
$$\n\
@end tex\n\
@end iftex\n\
@ifinfo\n\
\n\
@example\n\
           -1, x < 0;\n\
sign (x) =  0, x = 0;\n\
            1, x > 0.\n\
@end example\n\
@end ifinfo\n\
\n\
For complex arguments, @code{sign} returns @code{x ./ abs (@var{x})}.\n\
@end deftypefn");

  DEFUN_MAPPER (sin, 0, 0, 0, sin, 0, sin, 0.0, 0.0, 0, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} sin (@var{x})\n\
Compute the sin of each element of @var{x}.\n\
@end deftypefn");

  DEFUN_MAPPER (sinh, 0, 0, 0, sinh, 0, sinh, 0.0, 0.0, 0, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} sinh (@var{x})\n\
Compute the inverse hyperbolic sin of each element of @var{x}.\n\
@end deftypefn");

  DEFUN_MAPPER (sqrt, 0, 0, 0, sqrt, 0, sqrt, 0.0, octave_Inf, 0, 1,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} sqrt (@var{x})\n\
Compute the square root of @var{x}.  If @var{x} is negative, a complex\n\
result is returned.  To compute the matrix square root, see\n\
@ref{Linear Algebra}.\n\
@end deftypefn");

  DEFUN_MAPPER (tan, 0, 0, 0, tan, 0, tan, 0.0, 0.0, 0, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} tan (@var{z})\n\
Compute tanget of each element of @var{x}.\n\
@end deftypefn");

  DEFUN_MAPPER (tanh, 0, 0, 0, tanh, 0, tanh, 0.0, 0.0, 0, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} tanh (@var{x})\n\
Compute hyperbolic tangent of each element of @var{x}.\n\
@end deftypefn");

  DEFUN_MAPPER (toascii, xtoascii, 0, 0, 0, 0, 0, 0.0, 0.0, 1, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} toascii (@var{s})\n\
Return ASCII representation of @var{s} in a matrix.  For example,\n\
\n\
@example\n\
@group\n\
toascii (\"ASCII\")\n\
     @result{} [ 65, 83, 67, 73, 73 ]\n\
@end group\n\
\n\
@end example\n\
@end deftypefn");

  DEFUN_MAPPER (tolower, xtolower, 0, 0, 0, 0, 0, 0.0, 0.0, 2, 0,
    "-*- texinfo -*-\n\
@deftypefn {Mapping Function} {} tolower (@var{s})\n\
Return a copy of the string @var{s}, with each upper-case character\n\
replaced by the corresponding lower-case one; nonalphabetic characters\n\
are left unchanged.  For example,\n\
\n\
@example\n\
tolower (\"MiXeD cAsE 123\")\n\
     @result{} \"mixed case 123\"\n\
@end example\n\
@end deftypefn");

  DEFUN_MAPPER (toupper, xtoupper, 0, 0, 0, 0, 0, 0.0, 0.0, 2, 0,
    "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} toupper (@var{s})\n\
Return a copy of the string @var{s}, with each  lower-case character\n\
replaced by the corresponding upper-case one; nonalphabetic characters\n\
are left unchanged.  For example,\n\
\n\
@example\n\
@group\n\
toupper (\"MiXeD cAsE 123\")\n\
     @result{} \"MIXED CASE 123\"\n\
@end group\n\
@end example\n\
@end deftypefn");

  DEFALIAS (gammaln, lgamma);

  DEFALIAS (isfinite, finite);

  // Leave the previous new line, mkgendoc needs it!
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
