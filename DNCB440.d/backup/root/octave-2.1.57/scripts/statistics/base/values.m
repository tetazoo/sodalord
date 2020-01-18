## Copyright (C) 1995, 1996, 1997  Kurt Hornik
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
## @deftypefn {Function File} {} values (@var{x})
## Return the different values in a column vector, arranged in ascending
## order.
## @end deftypefn

## Author: KH <Kurt.Hornik@ci.tuwien.ac.at>
## Description: Extract unique elements

function v = values (x)

  if (nargin != 1)
    usage ("values (x)");
  endif

  if (! (isvector (x)))
    error ("values: x must be a vector");
  endif

  i = any (isnan (x));
  x = x(find(!isnan (x)));      # HACK!
  n = length (x);
  x = reshape (x, n, 1);
  s = sort (x);
  v = s([1; (find (s(2:n) > s(1:n-1)) + 1)]);
  if (i)
    v = [v; NaN];
  endif

endfunction
