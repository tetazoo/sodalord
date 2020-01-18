## Copyright (C) 1996 Auburn University.  All rights reserved.
##
## This file is part of Octave.
##
## Octave is free software; you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by the
## Free Software Foundation; either version 2, or (at your option) any
## later version.
##
## Octave is distributed in the hope that it will be useful, but WITHOUT
## ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
## FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
## for more details.
##
## You should have received a copy of the GNU General Public License
## along with Octave; see the file COPYING.  If not, write to the Free
## Software Foundation, 59 Temple Place, Suite 330, Boston, MA 02111 USA.

## -*- texinfo -*-
## @deftypefn {Function File} {} zgshsr (@var{y})
## apply householder vector based on @math{e^(m)} to
## (column vector) y.
## Called by zgfslv
## @end deftypefn

## Author: A. S. Hodel <a.s.hodel@eng.auburn.edu>
## Created: July 24, 1992
## Conversion to Octave by R. Bruce Tenison July 3, 1994

function x = zgshsr (y)

  if (! isvector (y))
    error (sprintf ("y(%dx%d) must be a vector", rows (y), columns (y)));
  endif
  x = vec (y);
  m = length (x);
  if (m > 1)
    beta = (1 + sqrt (m)) * x(1) + sum (x(2:m));
    beta /= (m + sqrt (m));
    x(1) -= (beta * (1 + sqrt (m)));
    x(2:m) -= (beta * ones (m-1,1));
  else
    x = -x;
  endif

endfunction
