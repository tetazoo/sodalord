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
## @deftypefn {Mapping Function} {} beta (@var{a}, @var{b})
## Return the Beta function,
## @iftex
## @tex
## $$
##  B (a, b) = {\Gamma (a) \Gamma (b) \over \Gamma (a + b)}.
## $$
## @end tex
## @end iftex
## @ifinfo
##
## @example
## beta (a, b) = gamma (a) * gamma (b) / gamma (a + b).
## @end example
## @end ifinfo
## @end deftypefn

## Author: KH <Kurt.Hornik@ci.tuwien.ac.at>
## Created: 13 June 1993
## Adapted-By: jwe

function retval = beta (a, b)

  if (nargin != 2)
    usage ("beta (a, b)");
  endif

  retval = exp (lgamma (a) + lgamma (b) - lgamma (a+b));

endfunction
