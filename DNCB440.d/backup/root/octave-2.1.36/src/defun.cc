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

#include <iostream>
#include <string>

#include "defun.h"
#include "dynamic-ld.h"
#include "error.h"
#include "help.h"
#include "ov.h"
#include "ov-builtin.h"
#include "ov-dld-fcn.h"
#include "ov-mapper.h"
#include "oct-obj.h"
#include "pager.h"
#include "symtab.h"
#include "variables.h"

void
print_usage (const std::string& nm, bool just_usage)
{
  symbol_record *sym_rec = global_sym_tab->lookup (nm);

  if (sym_rec)
    {
      std::string h = sym_rec->help ();

      if (h.length () > 0)
	{
	  octave_stdout << "\n*** " << nm << ":\n\n";

	  display_help_text (octave_stdout, h);

	  octave_stdout << "\n";

	  if (! just_usage)
	    additional_help_message (octave_stdout);
	}
    }
  else
    warning ("no usage message found for `%s'", nm.c_str ());
}

void
check_version (const std::string& version, const std::string& fcn)
{
  if (version != OCTAVE_VERSION)
    warning ("incompatible version %s found in function `%s'",
	     version.c_str (), fcn.c_str ());
}

// Install variables and functions in the symbol tables.

void
install_builtin_mapper (octave_mapper *mf)
{
  symbol_record *sym_rec = global_sym_tab->lookup (mf->name (), true);

  unsigned int t
    = symbol_record::BUILTIN_FUNCTION | symbol_record::MAPPER_FUNCTION;

  sym_rec->unprotect ();
  sym_rec->define (mf, t);
  sym_rec->document (mf->doc_string ());
  sym_rec->make_eternal ();
  sym_rec->protect ();
}

void
install_builtin_function (octave_builtin::fcn f, const std::string& name,
			  const std::string& doc, bool is_text_fcn)
{
  symbol_record *sym_rec = global_sym_tab->lookup (name, true);

  unsigned int t = symbol_record::BUILTIN_FUNCTION;

  if (is_text_fcn)
    t |= symbol_record::TEXT_FUNCTION;

  sym_rec->unprotect ();
  sym_rec->define (new octave_builtin (f, name, doc), t);
  sym_rec->document (doc);
  sym_rec->make_eternal ();
  sym_rec->protect ();
}

void
install_builtin_constant (const std::string& name, const octave_value& val,
			  bool protect, const std::string& help)
{
  bind_builtin_constant (name, val, protect, false, help);
}

void
install_builtin_variable (const std::string& name, const octave_value& value,
			  bool protect, bool eternal,
			  symbol_record::change_function chg_fcn,
			  const std::string& doc)
{
  bind_builtin_variable (name, value, protect, eternal, chg_fcn, doc);
}

void
install_dld_function (octave_dld_function::fcn f, const std::string& name,
		      const octave_shlib& shl,
		      const std::string& doc, bool is_text_fcn)
{
  symbol_record *sym_rec = global_sym_tab->lookup (name, true);

  unsigned int t = symbol_record::DLD_FUNCTION;

  if (is_text_fcn)
    t |= symbol_record::TEXT_FUNCTION;

  sym_rec->unprotect ();
  sym_rec->define (new octave_dld_function (f, shl, name, doc), t);
  sym_rec->document (doc);
  sym_rec->make_eternal ();
  sym_rec->protect ();
}

void
alias_builtin (const std::string& alias, const std::string& name)
{
  symbol_record *sr_name = global_sym_tab->lookup (name);

  if (! sr_name)
    panic ("can't alias to undefined name!");

  symbol_record *sr_alias = global_sym_tab->lookup (alias, true);

  if (sr_alias)
    sr_alias->alias (sr_name);
  else
    panic ("can't find symbol record for builtin function `%s'",
	   alias.c_str ());
}

#if 0
// This is insufficient to really make it possible to define an alias
// for function.  There are a number of subtle problems related to
// automatically reloading functions.
DEFUN (alias, args, ,
  "alias (alias, name)")
{
  octave_value retval;

  int nargin = args.length ();

  if (nargin == 2)
    {
      string alias = args(0).string_value ();
      string name = args(1).string_value ();

      if (! error_state)
	{
	  symbol_record *sr_name = lookup_by_name (name, false);

	  if (sr_name && sr_name->is_function ())
	    {
	      symbol_record *sr_alias = global_sym_tab->lookup (alias, true);

	      if (sr_alias)
		sr_alias->alias (sr_name);
	      else
		error ("alias: unable to insert `%s' in symbol table",
		       alias.c_str ());
	    }
	  else
	    error ("alias: function `%s' does not exist", name.c_str ());
	}
    }
  else
    print_usage ("alias");

  return retval;
}
#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
