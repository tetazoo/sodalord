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
## @deftypefn {Function File} {} freqchkw (@var{w})
## Used by @code{__freqresp__} to check that input frequency vector @var{w}
## is valid.
## Returns boolean value.
## @end deftypefn

## Author: A. S. Hodel <a.s.hodel@eng.auburn.edu>
## Created: July 1996

function USEW = freqchkw (w)

  if (isempty (w))
    USEW = 0;
  elseif (! isvector (w))
    error ("w (%dx%d): must be [], a vector or a scalar",
	   rows (w), columns (w));
  elseif (max (abs (imag(w))) != 0 && min (real (w)) <= 0)
    error ("w must have real positive entries");
  else
    w = sort (w);
    USEW = 1;   ## vector provided (check values later)
  endif

endfunction
