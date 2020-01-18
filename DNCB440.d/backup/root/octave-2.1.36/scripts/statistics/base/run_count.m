## Copyright (C) 1995, 1996, 1997  Friedrich Leisch
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
## @deftypefn {Function File} {} run_count (@var{x}, @var{n})
## Count the upward runs in the columns of @var{x} of length 1, 2, ...,
## @var{n}-1 and greater than or equal to @var{n}.
## @end deftypefn

## Author: FL <Friedrich.Leisch@ci.tuwien.ac.at>
## Description: Count upward runs

function retval = run_count (x, n)

  [xr, xc] = size(x);

  tmp = zeros (xr,xc);
  retval = zeros (n, xc);

  for j = 1 : xc
    run = 1;
    count = 1;

    for k = 2 : xr

      if x(k, j) < x(k-1, j)
        tmp(run, j) = count;
        run = run + 1;
        count = 0;
      endif

      count = count + 1;

    endfor

    tmp(run, j) = count;

  endfor

  for k=1 : (n-1)
    retval(k, :) = sum (tmp == k);
  endfor
  retval(n, :) = sum (tmp >= n);

endfunction
