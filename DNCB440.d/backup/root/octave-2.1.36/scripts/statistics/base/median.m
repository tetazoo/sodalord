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
## @deftypefn {Function File} {} median (@var{x})
## If @var{x} is a vector, compute the median value of the elements of
## @var{x}.
## @iftex
## @tex
## $$
## {\rm median} (x) =
##   \cases{x(\lceil N/2\rceil), & $N$ odd;\cr
##           (x(N/2)+x(N/2+1))/2, & $N$ even.}
## $$
## @end tex
## @end iftex
## @ifinfo
##
## @example
## @group
##             x(ceil(N/2)),             N odd
## median(x) =
##             (x(N/2) + x((N/2)+1))/2,  N even
## @end group
## @end example
## @end ifinfo
## If @var{x} is a matrix, compute the median value for each
## column and return them in a row vector.
## @end deftypefn
## @seealso{std and mean}

## Author: jwe

function retval = median (a)

  if (nargin != 1)
    usage ("median (a)");
  endif

  [nr, nc] = size (a);
  s = sort (a);
  if (nr == 1 && nc > 0)
    if (rem (nc, 2) == 0)
      i = nc/2;
      retval = (s (i) + s (i+1)) / 2;
    else
      i = ceil (nc/2);
      retval = s (i);
    endif
  elseif (nr > 0 && nc > 0)
    if (rem (nr, 2) == 0)
      i = nr/2;
      retval = (s (i,:) + s (i+1,:)) / 2;
    else
      i = ceil (nr/2);
      retval = s (i,:);
    endif
  else
    error ("median: invalid matrix argument");
  endif

endfunction
