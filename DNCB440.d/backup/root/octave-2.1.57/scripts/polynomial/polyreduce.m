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
## @deftypefn {Function File} {} polyreduce (@var{c})
## Reduces a polynomial coefficient vector to a minimum number of terms by
## stripping off any leading zeros.
## @end deftypefn
## @seealso{poly, roots, conv, deconv, residue, filter, polyval,
## polyvalm, polyderiv, and polyinteg}

## Author: Tony Richardson <arichard@stark.cc.oh.us>
## Created: June 1994
## Adapted-By: jwe

function p = polyreduce (p)

  if (nargin != 1)
    usage ("polyreduce (p)");
  endif

  if (! (isvector (p) || isempty (p)))
    error ("polyreduce: argument must be a vector");
  endif

  if (! isempty (p) )

    index = find (p != 0);

    if (isempty (index))
      
      p = 0;
    
    else

      p = p (index (1):length (p));

    endif

  endif

endfunction
