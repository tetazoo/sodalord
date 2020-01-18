## Copyright (C) 1996, 1997 John W. Eaton
##
## This file is part of Octave.
##
## Octave is free software; you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2, or (at your option)
## any later version.
##
## Octave is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
## General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with Octave; see the file COPYING.  If not, write to the Free
## Software Foundation, 59 Temple Place - Suite 330, Boston, MA
## 02111-1307, USA.

## -*- texinfo -*-
## @deftypefn {Mapping Function} {} gcd (@var{x}, @code{...})
## Compute the greatest common divisor of the elements of @var{x}, or the
## list of all the arguments.  For example,
##
## @example
## gcd (a1, ..., ak)
## @end example
##
## @noindent
## is the same as
##
## @example
## gcd ([a1, ..., ak])
## @end example
##
## An optional second return value, @var{v}
## contains an integer vector such that
##
## @example
## g = v(1) * a(k) + ... + v(k) * a(k)
## @end example
## @end deftypefn
## @seealso{lcm, min, max, ceil, and floor}

## Author: KH <Kurt.Hornik@ci.tuwien.ac.at>
## Created: 16 September 1994
## Adapted-By: jwe

function [g, v] = gcd (a, ...)

  if (nargin == 0)
    usage ("[g, v] = gcd (a, ...)");
  endif

  if (nargin > 1)
    va_start;
    for k = 2:nargin;
      a = [a, (va_arg ())];
    endfor
  endif

  if (round (a) != a)
    error ("gcd: all arguments must be integer");
  endif

  g = abs (a(1));
  v = sign (a(1));
  for k = 1:(length (a) - 1)
    x = [g, 1, 0];
    y = [(abs (a(k+1))), 0, 1];
    while (y(1) > 0)
      r = x - y * floor (x(1) / y(1));
      x = y;
      y = r;
    endwhile
    g = x(1);
    v = [x(2) * v, x(3) * (sign (a(k+1)))];
  endfor

endfunction
