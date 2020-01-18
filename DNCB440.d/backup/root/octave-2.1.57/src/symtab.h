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

#if !defined (octave_symtab_h)
#define octave_symtab_h 1

#if defined (__GNUG__) && defined (USE_PRAGMA_INTERFACE_IMPLEMENTATION)
#pragma interface
#endif

#include <cassert>

#include <string>
#include <stack>

#include "lo-sstream.h"
#include "oct-alloc.h"
#include "str-vec.h"

#include "ov.h"

class octave_lvalue;

class string_vector;

class symbol_record;
class symbol_table;

// Individual records in a symbol table.

class
symbol_record
{
public:

  // If you add or delete an entry here, you'll also need to change
  // the width parameter in the declaration for symbol_type below...

  enum TYPE
    {
      UNKNOWN = 0,
      USER_FUNCTION = 1,
      USER_VARIABLE = 2,
      DLD_FUNCTION = 4,
      BUILTIN_FUNCTION = 8,
      COMMAND = 16,
      MAPPER_FUNCTION = 32,
      BUILTIN_VARIABLE = 64,
      BUILTIN_CONSTANT = 128
    };

private:

  // Variables or functions.

  class symbol_def
  {
  public:

    symbol_def (const octave_value& val = octave_value (),
		unsigned int sym_type = 0)
      : symbol_type (sym_type), eternal (0), read_only (0), help_string (),
	definition (val), count (1) { }

    ~symbol_def (void) { }

    bool is_constant (void) const
      { return (symbol_type & symbol_record::BUILTIN_CONSTANT); }

    bool is_variable (void) const
      {
	return (symbol_type & symbol_record::USER_VARIABLE
		|| symbol_type & symbol_record::BUILTIN_VARIABLE);
      }

    // It's not necessary to check for COMMAND and MAPPER_FUNCTION
    // here.  Those tags are just used as additional qualifiers for
    // the other types of functions.

    bool is_function (void) const
      {
	return (symbol_type & symbol_record::USER_FUNCTION
		|| symbol_type & symbol_record::DLD_FUNCTION
		|| symbol_type & symbol_record::BUILTIN_FUNCTION);
      }

    bool is_user_variable (void) const
      { return (symbol_type & symbol_record::USER_VARIABLE); }

    void mark_as_command (void)
      { symbol_type |= symbol_record::COMMAND; }

    void unmark_command (void)
      { symbol_type &= ~symbol_record::COMMAND; }

    bool is_command (void) const
      { return (symbol_type & symbol_record::COMMAND); }

    bool is_mapper_function (void) const
      { return (symbol_type & symbol_record::MAPPER_FUNCTION); }

    bool is_user_function (void) const
      { return (symbol_type & symbol_record::USER_FUNCTION); }

    bool is_builtin_constant (void) const
      { return (symbol_type & symbol_record::BUILTIN_CONSTANT); }

    bool is_builtin_variable (void) const
      { return (symbol_type & symbol_record::BUILTIN_VARIABLE); }

    bool is_builtin_function (void) const
      { return (symbol_type & symbol_record::BUILTIN_FUNCTION); }

    bool is_dld_function (void) const
      { return (symbol_type & symbol_record::DLD_FUNCTION); }

    // XXX FIXME XXX
    bool is_map_element (const std::string& /* elts */) const
      { return false; }

    bool is_defined (void) const
      { return definition.is_defined (); }

    bool is_read_only (void) const
      { return read_only; }

    bool is_eternal (void) const
      { return eternal; }

    int rows (void) const { return definition.rows (); }
    int columns (void) const { return definition.columns (); }

    std::string type_name (void) const { return definition.type_name (); }

    std::string type_as_string (void) const;

    void type (std::ostream& os, const std::string& name, bool pr_type_info,
	       bool quiet, bool pr_orig_txt);

    std::string which (const std::string& name);

    void which (std::ostream& os, const std::string& name);

    void define (const octave_value& val, unsigned int sym_type)
      {
	definition = val;
	symbol_type = sym_type;
      }

    void protect (void) { read_only = 1; }

    void unprotect (void) { read_only = 0; }

    void make_eternal (void) { eternal = 1; }

    octave_value& def (void) { return definition; }

    std::string help (void) const { return help_string; }

    void document (const std::string& h) { help_string = h; }

    unsigned int type (void) { return symbol_type; }

    void *operator new (size_t size)
      { return allocator.alloc (size); }

    void operator delete (void *p, size_t size)
      { allocator.free (p, size); }

    static octave_allocator allocator;

    // The type of this symbol (see the enum above).
    unsigned int symbol_type : 8;

    // Nonzero means this variable cannot be cleared.
    unsigned int eternal : 1;

    // Nonzero means this variable cannot be given a new value.
    unsigned int read_only : 1;

    // The doc string associated with this variable.
    std::string help_string;

    // The value of this definition.  See ov.h and related files.
    octave_value definition;

    // Reference count.
    int count;

    void print_info (std::ostream& os,
		     const std::string& prefix = std::string ()) const;

    // No copying!

    symbol_def (const symbol_def& sd);

    symbol_def& operator = (const symbol_def& sd);
  };

public:

  typedef int (*change_function) (void);

  symbol_record (void)
    : formal_param (0), linked_to_global (0), tagged_static (0),
      can_hide_function (1), nm (), chg_fcn (0),
      definition (new symbol_def ()), next_elem (0) { }

  // XXX FIXME XXX -- kluge alert!  We obviously need a better way of
  // handling allow_shadow!

  symbol_record (const std::string& n, symbol_record *nxt)
    : formal_param (0), linked_to_global (0), tagged_static (0),
      can_hide_function (n != "__end__"), nm (n), chg_fcn (0),
      definition (new symbol_def ()), next_elem (nxt) { }

  ~symbol_record (void) { }

  std::string name (void) const { return nm; }

  std::string help (void) const { return definition->help (); }

  octave_value& def (void) { return definition->def (); }

  void rename (const std::string& new_name);

  bool is_function (void) const
    { return definition->is_function (); }

  void mark_as_command (void)
    { definition->mark_as_command (); }

  void unmark_command (void)
    { definition->unmark_command (); }

  bool is_command (void) const
    { return definition->is_command (); }

  bool is_mapper_function (void) const
    { return definition->is_mapper_function (); }

  bool is_user_function (void) const
    { return definition->is_user_function (); }

  bool is_builtin_function (void) const
    { return definition->is_builtin_function (); }

  bool is_dld_function (void) const
    { return definition->is_dld_function (); }

  bool is_constant (void) const
    { return definition->is_constant (); }

  bool is_builtin_constant (void) const
    { return definition->is_builtin_constant (); }

  bool is_variable (void) const
    { return definition->is_variable (); }

  bool is_user_variable (void) const
    { return definition->is_user_variable (); }

  bool is_builtin_variable (void) const
    { return definition->is_builtin_variable (); }

  bool is_map_element (const std::string& elts) const
    { return definition->is_map_element (elts); }

  unsigned int type (void) const { return definition->type (); }

  bool is_defined (void) const { return definition->is_defined (); }

  bool is_read_only (void) const { return definition->is_read_only (); }

  bool is_eternal (void) const { return definition->is_eternal (); }

  void protect (void) { definition->protect (); }

  void unprotect (void) { definition->unprotect (); }

  void make_eternal (void) { definition->make_eternal (); }

  void set_change_function (change_function f) { chg_fcn = f; }

  void define (const octave_value& v, unsigned int sym_type = USER_VARIABLE);

  void define_builtin_var (const octave_value& v);

  bool define_builtin_const (const octave_value& v);

  bool define (octave_function *f, unsigned int sym_type);

  void document (const std::string& h) { definition->document (h); }

  void clear (void);

  void alias (symbol_record *s);

  void mark_as_formal_parameter (void);
  bool is_formal_parameter (void) const { return formal_param; }

  void mark_as_linked_to_global (void);
  bool is_linked_to_global (void) const { return linked_to_global; }

  void mark_as_static (void);
  bool is_static (void) const { return tagged_static; }
  void unmark_static (void) { tagged_static = false; }

  int rows (void) const { return definition->rows (); }
  int columns (void) const { return definition->columns (); }

  std::string type_name (void) const { return definition->type_name (); }

  std::string type_as_string (void) const
    { return definition->type_as_string (); }

  void type (std::ostream& os, bool pr_type_info, bool quiet, bool pr_orig_txt)
    { definition->type (os, name (), pr_type_info, quiet, pr_orig_txt); }

  std::string which (void) { return definition->which (name ()); }

  void which (std::ostream& os) { definition->which (os, name ()); }

  octave_value& variable_value (void);
  octave_lvalue variable_reference (void);

  symbol_record *next (void) const { return next_elem; }

  void chain (symbol_record *s) { next_elem = s; }

  void push_context (void);

  void pop_context (void);

  void print_symbol_info_line (std::ostream& os) const;

  void print_info (std::ostream& os,
		   const std::string& prefix = std::string ()) const;

private:

  unsigned int formal_param : 1;
  unsigned int linked_to_global : 1;
  unsigned int tagged_static : 1;
  unsigned int can_hide_function : 1;

  std::string nm;
  change_function chg_fcn;
  symbol_def *definition;
  symbol_record *next_elem;

  // This should maybe be one stack with a structure containing all the
  // items we need to save for recursive calls...
  std::stack <symbol_def *> context;
  std::stack <unsigned int> global_link_context;

  bool read_only_error (const char *action);

  void link_to_builtin_variable (void);

  // No copying!

  symbol_record (const symbol_record& s);

  symbol_record& operator = (const symbol_record& s);
};

// A symbol table.

#define SYMTAB_LOCAL_SCOPE 1
#define SYMTAB_GLOBAL_SCOPE 2

#define SYMTAB_ALL_SCOPES (SYMTAB_LOCAL_SCOPE | SYMTAB_GLOBAL_SCOPE)

#define SYMTAB_ALL_TYPES (symbol_record::USER_FUNCTION \
			  | symbol_record::USER_VARIABLE \
			  | symbol_record::DLD_FUNCTION \
			  | symbol_record::BUILTIN_FUNCTION \
			  | symbol_record::COMMAND \
			  | symbol_record::MAPPER_FUNCTION \
			  | symbol_record::BUILTIN_VARIABLE \
			  | symbol_record::BUILTIN_CONSTANT)

#define SYMTAB_VARIABLES (symbol_record::USER_VARIABLE \
			  | symbol_record::BUILTIN_VARIABLE)

class
symbol_table
{
public:

  symbol_table (unsigned int tab_size = 128,
		const std::string& nm = std::string ())
    : table_size (tab_size), table (new symbol_record [table_size]),
      table_name (nm)
    {
      assert ((tab_size % 2) == 0);

      if (table_name.empty ())
	{
	  OSSTREAM buf;
	  buf << symtab_count++ << OSSTREAM_ENDS;
	  table_name = OSSTREAM_STR (buf);
	  OSSTREAM_FREEZE (buf);
	}
    }

  ~symbol_table (void)
    {
      clear ();
      delete [] table;
    }

  symbol_record *lookup (const std::string& nm, bool insert = false,
			 bool warn = false);

  void rename (const std::string& old_name, const std::string& new_name);

  void clear (void);

  void clear_variables (void);
  void clear_functions (void);
  void clear_globals (void);

  bool clear (const std::string& nm);

  bool clear_variable (const std::string& nm);
  bool clear_function (const std::string& nm);
  bool clear_global (const std::string& nm);

  bool clear_variable_pattern (const std::string& pat);
  bool clear_function_pattern (const std::string& pat);
  bool clear_global_pattern (const std::string& pat);

  int size (void) const;

  Array<symbol_record *>
  symbol_list (const string_vector& pats = string_vector (),
	       unsigned int type = SYMTAB_ALL_TYPES,
	       unsigned int scope = SYMTAB_ALL_SCOPES) const;


  string_vector
  name_list (const string_vector& pats = string_vector (),
	     bool sort = false, unsigned int type = SYMTAB_ALL_TYPES,
	     unsigned int scope = SYMTAB_ALL_SCOPES) const;

  string_vector
  user_function_name_list (void) const
    {
      return name_list
	(string_vector (), false,
	 symbol_record::USER_FUNCTION|symbol_record::DLD_FUNCTION,
	 SYMTAB_ALL_SCOPES);
    }

  string_vector
  global_variable_name_list (void) const
    {
      return name_list
	(string_vector (), false, SYMTAB_VARIABLES, SYMTAB_GLOBAL_SCOPE);
    }

  string_vector
  variable_name_list (void) const
    {
      return name_list
	(string_vector (), false, SYMTAB_VARIABLES, SYMTAB_LOCAL_SCOPE);
    }

  int maybe_list (const char *header, const string_vector& argv,
		  std::ostream& os, bool show_verbose,
		  unsigned type, unsigned scope);
  
  Array<symbol_record *> glob (const std::string& pat = std::string ("*"),
			       unsigned int type = SYMTAB_ALL_TYPES,
			       unsigned int scope = SYMTAB_ALL_SCOPES) const;

  void push_context (void);

  void pop_context (void);

  void print_info (std::ostream& os) const;

private:

  unsigned int table_size;

  symbol_record *table;

  std::string table_name;

  static unsigned long int symtab_count;

  unsigned int hash (const std::string& s);

  // No copying!

  symbol_table (const symbol_table&);

  symbol_table& operator = (const symbol_table&);
};

#endif

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
