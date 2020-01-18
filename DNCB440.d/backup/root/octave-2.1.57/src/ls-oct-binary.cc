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
#include <vector>

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

#include "ls-utils.h"
#include "ls-oct-binary.h"

// Extract one value (scalar, matrix, string, etc.) from stream IS and
// place it in TC, returning the name of the variable.  If the value
// is tagged as global in the file, return TRUE in GLOBAL.  If SWAP
// is TRUE, swap bytes after reading.
//
// The data is expected to be in the following format:
//
// Header (one per file):
// =====================
//
//   object               type            bytes
//   ------               ----            -----
//   magic number         string             10
//
//   float format         integer             1  
//
//
// Data (one set for each item):
// ============================
//
//   object               type            bytes
//   ------               ----            -----
//   name_length          integer             4
//
//   name                 string    name_length
//
//   doc_length           integer             4
//
//   doc                  string     doc_length
//
//   global flag          integer             1
//
//   data type            char                1
//
// In general "data type" is 255, and in that case the next arguments
// in the data set are
//
//   object               type            bytes
//   ------               ----            -----
//   type_length          integer             4
//
//   type                 string    type_length
//
// The string "type" is then used with octave_value_typeinfo::lookup_type
// to create an octave_value of the correct type. The specific load/save
// function is then called.
//
// For backward compatiablity "data type" can also be a value between 1
// and 7, where this defines a hardcoded octave_value of the type
//
//   data type                  octave_value
//   ---------                  ------------
//   1                          scalar
//   2                          matrix
//   3                          complex scalar
//   4                          complex matrix
//   5                          string   (old style storage)
//   6                          range
//   7                          string
//
// Except for "data type" equal 5 that requires special treatment, these
// old style "data type" value also cause the specific load/save functions
// to be called. FILENAME is used for error messages.

std::string
read_binary_data (std::istream& is, bool swap,
		  oct_mach_info::float_format fmt,
		  const std::string& filename, bool& global,
		  octave_value& tc, std::string& doc)
{
  std::string retval;

  char tmp = 0;

  FOUR_BYTE_INT name_len = 0;
  FOUR_BYTE_INT doc_len = 0;

  doc.resize (0);

  // We expect to fail here, at the beginning of a record, so not
  // being able to read another name should not result in an error.

  is.read (X_CAST (char *, &name_len), 4);
  if (! is)
    return retval;
  if (swap)
    swap_4_bytes (X_CAST (char *, &name_len));

  {
    OCTAVE_LOCAL_BUFFER (char, name, name_len+1);
    name[name_len] = '\0';
    if (! is.read (X_CAST (char *, name), name_len))
      goto data_read_error;
    retval = name;
  }

  is.read (X_CAST (char *, &doc_len), 4);
  if (! is)
    goto data_read_error;
  if (swap)
    swap_4_bytes (X_CAST (char *, &doc_len));

  {
    OCTAVE_LOCAL_BUFFER (char, tdoc, doc_len+1);
    tdoc[doc_len] = '\0';
    if (! is.read (X_CAST (char *, tdoc), doc_len))
      goto data_read_error;
    doc = tdoc;
  }

  if (! is.read (X_CAST (char *, &tmp), 1))
    goto data_read_error;
  global = tmp ? 1 : 0;

  tmp = 0;
  if (! is.read (X_CAST (char *, &tmp), 1))
    goto data_read_error;

  // All cases except 255 kept for backwards compatibility
  switch (tmp)
    {
    case 1:
      tc = octave_value_typeinfo::lookup_type ("scalar");
      break;

    case 2:
      tc = octave_value_typeinfo::lookup_type ("matrix");
      break;

    case 3:
      tc = octave_value_typeinfo::lookup_type ("complex scalar");
      break;

    case 4:
      tc = octave_value_typeinfo::lookup_type ("complex matrix");
      break;

    case 5:
      {
	// XXX FIXME XXXX
	// This is cruft, since its for a save type that is old. Maybe
	// this is taking backward compatability too far!!
	FOUR_BYTE_INT len;
	if (! is.read (X_CAST (char *, &len), 4))
	  goto data_read_error;
	if (swap)
	  swap_4_bytes (X_CAST (char *, &len));
	OCTAVE_LOCAL_BUFFER (char, s, len+1);
	if (! is.read (X_CAST (char *, s), len))
	  goto data_read_error;
	s[len] = '\0';
	tc = s;

	// Early return, since don't want rest of this function
	return retval;
      }
      break;

    case 6:
      tc = octave_value_typeinfo::lookup_type ("range");
      break;

    case 7:
      tc = octave_value_typeinfo::lookup_type ("string");
      break;

    case 255:
      {
	// Read the saved variable type
	FOUR_BYTE_INT len;
	if (! is.read (X_CAST (char *, &len), 4))
	  goto data_read_error;
	if (swap)
	  swap_4_bytes (X_CAST (char *, &len));
	OCTAVE_LOCAL_BUFFER (char, s, len+1);
	if (! is.read (X_CAST (char *, s), len))
	  goto data_read_error;
	s[len] = '\0';
	std::string typ = s;
	tc = octave_value_typeinfo::lookup_type (typ);
      }
      break;
    default:
      goto data_read_error;
      break;
    }
  
  if (!tc.load_binary (is, swap, fmt))
    {
    data_read_error:
      error ("load: trouble reading binary file `%s'", filename.c_str ());
    }

  return retval;
}

// Save the data from TC along with the corresponding NAME, help
// string DOC, and global flag MARK_AS_GLOBAL on stream OS in the
// binary format described above for read_binary_data.

bool
save_binary_data (std::ostream& os, const octave_value& tc,
		  const std::string& name, const std::string& doc,
		  bool mark_as_global, bool save_as_floats) 
{
  FOUR_BYTE_INT name_len = name.length ();

  os.write (X_CAST (char *, &name_len), 4);
  os << name;

  FOUR_BYTE_INT doc_len = doc.length ();

  os.write (X_CAST (char *, &doc_len), 4);
  os << doc;

  unsigned char tmp;

  tmp = mark_as_global;
  os.write (X_CAST (char *, &tmp), 1);

  // 255 flags the new binary format
  tmp = 255;
  os.write (X_CAST (char *, &tmp), 1);

  // Write the string corresponding to the octave_value type
  std::string typ = tc.type_name ();
  FOUR_BYTE_INT len = typ.length ();
  os.write (X_CAST (char *, &len), 4);
  const char *btmp = typ.data ();
  os.write (X_CAST (char *, btmp), len);
      
  // The octave_value of tc is const. Make a copy...
  octave_value val = tc;

  // Call specific save function
  bool success = val.save_binary (os, save_as_floats);

  return (os && success);
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/

