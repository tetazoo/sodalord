## Copyright (C) 1995, 1996, 1997  Friedrich Leisch
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
## @deftypefn {Function File} {[@var{a}, @var{v}] =} yulewalker (@var{c})
## Fit an AR (p)-model with Yule-Walker estimates given a vector @var{c}
## of autocovariances @code{[gamma_0, ..., gamma_p]}.
##
## Returns the AR coefficients, @var{a}, and the variance of white
## noise, @var{v}.
## @end deftypefn

## Author: FL <Friedrich.Leisch@ci.tuwien.ac.at>
## Description: Fit AR model by Yule-Walker method

function [a, v] = yulewalker (c)

  p = length (c) - 1;

  if (columns (c) > 1)
    c = c';
  endif

  cp = c(2 : p+1);
  CP = zeros(p, p);

  for i = 1:p
    for j = 1:p
      CP (i, j) = c (abs (i-j) + 1);
    endfor
  endfor

  a = inv (CP) * cp;
  v = c(1) - a' * cp;

endfunction





