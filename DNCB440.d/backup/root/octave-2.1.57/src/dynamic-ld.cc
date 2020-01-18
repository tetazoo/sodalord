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

#include <list>

#include "oct-time.h"
#include "file-stat.h"

#include <defaults.h>

#include "defun.h"
#include "dynamic-ld.h"
#include "parse.h"
#include "unwind-prot.h"
#include "utils.h"
#include "variables.h"

// TRUE means we print a warning if reloading a .oct file forces other
// functions to be cleared.
static bool Vwarn_reload_forces_clear;

class
octave_shlib_list
{
public:

  static void append (const octave_shlib& shl);

  static void remove (octave_shlib& shl);

  static void *search (const std::string& fcn_name, octave_shlib& shl,
		       octave_shlib::name_mangler mangler = 0);

private:

  octave_shlib_list (void) { }

  ~octave_shlib_list (void) { }

  void do_append (const octave_shlib& shl);

  void do_remove (octave_shlib& shl);

  void *do_search (const std::string& fcn_name, octave_shlib& shl,
		   octave_shlib::name_mangler mangler = 0);

  static octave_shlib_list *instance;

  static bool instance_ok (void);

  // List of libraries we have loaded.
  std::list<octave_shlib> lib_list;

  // No copying!

  octave_shlib_list (const octave_shlib_list&);

  octave_shlib_list& operator = (const octave_shlib_list&);
};

octave_shlib_list *octave_shlib_list::instance = 0;

void
octave_shlib_list::do_append (const octave_shlib& shl)
{
  lib_list.push_back (shl);
}

void
octave_shlib_list::do_remove (octave_shlib& shl)
{
  
  for (std::list<octave_shlib>::iterator p = lib_list.begin ();
       p != lib_list.end ();
       p++)
    {
      if (*p == shl)
	{
	  shl.close ();

	  lib_list.erase (p);

	  break;
	}
    }
}

void *
octave_shlib_list::do_search (const std::string& fcn_name, octave_shlib& shl,
			      octave_shlib::name_mangler mangler)
{
  void *function = 0;

  shl = octave_shlib ();

  for (std::list<octave_shlib>::iterator p = lib_list.begin ();
       p != lib_list.end ();
       p++)
    {
      function = p->search (fcn_name, mangler);

      if (function)
	{
	  shl = *p;

	  break;
	}
    }

  return function;
}

bool
octave_shlib_list::instance_ok (void)
{
  bool retval = true;

  if (! instance)
    instance = new octave_shlib_list ();

  if (! instance)
    {
      ::error ("unable to create shared library list object!");

      retval = false;
    }

  return retval;
}

void
octave_shlib_list::append (const octave_shlib& shl)
{
  if (instance_ok ())
    instance->do_append (shl);
}

void
octave_shlib_list::remove (octave_shlib& shl)
{
  if (instance_ok ())
    instance->do_remove (shl);
}

void *
octave_shlib_list::search (const std::string& fcn_name, octave_shlib& shl,
			   octave_shlib::name_mangler mangler)
{
  return (instance_ok ()) ? instance->do_search (fcn_name, shl, mangler) : 0;
}

octave_dynamic_loader *octave_dynamic_loader::instance = 0;

bool octave_dynamic_loader::doing_load = false;

bool
octave_dynamic_loader::instance_ok (void)
{
  bool retval = true;

  if (! instance)
    instance = new octave_dynamic_loader ();

  if (! instance)
    {
      ::error ("unable to create dynamic loader object!");

      retval = false;
    }

  return retval;
}

static
void clear_function (const std::string& fcn_name)
{
  if (Vwarn_reload_forces_clear)
    warning ("  %s", fcn_name.c_str ());

  curr_sym_tab->clear (fcn_name);

  if (curr_sym_tab != top_level_sym_tab)
    top_level_sym_tab->clear (fcn_name);

  fbi_sym_tab->clear (fcn_name);
}

bool
octave_dynamic_loader::do_load (const std::string& fcn_name,
				const std::string& file_name)
{
  bool retval = false;

  octave_shlib oct_file;

  unwind_protect::begin_frame ("octave_dynamic_loader::do_load");

  unwind_protect_bool (octave_dynamic_loader::doing_load);

  doing_load = true;

  void *function
    = octave_shlib_list::search (fcn_name, oct_file, mangle_name);

  if (! error_state)
    {
      if (function && oct_file.is_out_of_date ())
	{
	  int n = oct_file.number_of_functions_loaded ();

	  if (n > 0 && Vwarn_reload_forces_clear)
	    warning ("reloading %s clears the following functions:",
		     oct_file.file_name().c_str ());

	  oct_file.close (clear_function);

	  function = 0;
	}

      if (! function)
	{
	  std::string oct_file_name
	    = file_name.empty () ? oct_file_in_path (fcn_name) : file_name;

	  if (! oct_file_name.empty ())
	    {
	      oct_file.open (oct_file_name, Vwarn_future_time_stamp);

	      if (! error_state)
		{
		  if (oct_file)
		    {
		      octave_shlib_list::append (oct_file);

		      function = oct_file.search (fcn_name, mangle_name);
		    }
		  else
		    ::error ("%s is not a valid shared library",
			     oct_file_name.c_str ());
		}
	    }
	}
    }

  if (function)
    {
      octave_dld_fcn_installer f
	= X_CAST (octave_dld_fcn_installer, function);

      retval = f (oct_file);

      if (! retval)
	::error ("failed to install dld function `%s'", fcn_name.c_str ());
    }
  
  unwind_protect::run_frame ("octave_dynamic_loader::do_load");

  return retval;
}

bool
octave_dynamic_loader::do_remove (const std::string& fcn_name, octave_shlib& shl)
{
  bool retval = false;

  // We don't need to do anything if this is called because we are in
  // the process of reloading a .oct file that has changed.

  if (! doing_load)
    {
      retval = shl.remove (fcn_name);

      if (shl.number_of_functions_loaded () == 0)
	octave_shlib_list::remove (shl);
    }

  return retval;
}

bool
octave_dynamic_loader::load (const std::string& fcn_name,
			     const std::string& file_name)
{
  return (instance_ok ()) ? instance->do_load (fcn_name, file_name) : false;
}

bool
octave_dynamic_loader::remove (const std::string& fcn_name, octave_shlib& shl)
{
  return (instance_ok ()) ? instance->do_remove (fcn_name, shl) : false;
}

#define STRINGIFY(s) STRINGIFY1(s)
#define STRINGIFY1(s) #s

std::string
octave_dynamic_loader::mangle_name (const std::string& name)
{
#if defined (CXX_PREPENDS_UNDERSCORE)
  std::string retval ("_FS");
#else
  std::string retval ("FS");
#endif
  retval.append (name);
  retval.append ("_");
  retval.append (STRINGIFY (CXX_ABI));
  return retval;
}

static int
warn_reload_forces_clear (void)
{
  Vwarn_reload_forces_clear = check_preference ("warn_reload_forces_clear");

  return 0;
}

void
symbols_of_dynamic_ld (void)
{
  DEFVAR (warn_reload_forces_clear, true, warn_reload_forces_clear,
    "-*- texinfo -*-\n\
@defvr {Built-in Variable} warn_reload_forces_clear\n\
If several functions have been loaded from the same file, Octave must\n\
clear all the functions before any one of them can be reloaded.  If\n\
@code{warn_reload_forces_clear}, Octave will warn you when this happens,\n\
and print a list of the additional functions that it is forced to clear.\n\
@end defvr");
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
