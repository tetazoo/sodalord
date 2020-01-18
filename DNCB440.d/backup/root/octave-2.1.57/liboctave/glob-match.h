/*

Copyright (C) 1996, 1997 John W. Eaton

This file is part of Octave.

Octave is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2, or (at your option) any
later version.

Octave is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with Octave; see the file COPYING.  If not, write to the Free
Software Foundation, 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#if !defined (octave_glob_match_h)
#define octave_glob_match_h 1

#include <string>

#include "Array.h"
#include "str-vec.h"

class
glob_match
{
public:

  enum opts
    {
      pathname = 1,  // No wildcard can ever match `/'.
      noescape = 2,  // Backslashes don't quote special chars.
      period = 4     // Leading `.' is matched only explicitly.
   };

  glob_match (const std::string& p = std::string (),
	      unsigned int f = pathname|noescape|period)
    : pat (p), flags (f) { }

  glob_match (const string_vector& p = string_vector (),
	      unsigned int f = pathname|noescape|period)
    : pat (p), flags (f) { }

  glob_match (const glob_match& gm) : pat (gm.pat), flags (gm.flags) { }

  glob_match& operator = (const glob_match& gm)
    {
      if (this != &gm)
	{
	  pat = gm.pat;
	  flags = gm.flags;
	}
      return *this;
    }

  ~glob_match (void) { }

  void set_pattern (const std::string& p) { pat = p; }

  void set_pattern (const string_vector& p) { pat = p; }

  bool match (const std::string&);

  Array<bool> match (const string_vector&);

  string_vector glob (void);

private:

  // Globbing pattern(s).
  string_vector pat;

  // Option flags.
  unsigned int flags;
};

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
