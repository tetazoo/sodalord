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
## @deftypefn {Function File} {} title (@var{string})
## Specify a title for a plot.  If you already have a plot displayed, use
## the command @code{replot} to redisplay it with the new title.
## @end deftypefn
## @seealso{plot, semilogx, semilogy, loglog, polar, mesh, contour,
## bar, stairs, gplot, gsplot, replot, xlabel, and ylabel}

## Author: jwe

function title (text)

  if (nargin != 1)
    usage ("title (text)");
  endif

  if (isstr (text))
    eval (sprintf ("gset title \"%s\"",
		   undo_string_escapes (undo_string_escapes (text))));
  else
    error ("title: text must be a string");
  endif

endfunction
