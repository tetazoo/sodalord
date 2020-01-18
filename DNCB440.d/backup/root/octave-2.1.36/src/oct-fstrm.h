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

#if !defined (octave_octave_fstream_h)
#define octave_octave_fstream_h 1

#include <fstream>
#include <string>

#include "oct-stream.h"

class
octave_fstream : public octave_base_stream
{
public:

  octave_fstream (const std::string& nm_arg,
		  std::ios::openmode arg_md = std::ios::in|std::ios::out,
		  oct_mach_info::float_format flt_fmt =
		  oct_mach_info::native);

  static octave_stream
  create (const std::string& nm_arg,
	  std::ios::openmode arg_md = std::ios::in|std::ios::out,
	  oct_mach_info::float_format flt_fmt = oct_mach_info::native);

  // Position a stream at OFFSET relative to ORIGIN.

  int seek (std::streamoff offset, std::ios::seekdir origin);

  // Return current stream position.

  long tell (void) const;

  // Return non-zero if EOF has been reached on this stream.

  bool eof (void) const;

  void do_close (void);

  // The name of the file.

  std::string name (void) const { return nm; }

  std::istream *input_stream (void);

  std::ostream *output_stream (void);

protected:

  ~octave_fstream (void) { }

private:

  std::string nm;

  std::fstream fs;

  // No copying!

  octave_fstream (const octave_fstream&);

  octave_fstream& operator = (const octave_fstream&);
};

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
