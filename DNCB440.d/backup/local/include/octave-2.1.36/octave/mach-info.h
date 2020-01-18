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

#if !defined (octave_mach_info_h)
#define octave_mach_info_h 1

#include <string>

class
oct_mach_info
{
protected:

  oct_mach_info (void);

public:

  enum float_format
    {
      native,
      unknown,
      ieee_little_endian,
      ieee_big_endian,
      vax_d,
      vax_g,
      cray
    };

  static bool instance_ok (void);

  static float_format native_float_format (void);

  static bool words_big_endian (void);

  static bool words_little_endian (void);

  static float_format string_to_float_format (const std::string&);

  static std::string float_format_as_string (float_format);

private:

  static oct_mach_info *instance;

  void init_float_format (void) const;

  void ten_little_endians (void) const;

  // The floating point format for the current machine.
  mutable float_format native_float_fmt;

  // TRUE if the byte order on this system is big endian.
  mutable bool big_chief;

  // No copying!

  oct_mach_info (const oct_mach_info&);

  oct_mach_info& operator = (const oct_mach_info&);
};

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
