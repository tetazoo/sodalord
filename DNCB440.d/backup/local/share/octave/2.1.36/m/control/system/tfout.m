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
## @deftypefn {Function File} {} tfout (@var{num}, @var{denom}, @var{x})
## Print formatted transfer function @math{n(s)/d(s)} to the screen.
## @var{x} defaults to the string @code{"s"}
## @end deftypefn
## @seealso{polyval, polyvalm, poly, roots, conv, deconv, residue,
## filter, polyderiv, polyinteg, and polyout}

## Author: A. S. Hodel <a.s.hodel@eng.auburn.edu>
## Created: June 1995

function tfout (num, denom, x)

  save_empty = empty_list_elements_ok;
  empty_list_elements_ok = 1;

  if (nargin < 2 ) | (nargin > 3) | (nargout != 0 )
    usage("tfout(num,denom[,x])");
  endif

  if ( (!is_vector(num)) | (!is_vector(denom)) )
    error("tfout: first two argument must be vectors");
  endif

  if (nargin == 2)
    x = "s";
  elseif( ! isstr(x) )
    error("tfout: third argument must be a string");
  endif

  numstring = polyout(num,x);
  denomstring = polyout(denom,x);
  len = max(length(numstring),length(denomstring));
  if(len > 0)
    y = strrep(blanks(len)," ","-");
    disp(numstring)
    disp(y)
    disp(denomstring)
  else
    error ("tfout: empty transfer function")
  end

  empty_list_elements_ok = save_empty;
endfunction
