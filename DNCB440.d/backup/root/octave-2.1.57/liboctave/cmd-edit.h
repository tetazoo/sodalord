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

#if !defined (octave_cmd_edit_h)
#define octave_cmd_edit_h 1

#include <cstdio>

#include <string>

#include "str-vec.h"

class
command_editor
{
protected:

  command_editor (void)
    : command_number (0) { }

public:

  typedef int (*startup_hook_fcn) (void);

  typedef int (*event_hook_fcn) (void);

  typedef std::string (*completion_fcn) (const std::string&, int);

  virtual ~command_editor (void) { }

  static void set_name (const std::string& n);

  static std::string readline (const std::string& prompt);

  static std::string readline (const std::string& prompt, bool& eof);

  static void set_input_stream (FILE *f);

  static FILE *get_input_stream (void);

  static void set_output_stream (FILE *f);

  static FILE *get_output_stream (void);

  static int terminal_rows (void);

  static int terminal_cols (void);

  static void clear_screen (void);

  static void resize_terminal (void);

  static std::string decode_prompt_string (const std::string& s);

  static void restore_terminal_state (void);

  static void blink_matching_paren (bool flag);

  static void set_basic_word_break_characters (const std::string& s);

  static void set_completer_word_break_characters (const std::string& s);

  static void set_basic_quote_characters (const std::string& s);

  static void set_completion_append_character (char c);

  static void set_completion_function (completion_fcn f);

  static completion_fcn get_completion_function (void);

  static string_vector generate_filename_completions (const std::string& text);

  static void insert_text (const std::string& text);

  static void newline (void);

  static void clear_undo_list (void);

  static void set_startup_hook (startup_hook_fcn f);

  static void restore_startup_hook (void);

  static void set_event_hook (event_hook_fcn f);

  static void restore_event_hook (void);

  static void read_init_file (const std::string& file = std::string ());

  static bool filename_completion_desired (bool);

  static int current_command_number (void);

  static void reset_current_command_number (int n);

  static void increment_current_command_number (void);

private:

  // No copying!

  command_editor (const command_editor&);

  command_editor& operator = (const command_editor&);

  static bool instance_ok (void);

  static void make_command_editor (void);

  // The real thing.
  static command_editor *instance;

protected:

  // To use something other than the GNU readline library, derive a new
  // class from command_editor, overload these functions as
  // necessary, and make instance point to the new class.

  virtual void do_set_name (const std::string&) { }

  std::string do_readline (const std::string& prompt)
    {
      bool eof;

      return do_readline (prompt, eof);
    }

  virtual std::string do_readline (const std::string&, bool&) = 0;

  virtual void do_set_input_stream (FILE *) = 0;

  virtual FILE *do_get_input_stream (void) = 0;

  virtual void do_set_output_stream (FILE *) = 0;

  virtual FILE *do_get_output_stream (void) = 0;

  virtual int do_terminal_rows (void) { return 24; }

  virtual int do_terminal_cols (void) { return 80; }

  virtual void do_clear_screen (void) { }

  virtual void do_resize_terminal (void) { }

  virtual std::string do_decode_prompt_string (const std::string&);

  virtual std::string newline_chars (void) { return "\n"; } 

  virtual void do_restore_terminal_state (void) { }

  virtual void do_blink_matching_paren (bool) { }

  virtual void do_set_basic_word_break_characters (const std::string&) { }

  virtual void do_set_completer_word_break_characters (const std::string&) { }

  virtual void do_set_basic_quote_characters (const std::string&) { }

  virtual void do_set_completion_append_character (char) { }

  virtual void do_set_completion_function (completion_fcn) { }

  virtual completion_fcn do_get_completion_function (void) const { return 0; }

  virtual string_vector do_generate_filename_completions (const std::string& text) = 0;

  virtual void do_insert_text (const std::string&) = 0;

  virtual void do_newline (void) = 0;

  virtual void do_clear_undo_list (void) { }

  virtual void do_set_startup_hook (startup_hook_fcn) { }

  virtual void do_restore_startup_hook (void) { }

  virtual void do_set_event_hook (event_hook_fcn) { }

  virtual void do_restore_event_hook (void) { }

  virtual void do_read_init_file (const std::string&) { }

  virtual bool do_filename_completion_desired (bool) { return false; }

  int read_octal (const std::string& s);

  void error (int);

  void error (const std::string&);

  // The current command number.
  int command_number;
};

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
