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
## @deftypefn {Function File} {} laplace_rnd (@var{r}, @var{c})
## Return an @var{r} by @var{c} matrix of random numbers from the
## Laplace distribution.
## @end deftypefn

## Author: KH <Kurt.Hornik@ci.tuwien.ac.at>
## Description: Random deviates from the Laplace distribution

function rnd = laplace_rnd (r, c)

  if (nargin != 2)
    usage ("laplace_rnd (r, c)");
  endif

  if (! (isscalar (r) && (r > 0) && (r == round (r))))
    error ("laplace_rnd: r must be a positive integer");
  endif
  if (! (isscalar (c) && (c > 0) && (c == round (c))))
    error ("laplace_rnd: c must be a positive integer");
  endif

  tmp = rand (r, c);
  rnd = ((tmp < 1/2) .* log (2 * tmp)
         - (tmp > 1/2) .* log (2 * (1 - tmp)));

endfunction
