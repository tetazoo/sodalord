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
## @deftypefn {Function File} {} imshow (@var{i})
## @deftypefnx {Function File} {} imshow (@var{x}, @var{map})
## @deftypefnx {Function File} {} imshow (@var{x}, @var{n})
## @deftypefnx {Function File} {} imshow (@var{i}, @var{n})
## @deftypefnx {Function File} {} imshow (@var{r}, @var{g}, @var{b})
## Display an image.
##
## @code{imshow (@var{x})} displays an intensity image, estimating the 
## number of gray levels.
##
## @code{imshow (@var{x}, @var{map})} displays an indexed image using the
## specified colormap.
##
## @code{imshow (@var{i}, @var{N})} displays a gray scale intensity image of
## N levels.
##
## @code{imshow (@var{r}, @var{g}, @var{b})} displays an RGB image.
##
## The string @code{truesize} can always be used as an optional
## final argument to prevent automatic zooming of the image.
## @end deftypefn
##
## @seealso{image, imagesc, colormap, gray2ind, and rgb2ind}

## Author: Tony Richardson <arichard@stark.cc.oh.us>
## Created: July 1994
## Adapted-By: jwe

function imshow (varargin)

  usage_str = "imshow (x) or imshow (x, map) or imshow (i, N) or imshow (r, g, b)";

  if (nargin == 0 || nargin > 4)
    usage (usage_str);
  endif
  
  ## Count nr of matrix arguments.
  mvars = 0;
  while (mvars < nargin && ismatrix (varargin{mvars+1}))
    mvars++;
  endwhile
  
  if (mvars < 1 || mvars > 3)
    usage (usage_str);
  endif
  
  ## All except imshow (r, g, b)

  if (mvars != 3)
    I = varargin{1};
    if (max (varargin{1}(:)) <= 1)
      # image in [0-1]; scale to [0-255]
      I = I * 255;
      M = gray (256);
    endif
  endif

  if (mvars == 1)
    ## imshow (x)
    ## Grayscale image [0-N] -- estimate gray levels.
    N = 2^ceil (log2 (max(I(:))));
    M = gray (N);
  elseif (mvars == 2)
    ## imshow (x, map) or imshow (x, N)
    M = varargin{2};
    if (isscalar (M))
      M = gray (M);
    endif
  elseif (mvars == 3)
    ## imshow (r, g, b)
    r = varargin{1};
    g = varargin{2};
    b = varargin{3};
    tmp = [r; g; b];
    if (max (tmp(:)) > 1)
      ## Normalise to [0-1].
      r = r/255;
      g = g/255;
      b = b/255;
    endif
    [I, M] = rgb2ind (r, g, b);
  endif
  
  ## Check for "truesize".
  zoom = [];
  for i = mvars+1:nargin
    if (isstr (varargin{i}) && strcmp (varargin{i}, "truesize"))
      zoom = 1;
    endif
  endfor

  colormap (M);
  image (I, zoom);

endfunction

%!error imshow ()                           # no arguments
%!error imshow (1, 2, 3, 4, 5)              # too many arguments
%!error imshow ([1,2], [2,3], [3,4], [4,5]) # too many matrix arguments
%!error imshow ("image.png")                # filename not accepted as argument

%!demo
%!  imshow (loadimage ("default.img"));

%!demo
%!  I = loadimage ("default.img");
%!  imshow (I, "truesize")

%!demo
%!  [I, M] = loadimage ("default.img");
%!  imshow(I, M);
