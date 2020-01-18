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

#if !defined (octave_data_conv_h)
#define octave_data_conv_h 1

#include <climits>

#include "mach-info.h"

// Not all of the following are currently used.

#if CHAR_BIT != 8
#error "CHAR_BIT is not 8!"
#endif

#if SIZEOF_SHORT == 2
#define TWO_BYTE_INT short
#elif SIZEOF_INT == 2
#define TWO_BYTE_INT int
#else
#error "No 2 byte integer type found!"
#endif

#if SIZEOF_INT == 4
#define FOUR_BYTE_INT int
#elif SIZEOF_LONG == 4
#define FOUR_BYTE_INT long
#else
#error "No 4 byte integer type found!"
#endif

#if SIZEOF_LONG == 8
#define EIGHT_BYTE_INT long
#else
#if SIZEOF_LONG_LONG == 8
// if `long long' is not implemented, then SIZEOF_LONG_LONG will be 0
#define EIGHT_BYTE_INT long long
// if no 8 byte integer type is found, then EIGHT_BYTE_INT is not defined
#endif
#endif

class
oct_data_conv
{
public:

  enum data_type
    {
      dt_unknown,
      dt_char,
      dt_schar,
      dt_uchar,
      dt_short,
      dt_ushort,
      dt_int,
      dt_uint,
      dt_long,
      dt_ulong,
      dt_float,
      dt_double,
      dt_float_complex,
      dt_double_complex
    };

  static data_type string_to_data_type (const std::string& s);
};

// Add new entries to the end of this enum, otherwise Octave will not
// be able to read binary data files stored in Octave's binary data
// format that were created with previous versions of Octave.

enum save_type
  {
    LS_U_CHAR  = 0,
    LS_U_SHORT = 1,
    LS_U_INT   = 2,
    LS_CHAR    = 3,
    LS_SHORT   = 4,
    LS_INT     = 5,
    LS_FLOAT   = 6,
    LS_DOUBLE  = 7,
    LS_U_LONG  = 8,
    LS_LONG    = 9
  };

extern void
do_double_format_conversion (double *data, int len,
			     oct_mach_info::float_format fmt);

extern void
do_float_format_conversion (float *data, int len,
			    oct_mach_info::float_format fmt);

extern void
read_doubles (std::istream& is, double *data, save_type type, int len,
	      int swap, oct_mach_info::float_format fmt);
extern void
write_doubles (std::ostream& os, const double *data, save_type type, int len);

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
