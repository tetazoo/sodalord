/*

Copyright (C) 2003 John W. Eaton

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

#if !defined (octave_ls_mat5_h)
#define octave_ls_mat5_h 1

enum mat5_data_type
  {
    miINT8 = 1,			// 8 bit signed
    miUINT8,			// 8 bit unsigned
    miINT16,			// 16 bit signed
    miUINT16,			// 16 bit unsigned
    miINT32,			// 32 bit signed
    miUINT32,			// 32 bit unsigned
    miSINGLE,			// IEEE 754 single precision float
    miRESERVE1,
    miDOUBLE,			// IEEE 754 double precision float
    miRESERVE2,
    miRESERVE3,
    miINT64,			// 64 bit signed
    miUINT64,			// 64 bit unsigned
    miMATRIX			// MATLAB array
  };

extern int
read_mat5_binary_file_header (std::istream& is, bool& swap,
			      bool quiet = false);
extern std::string
read_mat5_binary_element (std::istream& is, const std::string& filename,
			  bool swap, bool& global, octave_value& tc);
extern bool
save_mat5_binary_element (std::ostream& os,
			  const octave_value& tc, const std::string& name,
			  bool mark_as_global, bool save_as_floats);

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/

