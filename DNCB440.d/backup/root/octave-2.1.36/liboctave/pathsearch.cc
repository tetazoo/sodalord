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

#include <cstdlib>

#include <string>

#include "lo-utils.h"
#include "oct-env.h"
#include "oct-kpse.h"
#include "pathsearch.h"
#include "str-vec.h"
#include "str-vec.h"

static bool octave_kpathsea_initialized = false;

string_vector
dir_path::elements (void)
{
  return initialized ? pv : string_vector ();
}

string_vector
dir_path::all_directories (void)
{
  int count = 0;
  string_vector retval;

  if (initialized)
    {
      int len = pv.length ();

      int nmax = len > 32 ? len : 32;

      retval.resize (len);

      for (int i = 0; i < len; i++)
	{
	  str_llist_type *elt_dirs
	    = ::octave_kpse_element_dirs (pv[i].c_str ());

	  if (elt_dirs)
	    {
	      str_llist_elt_type *dir;

	      for (dir = *elt_dirs; dir; dir = STR_LLIST_NEXT (*dir))
		{
		  char *elt_dir = STR_LLIST (*dir);

		  if (elt_dir)
		    {
		      if (count == nmax)
			nmax *= 2;

		      retval.resize (nmax);

		      retval[count++] = elt_dir;
		    }
		}
	    }
	}

      retval.resize (count);
    }

  return retval;
}

std::string
dir_path::find_first (const std::string& nm)
{
  std::string retval;

  if (initialized)
    {
      char *tmp = ::octave_kpse_path_search (p.c_str (), nm.c_str (), true);
      if (tmp)
	{
	  retval = tmp;
	  free (tmp);
	}
    }

  return retval;
}

string_vector
dir_path::find_all (const std::string& nm)
{
  string_vector retval;

  if (initialized)
    {
      char **tmp = ::octave_kpse_all_path_search (p.c_str (), nm.c_str ());

      if (tmp)
	{
	  int count = 0;
	  char **ptr = tmp;
	  while (*ptr++)
	    count++;

	  retval.resize (count);

	  for (int i = 0; i < count; i++)
	    retval[i] = tmp[i];
	}
    }

  return retval;
}

void
dir_path::set_program_name (const std::string& nm)
{
  std::string selfautodir = octave_env::getenv ("SELFAUTODIR");
  std::string selfautoloc = octave_env::getenv ("SELFAUTOLOC");
  std::string selfautoparent = octave_env::getenv ("SELFAUTOPARENT");

  ::octave_kpse_set_progname (nm.c_str ());

  // Calling kpse_set_progname has the unfortunate side-effect of
  // exporting the following variables.  If they were empty when we
  // started, we make them empty again so that they will not interfere
  // with TeX if it is run as a subprocess of Octave (if they were set
  // before, we want to preserve their values).
  //
  // XXX FIXME XXX -- is there a reasonable way to actually remove
  // them from the environment?

  if (selfautodir.empty ())
    octave_env::putenv ("SELFAUTODIR", "");

  if (selfautoloc.empty ())
    octave_env::putenv ("SELFAUTOLOC", "");

  if (selfautoparent.empty ())
    octave_env::putenv ("SELFAUTOPARENT", "");
}

void
dir_path::init (void)
{
  if (! octave_kpathsea_initialized)
    {
      char *s = getenv ("KPATHSEA_DEBUG");

      if (s)
	kpathsea_debug |= atoi (s);

      octave_kpathsea_initialized = true;
    }

  ::octave_kpse_clear_dir_cache ();

  char *t1 = 0;

  if (p_default.empty ())
    t1 = ::octave_kpse_path_expand (p_orig.c_str ());
  else
    {
      char *t2
	= ::octave_kpse_expand_default (p_orig.c_str (), p_default.c_str ());

      t1 = ::octave_kpse_path_expand (t2);

      if (t2)
	free (t2);
    }

  if (t1)
    {
      p = t1;
      free (t1);
    }
  else
    p = std::string ();

  int count = 0;
  char *path_elt = ::octave_kpse_path_element (p.c_str ());
  while (path_elt)
    {
      path_elt = ::octave_kpse_path_element (0);
      count++;
    }

  pv.resize (count);

  path_elt = ::octave_kpse_path_element (p.c_str ());

  for (int i = 0; i < count; i++)
    {
      pv[i] = path_elt;
      path_elt = ::octave_kpse_path_element (0);
    }

  initialized = true;
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
