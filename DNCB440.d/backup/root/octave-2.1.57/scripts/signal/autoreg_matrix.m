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
## @deftypefn {Function File} {} autoreg_matrix (@var{y}, @var{k})
## Given a time series (vector) @var{y}, return a matrix with ones in the
## first column and the first @var{k} lagged values of @var{y} in the
## other columns.  I.e., for @var{t} > @var{k}, @code{[1,
## @var{y}(@var{t}-1), ..., @var{y}(@var{t}-@var{k})]} is the t-th row
## of the result.  The resulting matrix may be used as a regressor matrix
## in autoregressions.
## @end deftypefn

## Author: KH <Kurt.Hornik@ci.tuwien.ac.at>
## Description: Design matrix for autoregressions

function X = autoreg_matrix (y, k)

  if (nargin != 2)
    usage ("autoreg_matrix (y, k)");
  endif

  if (! (isvector (y)))
    error ("autoreg_matrix: y must be a vector");
  endif

  T = length (y);
  y = reshape (y, T, 1);
  X = ones (T, k+1);
  for j = 1 : k;
    X(:, j+1) = [(zeros (j, 1)); y(1:T-j)];
  endfor

endfunction
