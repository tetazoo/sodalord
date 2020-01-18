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
## @deftypefn {Function File} {[@var{x}, @var{map}] =} loadimage (@var{file})
## Load an image file and it's associated color map from the specified
## @var{file}.  The image must be stored in Octave's image format.
## @end deftypefn
## @seealso{saveimage, load, and save}

## Author: Tony Richardson <arichard@stark.cc.oh.us>
## Created: July 1994
## Adapted-By: jwe

function [img_retval, map_retval] = loadimage (filename)

  if (nargin != 1)
    usage ("[img, map] = loadimage (filename)");
  elseif (! isstr (filename))
    error ("loadimage: expecting filename as a string");
  endif

  file = file_in_path (IMAGEPATH, filename);

  if (isempty (file))
    error ("loadimage: unable to find image file");
  endif

  ## The file is assumed to have variables img and map, or X and map.

  eval (sprintf ("load %s", file));

  if (exist ("img"))
    img_retval = img;
  elseif (exist ("X"))
    img_retval = X;
  else
    error ("loadimage: invalid image file found");
  endif

  if (exist ("map"))
    map_retval = map;
  else
    error ("loadimage: invalid image file found");
  endif

endfunction
