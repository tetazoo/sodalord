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
## @deftypefn {Function File} {} prompt (@var{inputs})
## @format
## function prompt([str])
## Prompt user to continue
## str: input string. Default value: "\n ---- Press a key to continue ---"
## @end format
## @end deftypefn

## Author: David Clem
## Created: August 15, 1994
## Modified A. S. Hodel June 1995

function prompt (str)

  if(nargin > 1)
    usage("prompt([str])");
  elseif(nargin == 0)
    str = "\n ---- Press a key to continue ---";
  elseif ( !isstr(str) )
    error("prompt: input must be a string");
  endif

  disp(str);
  fflush(stdout);
  kbhit;

endfunction
