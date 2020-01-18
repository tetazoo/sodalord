## Copyright (C) 2003 John W. Eaton
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
## @deftypefn {Function File} {[@var{dir}, @var{name}, @var{ext}, @var{ver}] =} fileparts (@var{filename})
## Return the directory, name, extension, and version components of
## @var{filename}.
## @end deftypefn

function [directory, name, extension, version] = fileparts (filename)

  if (nargin == 1)
    if (isstr (filename))
      ds = rindex (filename, filesep);
      es = rindex (filename, ".");
      if (es < ds)
	es = length(filename)+1;
      endif
      directory = filename(1:ds-1);
      name = filename(ds+1:es-1);
      extension = filename(es:end);
      version = "";
    else
      error ("fileparts: expecting filename argument to be a string");
    endif
  else
    usage ("fileparts (filename)");
  endif

endfunction
