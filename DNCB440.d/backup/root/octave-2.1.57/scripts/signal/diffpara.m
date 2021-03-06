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
## @deftypefn {Function File} {[@var{d}, @var{dd}]} = diffpara (@var{x}, @var{a}, @var{b})
## Return the estimator @var{d} for the differencing parameter of an
## integrated time series.
##
## The frequencies from @math{[2*pi*a/t, 2*pi*b/T]} are used for the
## estimation.  If @var{b} is omitted, the interval
## @math{[2*pi/T, 2*pi*a/T]} is used.  If both @var{b} and @var{a} are
## omitted then @math{a = 0.5 * sqrt (T)} and @math{b = 1.5 * sqrt (T)}
## is used, where @math{T} is the sample size.  If @var{x} is a matrix,
## the differencing parameter of each column is estimated.
##
## The estimators for all frequencies in the intervals
## described above is returned in @var{dd}.  The value of @var{d} is
## simply the mean of @var{dd}.
##
## Reference: Brockwell, Peter J. & Davis, Richard A. Time Series:
## Theory and Methods Springer 1987.
## @end deftypefn

## Author: FL <Friedrich.Leisch@ci.tuwien.ac.at>
## Description: Estimate the fractional differencing parameter

function [d, D] = diffpara (X, a, b)

  if ((nargin < 1) || (nargin > 3))
    usage ("[d, D] = diffpara (X, a, b)");
  else
    if (isvector (X))
      n = length (X);
      k = 1;
      X = reshape (X, n, 1);
    else
      [n, k] = size(X);
    endif
    if (nargin == 1)
      a = 0.5 * sqrt (n);
      b = 1.5 * sqrt (n);
    elseif (nargin == 2)
      b = a;
      a = 1;
    endif
  endif

  if (! (isscalar (a) && isscalar (b)))
    error ("diffpara: a and b must be scalars");
  endif

  D = zeros (b - a + 1, k);

  for l = 1:k

    w = 2 * pi * (1 : n-1) / n;

    x = 2 * log (abs (1 - exp (-i*w)));
    y = log (periodogram (X(2:n,l)));

    x = center (x);
    y = center (y);

    for m = a:b
      D(m-a+1) = - x(1:m) * y(1:m) / sumsq (x(1:m));
    endfor

  endfor

  d = mean (D);

endfunction

