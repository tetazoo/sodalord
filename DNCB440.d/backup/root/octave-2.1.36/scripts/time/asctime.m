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
## @deftypefn {Function File} {} asctime (@var{tm_struct})
## Convert a time structure to a string using the following five-field
## format: Thu Mar 28 08:40:14 1996.  For example,
##
## @example
## @group
## asctime (localtime (time ())
##      @result{} "Mon Feb 17 01:15:06 1997\n"
## @end group
## @end example
##
## This is equivalent to @code{ctime (time ())}.
## @end deftypefn

## Author: jwe

function retval = asctime (t)

  if (nargin == 1)
    retval = strftime ("%a %b %d %H:%M:%S %Y\n", t);
  else
    usage ("asctime (TMSTRUCT)");
  endif

endfunction
