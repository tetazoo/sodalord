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
## @deftypefn {Function File} {} hist (@var{y}, @var{x}, @var{norm})
## Produce histogram counts or plots.
##
## With one vector input argument, plot a histogram of the values with
## 10 bins.  The range of the histogram bins is determined by the range
## of the data.
##
## Given a second scalar argument, use that as the number of bins.
##
## Given a second vector argument, use that as the centers of the bins,
## with the width of the bins determined from the adjacent values in
## the vector.
##
## If third argument is provided, the histogram is normalised such that
## the sum of the bars is equal to @var{norm}.
##
## Extreme values are lumped in the first and last bins.
##
## With two output arguments, produce the values @var{nn} and @var{xx} such
## that @code{bar (@var{xx}, @var{nn})} will plot the histogram.
## @end deftypefn
## @seealso{bar}

## Author: jwe

function [nn, xx] = hist (y, x, norm)

  if (nargin < 1 || nargin > 3)
    usage ("[nn, xx] = hist (y, x, norm)");
  endif

  if (isvector (y))
    max_val = max (y);
    min_val = min (y);
  else
    error ("hist: first argument must be a vector");
  endif

  if (nargin == 1)
    n = 10;
    delta = (max_val - min_val) / n / 2;
    x = linspace (min_val+delta, max_val-delta, n);
    cutoff = x + delta;
  else
    ## nargin is either 2 or 3
    if (isscalar (x))
      n = x;
      if (n <= 0)
        error ("hist: number of bins must be positive");
      endif
      delta = (max_val - min_val) / n / 2;
      x = linspace (min_val+delta, max_val-delta, n);
      cutoff = x + delta;
    elseif (isvector (x))
      tmp = sort (x);
      if (any (tmp != x))
        warning ("hist: bin values not sorted on input");
        x = tmp;
      endif
      cutoff = (x(1:end-1) + x(2:end)) / 2;
      n = length (x);
    else
      error ("hist: second argument must be a scalar or a vector");
    endif
  endif

  if (n < 30)
    ## The following algorithm works fastest for n less than about 30.
    chist = [zeros(n,1); length(y)];
    for i = 1:n-1
      chist(i+1) = sum (y < cutoff(i));
    endfor
  else
    ## The following algorithm works fastest for n greater than about 30.
    ## Put cutoff elements between boundaries, integrate over all
    ## elements, keep totals at boundaries.
    [s, idx] = sort ([cutoff(:); y(:)]);
    chist = cumsum(idx>=n);
    chist = [0; chist(idx<n); chist(end)];
  endif

  freq= diff(chist)';

  if (nargin == 3)
    ## Normalise the histogram.
    freq = freq / length (y) * norm;
  endif

  if (nargout > 0)
    nn = freq;
    xx = x;
  else
    bar (x, freq);
  endif

endfunction

%!test
%!  for n = [1, 10, 30, 100, 1000]
%!    assert( sum(hist([1:n], [1:n])) == n );
%!  endfor
