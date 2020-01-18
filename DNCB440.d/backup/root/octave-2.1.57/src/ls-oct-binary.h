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

#if !defined (octave_ls_oct_binary_h)
#define octave_ls_oct_binary_h 1

extern bool
save_binary_data (std::ostream& os, const octave_value& tc,
		  const std::string& name, const std::string& doc,
		  bool mark_as_global, bool save_as_floats);

extern std::string
read_binary_data (std::istream& is, bool swap,
		  oct_mach_info::float_format fmt,
		  const std::string& filename, bool& global,
		  octave_value& tc, std::string& doc);

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/

