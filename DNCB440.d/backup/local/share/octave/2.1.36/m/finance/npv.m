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
## @deftypefn {Function File} {} npv (@var{r}, @var{p}, @var{i})
## Returns the net present value of a series of irregular (i.e., not
## necessarily identical) payments @var{p} which occur at the ends of @var{n}
## consecutive periods.  @var{r} specifies the one-period interest rates and
## can either be a scalar (constant rates) or a vector of the same
## length as @var{p}.
##
## The optional argument @var{i} may be used to specify an initial
## investment.
##
## Note that the rate @var{r} is specified as a fraction (i.e., 0.05,
## not 5 percent).
## @end deftypefn
## @seealso{irr and pv}

## Author: KH <Kurt.Hornik@ci.tuwien.ac.at>
## Description: Net present value of a series of payments

function v = npv (r, p, i)

  if ((nargin < 2) || (nargin > 3))
    usage ("npv (r, p, i");
  endif

  if (! (is_vector (p)))
    error ("npv: p has to be a vector");
  else
    n = length (p);
    p = reshape (p, 1, n);
  endif

  if (any (any (r <= -1)))
    error ("npv: all interest rates must be > -1");
  endif
  if (is_scalar (r))
    d = 1 ./ (1 + r) .^ (0 : n);
  elseif (is_vector (r) && (length (r) == n))
    d = [1, (1 ./ cumprod (reshape (1 + r, 1, n)))];
  else
    error ("npv: r must be a scalar or a vector of the same length as p");
  endif

  if (nargin == 3)
    if (! is_scalar (i))
      error ("npv: I_0 must be a scalar");
    endif
  else
    i = 0;
  endif

  p = [i, p];
  v = sum (d .* p);

endfunction
