## Copyright (C) 2002 John W. Eaton
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
## @deftypefn {Command} {} close
## @deftypefnx {Command} {} close all
## Close the plot window(s).
## @end deftypefn

## Author: jwe

## PKG_ADD: mark_as_command close

function retval = close (arg1, arg2)

  static warned_all = false;
  static warned_name = false;
  static warned_handle = false;

  if (nargin == 0)
    if (! warned_all)
      warned_all = true;
      warning ("close: unable to close only current plot window");
    endif
    closeplot;
  elseif (nargin == 1)
    if (isstr (arg1))
      if (strcmp (arg1, "all"))
	closeplot;
      else
	if (! warned_name)
	  warned_name = true;
	  warning ("close: unable to close plot windows by name");
	endif
      endif
    else
      if (! warned_handle)
	warned_handle = true;
	warning ("close: unable to close plot windows by handle");
      endif
    endif
  elseif (nargin == 2
	  && isstr (arg1) && strcmp (arg1, "all")
	  && isstr (arg2) && strcmp (arg2, "hidden"))
    closeplot;
  else
    usage ("close [all]");
  endif

  if (nargout > 0)
    retval = 1;
  endif

endfunction
