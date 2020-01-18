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
## @deftypefn {Function File} {} stdnormal_cdf (@var{x})
## For each component of @var{x}, compute the CDF of the standard normal
## distribution at @var{x}.
## @end deftypefn

## Author: KH <Kurt.Hornik@ci.tuwien.ac.at>
## Description: CDF of the standard normal distribution

function cdf = stdnormal_cdf (x)

  if (nargin != 1)
    usage ("stdnormal_cdf (x)");
  endif

  [r_x, c_x] = size (x);
  if (r_x * c_x == 0)
    error ("stdnormal_cdf: x must not be empty");
  endif

  cdf = (ones (r_x, c_x) + erf (x / sqrt (2))) / 2;

endfunction




