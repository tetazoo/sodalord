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
## @deftypefn {Function File} {} __plr1__ (@var{theta}, @var{fmt})
## @end deftypefn

## Author: jwe

function __plr1__ (theta, fmt)

  if (nargin != 2)
    usage ("__plr1__ (theta, fmt)");
  endif

  [nr, nc] = size (theta);
  if (nr == 1)
    theta = theta';
    tmp = nr;
    nr = nc;
    nc = tmp;
  endif
  theta_i = imag (theta);
  if (any (theta_i))
    rho = theta_i;
    theta = real (theta);
  else
    rho = theta;
    theta = (1:nr)';
  endif

  __plr2__ (theta, rho, fmt);

endfunction
