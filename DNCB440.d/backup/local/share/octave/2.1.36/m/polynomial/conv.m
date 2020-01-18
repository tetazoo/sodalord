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
## @deftypefn {Function File} {} conv (@var{a}, @var{b})
## Convolve two vectors.
##
## @code{y = conv (a, b)} returns a vector of length equal to
## @code{length (a) + length (b) - 1}.
## If @var{a} and @var{b} are polynomial coefficient vectors, @code{conv}
## returns the coefficients of the product polynomial.
## @end deftypefn
## @seealso{deconv, poly, roots, residue, polyval, polyderiv, and polyinteg}

## Author: Tony Richardson <arichard@stark.cc.oh.us>
## Created: June 1994
## Adapted-By: jwe

function y = conv (a, b)

  if (nargin != 2)
    usage ("conv(a, b)");
  endif

  if (! (is_vector (a) && is_vector (b)))
    error("conv: both arguments must be vectors");
  endif

  la = length (a);
  lb = length (b);

  ly = la + lb - 1;

  ## Ensure that both vectors are row vectors.
  if (rows (a) > 1)
    a = reshape (a, 1, la);
  endif
  if (rows (b) > 1)
    b = reshape (b, 1, lb);
  endif

  ## Use the shortest vector as the coefficent vector to filter.
  if (la < lb)
    if (ly > lb)
      x = [b, (zeros (1, ly - lb))];
    else
      x = b;
    endif
    y = filter (a, 1, x);
  else
    if(ly > la)
      x = [a, (zeros (1, ly - la))];
    else
      x = a;
    endif
    y = filter (b, 1, x);
  endif

endfunction
