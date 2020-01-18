## Copyright (C) 1996, 1997  Kurt Hornik
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
## @deftypefn {Function File} {} cut (@var{x}, @var{breaks})
## Create categorical data out of numerical or continuous data by
## cutting into intervals.
##
## If @var{breaks} is a scalar, the data is cut into that many
## equal-width intervals.  If @var{breaks} is a vector of break points,
## the category has @code{length (@var{breaks}) - 1} groups.
##
## The returned value is a vector of the same size as @var{x} telling
## which group each point in @var{x} belongs to.  Groups are labelled
## from 1 to the number of groups; points outside the range of
## @var{breaks} are labelled by @code{NaN}.
## @end deftypefn

## Author: KH <Kurt.Hornik@ci.tuwien.ac.at>
## Description: Cut data into intervals

function group = cut (X, BREAKS)

  if (nargin != 2)
    usage ("cut (X, BREAKS)");
  endif

  if (! is_vector (X))
    error ("cut: X must be a vector");
  endif
  if is_scalar (BREAKS)
    BREAKS = linspace (min (X), max (X), BREAKS + 1);
    BREAKS(1) = BREAKS(1) - 1;
  elseif is_vector (BREAKS)
    BREAKS = sort (BREAKS);
  else
    error ("cut: BREAKS must be a scalar or vector");
  endif

  group = NaN * ones (size (X));
  m = length (BREAKS);
  if any (k = find ((X >= min (BREAKS)) & (X <= max (BREAKS))))
    n = length (k);
    group(k) = sum ((ones (m, 1) * reshape (X(k), 1, n))
                    > (reshape (BREAKS, m, 1) * ones (1, n)));
  endif

endfunction
