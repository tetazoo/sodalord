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

#if !defined (octave_octave_stream_h)
#define octave_octave_stream_h 1

class Matrix;
class string_vector;
class octave_value;
class octave_value_list;

#include <iostream>
#include <string>

#include "Array.h"
#include "data-conv.h"
#include "lo-sstream.h"
#include "lo-utils.h"
#include "mach-info.h"

class
scanf_format_elt
{
public:

  enum special_conversion
    {
      whitespace_conversion = 1,
      literal_conversion = 2
    };

  scanf_format_elt (const char *txt = 0, int w = 0, bool d = false,
		    char typ = '\0', char mod = '\0',
		    const std::string& ch_class = std::string ())
    : text (strsave (txt)), width (w), discard (d), type (typ),
      modifier (mod), char_class (ch_class) { }

  scanf_format_elt (const scanf_format_elt& e)
    : text (strsave (e.text)), width (e.width), discard (e.discard),
      type (e.type), modifier (e.modifier), char_class (e.char_class) { }

  scanf_format_elt& operator = (const scanf_format_elt& e)
    {
      if (this != &e)
	{
	  text = strsave (e.text);
	  width = e.width;
	  discard = e.discard;
	  type = e.type;
	  modifier = e.modifier;
	  char_class = e.char_class;
	}

      return *this;
    }

  ~scanf_format_elt (void) { delete [] text; }

  // The C-style format string.
  const char *text;

  // The maximum field width.
  int width;

  // TRUE if we are not storing the result of this conversion.
  bool discard;

  // Type of conversion -- `d', `i', `o', `u', `x', `e', `f', `g',
  // `c', `s', `p', `%', or `['.
  char type;

  // A length modifier -- `h', `l', or `L'.
  char modifier;

  // The class of characters in a `[' format.
  std::string char_class;
};

class
scanf_format_list
{
public:

  scanf_format_list (const std::string& fmt = std::string ());

  ~scanf_format_list (void);

  int num_conversions (void) { return nconv; }

  // The length can be different than the number of conversions.
  // For example, "x %d y %d z" has 2 conversions but the length of
  // the list is 3 because of the characters that appear after the
  // last conversion.

  int length (void) { return list.length (); }

  const scanf_format_elt *first (void)
    {
      curr_idx = 0;
      return current ();
    }

  const scanf_format_elt *current (void) const
    { return list.length () > 0 ? list.elem (curr_idx) : 0; }

  const scanf_format_elt *next (bool cycle = true)
    {
      curr_idx++;

      if (curr_idx >= list.length ())
	{
	  if (cycle)
	    curr_idx = 0;
	  else
	    return 0;
	}
      return current ();
    }

  void printme (void) const;

  bool ok (void) const { return (nconv >= 0); }

  operator bool () const { return ok (); }

  bool all_character_conversions (void);

  bool all_numeric_conversions (void);

private:

  // Number of conversions specified by this format string, or -1 if
  // invalid conversions have been found.
  int nconv;

  // Index to current element;
  int curr_idx;

  // List of format elements.
  Array<scanf_format_elt*> list;

  // Temporary buffer.
  OSSTREAM *buf;

  void add_elt_to_list (int width, bool discard, char type, char modifier,
			int& num_elts,
			const std::string& char_class = std::string ()); 

  void process_conversion (const std::string& s, int& i, int n, int& width,
			   bool& discard, char& type, char& modifier,
			   int& num_elts);

  int finish_conversion (const std::string& s, int& i, int n, int& width,
			 bool discard, char& type, char modifier,
			 int& num_elts);
  // No copying!

  scanf_format_list (const scanf_format_list&);

  scanf_format_list& operator = (const scanf_format_list&);
};

class
printf_format_elt
{
public:

  printf_format_elt (const char *txt = 0, int n = 0, int w = 0,
		     int p = 0, const std::string& f = std::string (),
		     char typ = '\0', char mod = '\0')
    : text (strsave (txt)), args (n), fw (w), prec (p), flags (f),
      type (typ), modifier (mod) { }

  printf_format_elt (const printf_format_elt& e)
    : text (strsave (e.text)), args (e.args), fw (e.fw), prec (e.prec),
      flags (e.flags), type (e.type), modifier (e.modifier) { }

  printf_format_elt& operator = (const printf_format_elt& e)
    {
      if (this != &e)
	{
	  text = strsave (e.text);
	  args = e.args;
	  fw = e.fw;
	  prec = e.prec;
	  flags = e.flags;
	  type = e.type;
	  modifier = e.modifier;
	}

      return *this;
    }

  ~printf_format_elt (void) { delete [] text; }
 
  // The C-style format string.
  const char *text;

  // How many args do we expect to consume?
  int args;

  // Field width.
  int fw;

  // Precision.
  int prec;

  // Flags -- `-', `+', ` ', `0', or `#'.
  std::string flags;

  // Type of conversion -- `d', `i', `o', `x', `X', `u', `c', `s',
  // `f', `e', `E', `g', `G', `p', or `%'
  char type;

  // A length modifier -- `h', `l', or `L'.
  char modifier;
};

class
printf_format_list
{
public:

  printf_format_list (const std::string& fmt = std::string ());

  ~printf_format_list (void);

  int num_conversions (void) { return nconv; }

  const printf_format_elt *first (void)
    {
      curr_idx = 0;
      return current ();
    }

  const printf_format_elt *current (void) const
    { return list.length () > 0 ? list.elem (curr_idx) : 0; }

  const printf_format_elt *next (bool cycle = true)
    {
      curr_idx++;

      if (curr_idx >= list.length ())
	{
	  if (cycle)
	    curr_idx = 0;
	  else
	    return 0;
	}

      return current ();
    }

  bool last_elt_p (void) { return (curr_idx + 1 == list.length ()); }

  void printme (void) const;

  bool ok (void) const { return (nconv >= 0); }

  operator bool () const { return ok (); }

private:

  // Number of conversions specified by this format string, or -1 if
  // invalid conversions have been found.
  int nconv;

  // Index to current element;
  int curr_idx;

  // List of format elements.
  Array<printf_format_elt*> list;

  // Temporary buffer.
  OSSTREAM *buf;

  void add_elt_to_list (int args, const std::string& flags, int fw,
			int prec, char type, char modifier,
 			int& num_elts);
 
  void process_conversion (const std::string& s, int& i, int n,
			   int& args, std::string& flags, int& fw,
			   int& prec, char& modifier, char& type,
			   int& num_elts); 
 
  void finish_conversion (const std::string& s, int& i, int args,
			  const std::string& flags, int fw, int prec,
			  char modifier, char& type, int& num_elts);

  // No copying!

  printf_format_list (const printf_format_list&);

  printf_format_list& operator = (const printf_format_list&);
};

// Provide an interface for Octave streams.

class
octave_base_stream
{
friend class octave_stream;

public:

  octave_base_stream (std::ios::openmode arg_md = std::ios::in|std::ios::out,
		      oct_mach_info::float_format ff = oct_mach_info::flt_fmt_native)
    : count (0), md (arg_md), flt_fmt (ff), fail (false), open_state (true)
  { }

  virtual ~octave_base_stream (void) { }

  // The remaining functions are not specific to input or output only,
  // and must be provided by the derived classes.

  // Position a stream at OFFSET relative to ORIGIN.

  virtual int seek (long offset, int origin) = 0;

  // Return current stream position.

  virtual long tell (void) = 0;

  // Return TRUE if EOF has been reached on this stream.

  virtual bool eof (void) const = 0;

  // The name of the file.

  virtual std::string name (void) const = 0;

  // If the derived class provides this function and it returns a
  // pointer to a valid istream, scanf(), read(), getl(), and gets()
  // will automatically work for this stream.

  virtual std::istream *input_stream (void) { return 0; }

  // If the derived class provides this function and it returns a
  // pointer to a valid ostream, flush(), write(), and printf() will
  // automatically work for this stream.

  virtual std::ostream *output_stream (void) { return 0; }

  // Return TRUE if this stream is open.

  bool is_open (void) const { return open_state; }

  virtual void do_close (void) { }

  void close (void)
    {
      if (is_open ())
	{
	  open_state = false;
	  do_close ();
	}
    }

  int file_number (void);

  bool ok (void) const { return ! fail; }

  // Return current error message for this stream.

  std::string error (bool clear, int& err_num);

protected:

  int mode (void) const { return md; }

  oct_mach_info::float_format float_format (void) const { return flt_fmt; }

  // Set current error state and set fail to TRUE.

  void error (const std::string& msg);
  void error (const std::string& who, const std::string& msg);

  // Clear any error message and set fail to FALSE.

  void clear (void);

private:

  // A reference count.
  int count;

  // The permission bits for the file.  Should be some combination of
  // std::ios::open_mode bits.
  int md;

  // Data format.
  oct_mach_info::float_format flt_fmt;

  // TRUE if an error has occurred.
  bool fail;

  // TRUE if this stream is open.
  bool open_state;

  // Should contain error message if fail is TRUE.
  std::string errmsg;

  // Functions that are defined for all input streams (input streams
  // are those that define is).

  std::string do_gets (int max_len, bool& err, bool strip_newline,
		       const std::string& who /* = "gets" */);

  std::string getl (int max_len, bool& err, const std::string& who /* = "getl" */);
  std::string gets (int max_len, bool& err, const std::string& who /* = "gets" */);

  octave_value do_read (int nr, int nc, oct_data_conv::data_type dt,
			int skip, oct_mach_info::float_format flt_fmt,
			int& count);

  octave_value read (const Array<double>& size, oct_data_conv::data_type dt,
		     int skip, oct_mach_info::float_format flt_fmt,
		     int& count);

  octave_value do_scanf (scanf_format_list& fmt_list, int nr, int nc,
			 bool one_elt_size_spec, int& count,
			 const std::string& who /* = "scanf" */);

  octave_value scanf (const std::string& fmt, const Array<double>& size,
		      int& count, const std::string& who /* = "scanf" */);

  bool do_oscanf (const scanf_format_elt *elt, octave_value&,
		  const std::string& who /* = "scanf" */);

  octave_value_list oscanf (const std::string& fmt,
			    const std::string& who /* = "scanf" */);

  // Functions that are defined for all output streams (output streams
  // are those that define os).

  int flush (void);

  int write (const octave_value& data, oct_data_conv::data_type dt,
	     int skip, oct_mach_info::float_format flt_fmt);

  int do_printf (printf_format_list& fmt_list, const octave_value_list& args,
		 const std::string& who /* = "printf" */);

  int printf (const std::string& fmt, const octave_value_list& args,
	      const std::string& who /* = "printf" */);

  int puts (const std::string& s, const std::string& who /* = "puts" */);

  // We can always do this in terms of seek(), so the derived class
  // only has to provide that.

  int rewind (void);

  void invalid_operation (const std::string& who, const char *rw);

  // No copying!

  octave_base_stream (const octave_base_stream&);

  octave_base_stream& operator = (const octave_base_stream&);
};

class
octave_stream
{
public:

  octave_stream (octave_base_stream *bs = 0);

  ~octave_stream (void);

  octave_stream (const octave_stream&);

  octave_stream& operator = (const octave_stream&);

  int flush (void);

  std::string getl (int max_len, bool& err, const std::string& who /* = "getl" */);
  std::string getl (const octave_value& max_len, bool& err,
		    const std::string& who /* = "getl" */);

  std::string gets (int max_len, bool& err, const std::string& who /* = "gets" */);
  std::string gets (const octave_value& max_len, bool& err,
		    const std::string& who /* = "gets" */);

  int seek (long offset, int origin);
  int seek (const octave_value& offset, const octave_value& origin);

  long tell (void);

  int rewind (void);

  bool is_open (void) const;

  void close (void);

  octave_value read (const Array<double>& size, oct_data_conv::data_type dt,
		     int skip, oct_mach_info::float_format flt_fmt,
		     int& count);

  int write (const octave_value& data, oct_data_conv::data_type dt,
	     int skip, oct_mach_info::float_format flt_fmt);

  octave_value scanf (const std::string& fmt, const Array<double>& size,
		      int& count, const std::string& who /* = "scanf" */);

  octave_value_list oscanf (const std::string& fmt,
			    const std::string& who /* = "scanf" */);

  int printf (const std::string& fmt, const octave_value_list& args,
	      const std::string& who /* = "printf" */);

  int puts (const std::string& s, const std::string& who /* = "puts" */);
  int puts (const octave_value& s, const std::string& who /* = "puts" */);

  bool eof (void) const;

  std::string error (bool clear, int& err_num);

  std::string error (bool clear = false)
    {
      int err_num;
      return error (clear, err_num);
    }

  // Set the error message and state.

  void error (const std::string& msg)
    {
      if (rep)
	rep->error (msg);
    }

  void error (const char *msg) { error (std::string (msg)); }

  int file_number (void) { return rep ? rep->file_number () : -1; }

  bool is_valid (void) const { return (rep != 0); }

  bool ok (void) const { return rep && rep->ok (); }

  operator bool () const { return ok (); }

  std::string name (void) const;

  int mode (void) const;

  oct_mach_info::float_format float_format (void) const;

  static std::string mode_as_string (int mode);

  std::istream *input_stream (void) { return rep ? rep->input_stream () : 0; }

  std::ostream *output_stream (void) { return rep ? rep->output_stream () : 0; }

private:

  // The actual representation of this stream.
  octave_base_stream *rep;

  void invalid_stream_error (const std::string& who) const;

  bool stream_ok (const std::string& who, bool clear = true) const
    {
      bool retval = true;

      if (rep)
	{
	  if (clear)
	    rep->clear ();
	}
      else
	{
	  retval = false;
	  invalid_stream_error (who);
	}

      return retval;
    }
};

class
octave_stream_list
{
protected:

  octave_stream_list (void) : list (32), curr_len (0) { }

public:

  ~octave_stream_list (void) { }

  static bool instance_ok (void);

  static octave_value insert (const octave_stream& os);

  static octave_stream
  lookup (int fid, const std::string& who = std::string ());

  static octave_stream
  lookup (const octave_value& fid, const std::string& who = std::string ());

  static int remove (int fid, const std::string& who = std::string ());
  static int remove (const octave_value& fid,
		     const std::string& who = std::string ());

  static void clear (void);

  static string_vector get_info (int fid);
  static string_vector get_info (const octave_value& fid);

  static std::string list_open_files (void);

  static octave_value open_file_numbers (void);

  static int get_file_number (const octave_value& fid);

private:

  Array<octave_stream> list;

  int curr_len;

  static octave_stream_list *instance;

  octave_value do_insert (const octave_stream& os);

  octave_stream do_lookup (int fid, const std::string& who = std::string ()) const;
  octave_stream do_lookup (const octave_value& fid,
			   const std::string& who = std::string ()) const;

  int do_remove (int fid, const std::string& who = std::string ());
  int do_remove (const octave_value& fid, const std::string& who = std::string ());

  void do_clear (void);

  string_vector do_get_info (int fid) const;
  string_vector do_get_info (const octave_value& fid) const;

  std::string do_list_open_files (void) const;

  octave_value do_open_file_numbers (void) const;

  int do_get_file_number (const octave_value& fid) const;
};

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
