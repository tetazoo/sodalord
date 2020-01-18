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
## @deftypefn {Function File} {} geometric_rnd (@var{p}, @var{r}, @var{c})
## Return an @var{r} by @var{c} matrix of random samples from the
## geometric distribution with parameter @var{p}, which must be a scalar
## or of size @var{r} by @var{c}.
##
## If @var{r} and @var{c} are omitted, the size of the result matrix is
## the size of @var{p}.
## @end deftypefn

## Author: KH <Kurt.Hornik@ci.tuwien.ac.at>
## Description: Random deviates from the geometric distribution

function rnd = geometric_rnd (p, r, c)

  if (nargin == 3)
    if (! (isscalar (r) && (r > 0) && (r == round (r))))
      error ("geometric_rnd: r must be a positive integer");
    endif
    if (! (isscalar (c) && (c > 0) && (c == round (c))))
      error ("geometric_rnd: c must be a positive integer");
    endif
    [retval, p] = common_size (p, zeros (r, c));
    if (retval > 0)
      error ("geometric_rnd: p must be scalar or of size %d by %d", r, c);
    endif
  elseif (nargin != 1)
    usage ("geometric_rnd (p, r, c)");
  endif

  [r, c] = size (p);
  s = r * c;
  p = reshape (p, 1, s);
  rnd = zeros (1, s);

  k = find (!(p >= 0) | !(p <= 1));
  if (any (k))
    rnd(k) = NaN * ones (1, length (k));
  endif

  k = find (p == 0);
  if (any (k))
    rnd(k) = Inf * ones (1, length (k));
  endif

  k = find ((p > 0) & (p < 1));
  if (any (k))
    rnd(k) = floor (log (rand (1, length (k))) ./ log (1 - p(k)));
  endif

  rnd = reshape (rnd, r, c);

endfunction
