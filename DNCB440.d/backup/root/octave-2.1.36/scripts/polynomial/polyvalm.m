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
## @deftypefn {Function File} {} polyvalm (@var{c}, @var{x})
## Evaluate a polynomial in the matrix sense.
##
## @code{polyvalm (@var{c}, @var{x})} will evaluate the polynomial in the
## matrix sense, i.e. matrix multiplication is used instead of element by
## element multiplication as is used in polyval.
##
## The argument @var{x} must be a square matrix.
## @end deftypefn
## @seealso{polyval, poly, roots, conv, deconv, residue, filter,
## polyderiv, and polyinteg}

## Author: Tony Richardson <arichard@stark.cc.oh.us>
## Created: June 1994
## Adapted-By: jwe

function y = polyvalm (c, x)

  if (nargin != 2)
    usage ("polyvalm (c, x)");
  endif

  if (! (is_vector (c) || isempty (c)))
    error ("polyvalm: first argument must be a vector");
  endif

  if (! is_square (x))
    error ("polyvalm: second argument must be a square matrix");
  endif

  if (isempty (c))
    y = [];
    return;
  endif

  [v, d] = eig (x);

  if (is_symmetric (x))
    y = v * diag (polyval (c, diag (d))) * v';
  else
    y = v * (diag (polyval (c, diag (d))) / v);
  endif

endfunction
