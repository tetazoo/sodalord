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
## @deftypefn {Function File} {} create_set (@var{x})
## Return a row vector containing the unique values in @var{x}, sorted in
## ascending order.  For example,
##
## @example
## @group
## create_set ([ 1, 2; 3, 4; 4, 2 ])
##      @result{} [ 1, 2, 3, 4 ]
## @end group
## @end example
## @end deftypefn
## @seealso{union, intersection, and complement}

## Author: jwe

function y = create_set(x)

  if (nargin != 1)
    usage ("create_set(x)");
  endif

  if (isempty(x))
    y = [];
  else
    [nrx, ncx] = size (x);
    nelx = nrx * ncx;
    y = sort (reshape (x, 1, nelx));
    els = find (y(1:nelx-1) != y(2:nelx));
    if (isempty (els));
      y = y(1);
    else
      y = y([1, els+1]);
    endif
  endif

endfunction
