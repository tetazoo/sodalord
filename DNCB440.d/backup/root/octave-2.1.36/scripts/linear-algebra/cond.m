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
## @deftypefn {Function File} {} cond (@var{a})
## Compute the (two-norm) condition number of a matrix. @code{cond (a)} is
## defined as @code{norm (a) * norm (inv (a))}, and is computed via a
## singular value decomposition.
## @end deftypefn
## @seealso{norm, svd, and rank}

## Author: jwe

function retval = cond (a)

  if (nargin == 1)
    [nr, nc] = size (a);
    if (nr == 0 && nc == 0)
      if (! propagate_empty_matrices)
        error ("cond: empty matrix is invalid as argument");
      endif
      if (strcmp (propagate_empty_matrices, "warn"))
        warning ("cond: argument is empty matrix\n");
      endif
      retval = 0.0;
    endif
    if (any (any (isinf (a) | isnan (a))))
      error ("cond: argument must not contain Inf or NaN values");
    else
      sigma = svd (a);
      sigma_1 = sigma(1);
      sigma_n = sigma(length (sigma));
      if (sigma_1 == 0 || sigma_n == 0)
        retval = Inf;
      else
        retval = sigma_1 / sigma_n;
      endif
    endif
  else
    usage ("cond (a)");
  endif

endfunction
