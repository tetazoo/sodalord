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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <cfloat>
#include <cstring>
#include <cctype>

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "byte-swap.h"
#include "data-conv.h"
#include "file-ops.h"
#include "glob-match.h"
#include "lo-mappers.h"
#include "lo-sstream.h"
#include "mach-info.h"
#include "oct-env.h"
#include "oct-time.h"
#include "quit.h"
#include "str-vec.h"

#include "Cell.h"
#include "defun.h"
#include "error.h"
#include "gripes.h"
#include "load-save.h"
#include "oct-obj.h"
#include "oct-map.h"
#include "ov-cell.h"
#include "pager.h"
#include "pt-exp.h"
#include "symtab.h"
#include "sysdep.h"
#include "unwind-prot.h"
#include "utils.h"
#include "variables.h"
#include "version.h"
#include "dMatrix.h"

#include "ls-mat-ascii.h"

static std::string
get_mat_data_input_line (std::istream& is)
{
  std::string retval;

  bool have_data = false;

  do
    {
      retval = "";

      char c;
      while (is.get (c))
	{
	  if (c == '\n' || c == '\r')
	    break;

	  if (c == '%' || c == '#')
	    {
	      // skip to end of line
	      while (is.get (c))
		if (c == '\n' || c == '\r')
		  break;

	      break;
	    }

	  if (! is.eof ())
	    {
	      if (! have_data && c != ' ' && c != '\t')
		have_data = true;

	      retval += c;
	    }
	}
    }
  while (! (have_data || is.eof ()));

  return retval;
}

static void
get_lines_and_columns (std::istream& is, const std::string& filename, int& nr, int& nc)
{
  std::streampos pos = is.tellg ();

  int file_line_number = 0;

  nr = 0;
  nc = 0;

  while (is && ! error_state)
    {
      OCTAVE_QUIT;

      std::string buf = get_mat_data_input_line (is);

      file_line_number++;

      size_t beg = buf.find_first_not_of (", \t");

      // If we see a CR as the last character in the buffer, we had a
      // CRLF pair as the line separator.  Any other CR in the text
      // will not be considered as whitespace.

      if (beg != NPOS && buf[beg] == '\r' && beg == buf.length () - 1)
	{
	  // We had a blank line ending with a CRLF.  Handle it the
	  // same as an empty line.
	  beg = NPOS;
	}

      int tmp_nc = 0;

      while (beg != NPOS)
	{
	  tmp_nc++;

	  size_t end = buf.find_first_of (", \t", beg);

	  if (end != NPOS)
	    {
	      beg = buf.find_first_not_of (", \t", end);

	      if (buf[beg] == '\r' && beg == buf.length () - 1)
		{
		  // We had a line with trailing spaces and
		  // ending with a CRLF, so this should look like EOL,
		  // not a new colum.
		  break;
		}
	    }
	  else
	    break;
	}

      if (tmp_nc > 0)
	{
	  if (nc == 0)
	    {
	      nc = tmp_nc;
	      nr++;
	    }
	  else if (nc == tmp_nc)
	    nr++;
	  else
	    error ("load: %s: inconsistent number of columns near line %d",
		   filename.c_str (), file_line_number);
	}
    }

  if (nr == 0 || nc == 0)
    error ("load: file `%s' seems to be empty!", filename.c_str ());

  is.clear ();
  is.seekg (pos);
}

// Extract a matrix from a file of numbers only.
//
// Comments are not allowed.  The file should only have numeric values.
//
// Reads the file twice.  Once to find the number of rows and columns,
// and once to extract the matrix.
//
// FILENAME is used for error messages.
//
// This format provides no way to tag the data as global.

std::string
read_mat_ascii_data (std::istream& is, const std::string& filename,
		     octave_value& tc)
{
  std::string retval;

  std::string varname;

  size_t pos = filename.rfind ('/');

  if (pos != NPOS)
    varname = filename.substr (pos+1);
  else
    varname = filename;

  pos = varname.find ('.');

  if (pos != NPOS)
    varname = varname.substr (0, pos);

  size_t len = varname.length ();
  for (size_t i = 0; i < len; i++)
    {
      char c = varname[i];
      if (! (isalnum (c) || c == '_'))
	varname[i] = '_';
    }

  if (! isalpha (varname[0]))
    varname.insert (0, "X");

  if (valid_identifier (varname))
    {
      int nr = 0;
      int nc = 0;

      int total_count = 0;

      get_lines_and_columns (is, filename, nr, nc);

      OCTAVE_QUIT;

      if (! error_state && nr > 0 && nc > 0)
	{
	  Matrix tmp (nr, nc);

	  if (nr < 1 || nc < 1)
	    is.clear (std::ios::badbit);
	  else
	    {
	      double d;
	      for (int i = 0; i < nr; i++)
		{
		  std::string buf = get_mat_data_input_line (is);

#ifdef HAVE_SSTREAM
		  std::istringstream tmp_stream (buf);
#else
		  std::istrstream tmp_stream (buf.c_str ());
#endif

		  for (int j = 0; j < nc; j++)
		    {
		      OCTAVE_QUIT;

		      d = octave_read_double (tmp_stream);

		      if (tmp_stream || tmp_stream.eof ())
			{
			  tmp.elem (i, j) = d;
			  total_count++;

			  // Skip whitespace and commas.
			  char c;
			  while (1)
			    {
			      tmp_stream >> c;

			      if (! tmp_stream)
				break;

			      if (! (c == ' ' || c == '\t' || c == ','))
				{
				  tmp_stream.putback (c);
				  break;
				}
			    }

			  if (tmp_stream.eof ())
			    break;
			}
		      else
			{
			  error ("load: failed to read matrix from file `%s'",
				 filename.c_str ());

			  return retval;
			}

		    }
		}
	    }

	  if (is || is.eof ())
	    {
	      // XXX FIXME XXX -- not sure this is best, but it works.

	      if (is.eof ())
		is.clear ();

	      int expected = nr * nc;

	      if (expected == total_count)
		{
		  tc = tmp;
		  retval = varname;
		}
	      else
		error ("load: expected %d elements, found %d",
		       expected, total_count);
	    }
	  else
	    error ("load: failed to read matrix from file `%s'",
		   filename.c_str ());
	}
      else
	error ("load: unable to extract matrix size from file `%s'",
	       filename.c_str ());
    }
  else
    error ("load: unable to convert filename `%s' to valid identifier",
	   filename.c_str ());

  return retval;
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/

