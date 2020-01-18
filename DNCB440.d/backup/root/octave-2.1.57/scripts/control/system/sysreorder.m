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
## @deftypefn {Function File} {} sysreorder (@var{vlen}, @var{list})
##
## @strong{Inputs}
## @var{vlen}=vector length, @var{list}= a subset of @code{[1:vlen]},
##
## @strong{Outputs}
## @var{pv}: a permutation vector to order elements of @code{[1:vlen]} in
## @code{list} to the end of a vector.
##
## Used internally by @code{sysconnect} to permute vector elements to their
## desired locations.
## @end deftypefn

## Author: A. S. Hodel <a.s.hodel@eng.auburn.edu>
## Created: August 1995

function pv = sysreorder (vlen, list)

  ## disp('sysreorder: entry')

  pv = 1:vlen;
  ## make it a row vector
  list = reshape(list,1,length(list));
  A = pv'*ones(size(list));
  B = ones(size(pv'))*list;
  X = (A != B);
  if(!isvector(X))
    y = min(X');
  else
   y = X';
  endif
  z = find(y == 1);
  if(!isempty(z))
    pv = [z, list];
  else
    pv = list;
  endif

endfunction
