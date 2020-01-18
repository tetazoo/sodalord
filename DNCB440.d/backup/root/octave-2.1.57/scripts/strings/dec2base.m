## Copyright (C) 2000 Daniel Calvelo
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
## @deftypefn {Function File} {} dec2base (@var{n}, @var{b}, @var{len})
## Return a string of symbols in base @var{b} corresponding to the
## the nonnegative integer @var{n}.
##
## @example
## dec2base (123, 3)
##      @result{} "11120"
## @end example
##
## If @var{n} is a vector, return a string matrix with one row per value,
## padded with leading zeros to the width of the largest value.
##
## If @var{b} is a string then the characters of @var{b} are used as
## the symbols for the digits of @var{n}.  Space (' ') may not be used
## as a symbol.
##
## @example
## dec2base (123, "aei")
##      @result{} "eeeia"
## @end example
##
## The optional third argument, @var{len}, specifies the minimum
## number of digits in the result.
## @end deftypefn
##
## @seealso{base2dec, dec2bin, bin2dec, hex2dec, dec2hex}

## Author: Daniel Calvelo <dcalvelo@yahoo.com>
## Adapted-by: Paul Kienzle <pkienzle@kienzle.powernet.co.uk>

function retval = dec2base (n, base, len)

  if (nargin < 2 || nargin > 3)
    usage ("dec2base (n, base [, len])");
  endif

  if (prod (size (n)) != length (n))
    error ("dec2base: cannot convert matrices.");
  elseif (any (n < 0 | n != fix (n)))
    error ("dec2base: can only convert non-negative integers.")
  endif

  symbols = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  if (isstr (base))
    symbols = base;
    base = length (symbols);
    if any (diff (sort (toascii (symbols))) == 0)
      error ("dec2base: symbols representing digits must be unique.");
    endif
  elseif (! isscalar (base))
    error ("dec2base: cannot convert from several bases at once.");
  elseif (base < 2 || base > length (symbols))
    error ("dec2base: base must be between 2 and 36 or a string of symbols");
  endif
  
  ## determine number of digits required to handle all numbers
  max_len = floor (log (max (max (n), 1)) ./ log (base)) + 1;

  if (nargin == 3)
    max_len = max (max_len, len);
  endif
  
  ## determine digits for each number
  power = ones (length (n), 1) * (base .^ (max_len-1 : -1 : 0));
  n = n(:) * ones (1, max_len);
  digits = floor (rem (n, base*power) ./ power);

  ## convert digits to symbols
  retval = reshape (symbols (digits+1), size (digits));

endfunction
