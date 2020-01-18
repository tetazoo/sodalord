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
## @deftypefn {Function File} {} loadaudio (@var{name}, @var{ext}, @var{bps})
## Loads audio data from the file @file{@var{name}.@var{ext}} into the
## vector @var{x}.
##
## The extension @var{ext} determines how the data in the audio file is
## interpreted;  the extensions @file{lin} (default) and @file{raw}
## correspond to linear, the extensions @file{au}, @file{mu}, or @file{snd}
## to mu-law encoding.
##
## The argument @var{bps} can be either 8 (default) or 16, and specifies
## the number of bits per sample used in the audio file.
## @end deftypefn
## @seealso{lin2mu, mu2lin, saveaudio, playaudio, setaudio, and record}

## Author: AW <Andreas.Weingessel@ci.tuwien.ac.at>
## Created: 10 April 1994
## Adapted-By: jwe

function X = loadaudio (name, ext, bit)

  if (nargin == 0 || nargin > 3)
    usage ("loadaudio (name, ext, bit)");
  endif

  if (nargin == 1)
    ext = "lin";
  endif

  if (nargin < 3)
    bit = 8;
  elseif (bit != 8 && bit != 16)
    error ("loadaudio: bit must be either 8 or 16");
  endif

  name = [name, ".", ext];
  num = fopen (name, "rb");

  if (strcmp (ext, "lin") || strcmp (ext, "raw") || strcmp (ext, "pcm"))
    if (bit == 8)
      [Y, c] = fread (num, inf, "uchar");
      X = Y - 127;
    else
      [X, c] = fread (num, inf, "short");
    endif
  elseif (strcmp (ext, "mu") || strcmp (ext, "au")
	  || strcmp (ext, "snd") || strcmp(ext, "ul"))
    [Y, c] = fread (num, inf, "uchar");
    ## remove file header
    m = max (find (Y(1:64) == 0));
    if (! isempty (m))
      Y(1:m) = [];
    endif
    X = mu2lin (Y, bit);
  else
    fclose (num);
    error ("loadaudio does not support given extension");
  endif

  fclose (num);

endfunction
