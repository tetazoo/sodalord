## Copyright (C) 2000, Teemu Ikonen
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
## @deftypefn {Function File} {} errorbar (@var{args})
## This function produces two-dimensional plots with errorbars. Many
## different combinations of arguments are possible.  The simplest form is
##
## @example
## errorbar (@var{y}, @var{ey})
## @end example
##
## @noindent
## where the first argument is taken as the set of @var{y} coordinates
## and the second argument @var{ey} is taken as the errors of the
## @var{y} values. @var{x} coordinates are taken to be the indices
## of the elements, starting with 1.
##
## If more than two arguments are given, they are interpreted as
##
## @example
## errorbar (@var{x}, @var{y}, ..., @var{fmt} ...)
## @end example
##
## @noindent
## where after @var{x} and @var{y} there can be up to four error
## parameters such as @var{ey}, @var{ex}, @var{ly}, @var{uy} etc.,
## depending on the plot type. Any number of argument sets may appear,
## as long as they are separated with a format string @var{fmt}.
##
## If @var{y} is a matrix, @var{x} and error parameters must also be matrices
## having same dimensions. The columns of @var{y} are plotted versus the
## corresponding columns of @var{x} and errorbars are drawn from
## the corresponding columns of error parameters.
##
## If @var{fmt} is missing, yerrorbars ("~") plot style
## is assumed.
## If the @var{fmt} argument is supplied, it is interpreted as in
## normal plots (See __pltopt__). In addition the following
## plot styles are supported by errorbar:
##
## @table @samp
## @item ~
## Set yerrorbars plot style (default).
##
## @item >
## Set xerrorbars plot style.
##
## @item ~>
## Set xyerrorbars plot style.
##
## @item #
## Set boxes plot style.
##
## @item #~
## Set boxerrorbars plot style.
##
## @item #~>
## Set boxxyerrorbars plot style.
##
## @end table
##
## Examples:
##
## @example
## errorbar(@var{x}, @var{y}, @var{ex}, ">")
## @end example
##
## xerrorbar plot of @var{y} versus @var{x} with @var{x} errorbars drawn from
## @var{x}-@var{ex} to @var{x}+@var{ex}.
##
## @example
## errorbar(@var{x}, @var{y1}, @var{ey}, "~", @var{x}, @var{y2}, @var{ly}, @var{uy})
## @end example
##
## Two yerrorbar plots with @var{y1} and @var{y2} versus @var{x}.
## Errorbars for @var{y1} are drawn from @var{y1}-@var{ey} to
## @var{y1}+@var{ey}, errorbars for @var{y2} from @var{y2}-@var{ly} to
## @var{y2}+@var{uy}.
##
## @example
## errorbar(@var{x}, @var{y}, @var{lx}, @var{ux}, @var{ly}, @var{uy}, "~>")
## @end example
##
## xyerrorbar plot of @var{y} versus @var{x} where @var{x} errorbars
## are drawn from @var{x}-@var{lx} to @var{x}+@var{ux} and @var{y} errorbars
## from @var{y}-@var{ly} to @var{y}+@var{uy}.
##
## @end deftypefn
## @seealso{semilogx, semilogy, loglog, polar, mesh, contour, __pltopt__,
## bar, stairs, gplot, gsplot, replot, xlabel, ylabel, and title}

## Created: 18.7.2000
## Author: Teemu Ikonen <tpikonen@pcu.helsinki.fi>
## Keywords: errorbar, plotting

function errorbar (...)

  if (nargin < 2)
    usage ("errorbar (...)");
  endif

  save_hold = ishold;
  unwind_protect
    if (! ishold)
      clg ()
    endif
    hold ("on");
    while (nargin)
      a = va_arg ();
      nargin--;
      if (is_vector (a))
	a = a(:);
      elseif (is_matrix (a));
	;
      else
	usage ("errorbar (...)");
      endif
      sz = size (a);
      ndata = 1;
      arg1 = a;
      fmt = " ";
      while (nargin)
	nargin--;
	a = va_arg ();
	if (isstr (a))
	  fmt = a;
	  cmd = "__errplot__ (arg1";
	  for i = 2:ndata,
	    cmd = [cmd, sprintf(", arg%d",i)];
	  endfor
	  cmd = [cmd, ", fmt);"];
	  eval (cmd);
	  break;
	elseif (is_vector (a))
	  a = a(:);
	elseif (is_matrix (a))
	  ;
	else
	  error ("wrong argument types");
	endif
	if (size (a) != sz)
	  error ("argument sizes do not match");
	endif
	ndata++;
	eval (sprintf ("arg%d = a;", ndata));
	if (ndata > 6)
	  error ("too many arguments to a plot");
	endif
      endwhile
    endwhile

    if (! isstr (a))
      fmt = " ";
      cmd = "__errplot__(arg1";
      for i = 2:ndata,
	cmd = [cmd, sprintf(", arg%d",i)];
      endfor
      cmd = [cmd, ", fmt);"];
      eval (cmd);
    endif
  unwind_protect_cleanup
    if (! save_hold)
      hold ("off");
    endif
  end_unwind_protect

endfunction
