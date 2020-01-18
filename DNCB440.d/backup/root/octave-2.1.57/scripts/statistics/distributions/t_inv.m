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
## @deftypefn {Function File} {} t_inv (@var{x}, @var{n})
## For each component of @var{x}, compute the quantile (the inverse of
## the CDF) at @var{x} of the t (Student) distribution with parameter
## @var{n}.
## @end deftypefn

## For very large n, the "correct" formula does not really work well,
## and the quantiles of the standard normal distribution are used
## directly.

## Author: KH <Kurt.Hornik@ci.tuwien.ac.at>
## Description: Quantile function of the t distribution

function inv = t_inv (x, n)

  if (nargin != 2)
    usage ("t_inv (x, n)");
  endif

  [retval, x, n] = common_size (x, n);
  if (retval > 0)
    error ("t_inv: x and n must be of common size or scalar");
  endif

  [r, c] = size (x);
  s = r * c;
  x = reshape (x, 1, s);
  n = reshape (n, 1, s);
  inv = zeros (1, s);

  k = find ((x < 0) | (x > 1) | isnan (x) | !(n > 0));
  if (any (k))
    inv(k) = NaN * ones (1, length (k));
  endif

  k = find ((x == 0) & (n > 0));
  if (any (k))
    inv(k) = (-Inf) * ones (1, length (k));
  endif

  k = find ((x == 1) & (n > 0));
  if (any (k))
    inv(k) = Inf * ones (1, length (k));
  endif

  k = find ((x > 0) & (x < 1) & (n > 0) & (n < 10000));
  if (any (k))
    inv(k) = (sign (x(k) - 1/2)
	      .* sqrt (n(k) .* (1 ./ beta_inv (2*min (x(k), 1 - x(k)),
					       n(k)/2, 1/2) - 1)));
  endif

  ## For large n, use the quantiles of the standard normal
  k = find ((x > 0) & (x < 1) & (n >= 10000));
  if (any (k))
    inv(k) = stdnormal_inv (x(k));
  endif

  inv = reshape (inv, r, c);

endfunction