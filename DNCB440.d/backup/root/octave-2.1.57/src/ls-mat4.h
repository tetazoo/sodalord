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

#if !defined (octave_ls_mat4_h)
#define octave_ls_mat4 1

extern oct_mach_info::float_format
mopt_digit_to_float_format (int mach);

extern int
float_format_to_mopt_digit (oct_mach_info::float_format flt_fmt);

extern int
read_mat_file_header (std::istream& is, bool& swap, FOUR_BYTE_INT& mopt, 
		      FOUR_BYTE_INT& nr, FOUR_BYTE_INT& nc,
		      FOUR_BYTE_INT& imag, FOUR_BYTE_INT& len,
		      int quiet = 0);

extern std::string
read_mat_binary_data (std::istream& is, const std::string& filename,
		      octave_value& tc);

extern bool
save_mat_binary_data (std::ostream& os, const octave_value& tc,
		      const std::string& name) ;

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
