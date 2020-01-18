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
## @deftypefn {Function File} {[@var{nonz}, @var{zer}] =} zgrownorm (@var{mat}, @var{meps})
## Return @var{nonz} = number of rows of @var{mat} whose two norm
## exceeds @var{meps}, and @var{zer} = number of rows of mat whose two
## norm is less than @var{meps}.
## @end deftypefn

function [sig, tau] = zgrownorm (mat, meps)

  rownorm = [];
  for ii=1:rows(mat)
    rownorm(ii) = norm(mat(ii,:));
  endfor
  sig = sum(rownorm > meps);
  tau = sum(rownorm <= meps);

endfunction

