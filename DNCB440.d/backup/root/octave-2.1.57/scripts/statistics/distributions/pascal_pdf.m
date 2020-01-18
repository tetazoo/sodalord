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
## @deftypefn {Function File} {} pascal_pdf (@var{x}, @var{n}, @var{p})
## For each element of @var{x}, compute the probability density function
## (PDF) at @var{x} of the Pascal (negative binomial) distribution with
## parameters @var{n} and @var{p}.
##
## The number of failures in a Bernoulli experiment with success
## probability @var{p} before the @var{n}-th success follows this
## distribution. 
## @end deftypefn

## Author: KH <Kurt.Hornik@ci.tuwien.ac.at>
## Description: PDF of the Pascal (negative binomial) distribution

function pdf = pascal_pdf (x, n, p)

  if (nargin != 3)
    usage ("pascal_pdf (x, n, p)");
  endif

  [retval, x, n, p] = common_size (x, n, p);
  if (retval > 0)
    error ("pascal_pdf: x, n and p must be of common size or scalar");
  endif

  [r, c] = size (x);
  s = r * c;
  x   = reshape (x, 1, s);
  n   = reshape (n, 1, s);
  p   = reshape (p, 1, s);
  cdf = zeros (1, s);

  k = find (isnan (x) | (n < 1) | (n == Inf) | (n != round (n))
	    | (p < 0) | (p > 1));
  if (any (k))
    pdf(k) = NaN * ones (1, length (k));
  endif

  ## Just for the fun of it ...
  k = find ((x == Inf) & (n > 0) & (n < Inf) & (n == round (n))
	    & (p == 0));
  if (any (k))
    pdf(k) = ones (1, length (k));
  endif

  k = find ((x >= 0) & (x < Inf) & (x == round (x)) & (n > 0)
	    & (n < Inf) & (n == round (n)) & (p > 0) & (p <= 1));
  if (any (k))
    pdf(k) = bincoeff (-n(k), x(k)) .* (p(k) .^ n(k)) .* ((p(k) - 1) .^ x(k));
  endif

  pdf = reshape (pdf, r, c);

endfunction
