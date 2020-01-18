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
## @deftypefn {Function File} {} geometric_pdf (@var{x}, @var{p})
## For each element of @var{x}, compute the probability density function
## (PDF) at @var{x} of the geometric distribution with parameter @var{p}.
## @end deftypefn

## Author: KH <Kurt.Hornik@ci.tuwien.ac.at>
## Description: PDF of the geometric distribution

function pdf = geometric_pdf (x, p)

  if (nargin != 2)
    usage ("geometric_pdf (x, p)");
  endif

  [retval, x, p] = common_size (x, p);
  if (retval > 0)
    error ("geometric_pdf: x and p must be of common size or scalar");
  endif

  [r, c] = size (x);
  s = r * c;
  x   = reshape (x, 1, s);
  p   = reshape (p, 1, s);
  cdf = zeros (1, s);

  k = find (isnan (x) | !(p >= 0) | !(p <= 1));
  if (any (k))
    pdf(k) = NaN * ones (1, length (k));
  endif

  ## Just for the fun of it ...
  k = find ((x == Inf) & (p == 0));
  if (any (k))
    pdf(k) = ones (1, length (k));
  endif

  k = find ((x >= 0) & (x < Inf) & (x == round (x)) & (p > 0) & (p <= 1));
  if (any (k))
    pdf(k) = p(k) .* ((1 - p(k)) .^ x(k));
  endif

  pdf = reshape (pdf, r, c);

endfunction
