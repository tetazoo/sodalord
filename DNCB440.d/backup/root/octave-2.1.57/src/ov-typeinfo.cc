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

#if defined (__GNUG__) && defined (USE_PRAGMA_INTERFACE_IMPLEMENTATION)
#pragma implementation
#endif

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "ov-typeinfo.h"

#include "defun.h"
#include "error.h"
#include "oct-obj.h"

const int
octave_value_typeinfo::init_tab_sz (16);

octave_value_typeinfo *
octave_value_typeinfo::instance (0);

#include <Array.h>
#include <Array2.h>
#include <Array3.h>

#include <Array.cc>

INSTANTIATE_ARRAY (unary_op_fcn);
template class Array2<unary_op_fcn>;

INSTANTIATE_ARRAY (non_const_unary_op_fcn);
template class Array2<non_const_unary_op_fcn>;

INSTANTIATE_ARRAY (binary_op_fcn);
template class Array2<binary_op_fcn>;
template class Array3<binary_op_fcn>;

INSTANTIATE_ARRAY (assign_op_fcn);
template class Array2<assign_op_fcn>;
template class Array3<assign_op_fcn>;

INSTANTIATE_ARRAY (type_conv_fcn);
template class Array2<type_conv_fcn>;

bool
octave_value_typeinfo::instance_ok (void)
{
  bool retval = true;
  if (! instance)
    instance = new octave_value_typeinfo ();

  if (! instance)
    {
      ::error ("unable to create value type info object!");

      retval = false;
    }

  return retval;
}

int
octave_value_typeinfo::register_type (const std::string& t_name,
				      const std::string& c_name,
				      const octave_value& val)
{
  return (instance_ok ())
    ? instance->do_register_type (t_name, c_name, val) : -1;
}

bool
octave_value_typeinfo::register_unary_op (octave_value::unary_op op,
					   int t, unary_op_fcn f)
{
  return (instance_ok ())
    ? instance->do_register_unary_op (op, t, f) : false;
}

bool
octave_value_typeinfo::register_non_const_unary_op (octave_value::unary_op op,
						    int t,
						    non_const_unary_op_fcn f)
{
  return (instance_ok ())
    ? instance->do_register_non_const_unary_op (op, t, f) : false;
}

bool
octave_value_typeinfo::register_binary_op (octave_value::binary_op op,
					   int t1, int t2,
					   binary_op_fcn f)
{
  return (instance_ok ())
    ? instance->do_register_binary_op (op, t1, t2, f) : false;
}

bool
octave_value_typeinfo::register_assign_op (octave_value::assign_op op,
					   int t_lhs, int t_rhs,
					   assign_op_fcn f)
{
  return (instance_ok ())
    ? instance->do_register_assign_op (op, t_lhs, t_rhs, f) : -1;
}

bool
octave_value_typeinfo::register_assignany_op (octave_value::assign_op op,
					       int t_lhs, assign_op_fcn f)
{
  return (instance_ok ())
    ? instance->do_register_assignany_op (op, t_lhs, f) : -1;
}

bool
octave_value_typeinfo::register_pref_assign_conv (int t_lhs, int t_rhs,
						  int t_result) 
{
  return (instance_ok ())
    ? instance->do_register_pref_assign_conv (t_lhs, t_rhs, t_result) : false;
}

bool
octave_value_typeinfo::register_widening_op (int t, int t_result,
					     type_conv_fcn f)
{
  return (instance_ok ())
    ? instance->do_register_widening_op (t, t_result, f) : false;
}

// XXX FIXME XXX -- we should also store all class names and provide a
// way to list them (calling class with nargin == 0?).

int
octave_value_typeinfo::do_register_type (const std::string& t_name,
					 const std::string& c_name,
					 const octave_value& val)
{
  int i = 0;

  for (i = 0; i < num_types; i++)
    if (t_name == types (i))
      return i;

  int len = types.length ();

  if (i == len)
    {
      len *= 2;

      types.resize (len, std::string ());

      vals.resize (len, octave_value ());

      unary_ops.resize (static_cast<int> (octave_value::num_unary_ops),
			len, static_cast<unary_op_fcn> (0));

      non_const_unary_ops.resize
	(static_cast<int> (octave_value::num_unary_ops),
	 len, static_cast<non_const_unary_op_fcn> (0));

      binary_ops.resize (static_cast<int> (octave_value::num_binary_ops),
			 len, len, static_cast<binary_op_fcn> (0));

      assign_ops.resize (static_cast<int> (octave_value::num_assign_ops),
			 len, len, static_cast<assign_op_fcn> (0));

      assignany_ops.resize (static_cast<int> (octave_value::num_assign_ops),
			    len, static_cast<assign_op_fcn> (0));

      pref_assign_conv.resize (len, len, -1);

      widening_ops.resize (len, len, static_cast<type_conv_fcn> (0));
    }

  types (i) = t_name;

  vals (i) = val;

  num_types++;

  return i;
}

bool
octave_value_typeinfo::do_register_unary_op (octave_value::unary_op op,
					     int t, unary_op_fcn f)
{
  if (lookup_unary_op (op, t))
    {
      std::string op_name = octave_value::unary_op_as_string (op);
      std::string type_name = types(t);

      warning ("duplicate unary operator `%s' for type `%s'",
	       op_name.c_str (), type_name.c_str ());
    }

  unary_ops.checkelem (static_cast<int> (op), t) = f;

  return false;
}

bool
octave_value_typeinfo::do_register_non_const_unary_op
  (octave_value::unary_op op, int t, non_const_unary_op_fcn f)
{
  if (lookup_non_const_unary_op (op, t))
    {
      std::string op_name = octave_value::unary_op_as_string (op);
      std::string type_name = types(t);

      warning ("duplicate unary operator `%s' for type `%s'",
	       op_name.c_str (), type_name.c_str ());
    }

  non_const_unary_ops.checkelem (static_cast<int> (op), t) = f;

  return false;
}

bool
octave_value_typeinfo::do_register_binary_op (octave_value::binary_op op,
					      int t1, int t2,
					      binary_op_fcn f)
{
  if (lookup_binary_op (op, t1, t2))
    {
      std::string op_name = octave_value::binary_op_as_string (op);
      std::string t1_name = types(t1);
      std::string t2_name = types(t2);

      warning ("duplicate binary operator `%s' for types `%s' and `%s'",
	       op_name.c_str (), t1_name.c_str (), t1_name.c_str ());
    }

  binary_ops.checkelem (static_cast<int> (op), t1, t2) = f;

  return false;
}

bool
octave_value_typeinfo::do_register_assign_op (octave_value::assign_op op,
					      int t_lhs, int t_rhs,
					      assign_op_fcn f)
{
  if (lookup_assign_op (op, t_lhs, t_rhs))
    {
      std::string op_name = octave_value::assign_op_as_string (op);
      std::string t_lhs_name = types(t_lhs);
      std::string t_rhs_name = types(t_rhs);

      warning ("duplicate assignment operator `%s' for types `%s' and `%s'",
	       op_name.c_str (), t_lhs_name.c_str (), t_rhs_name.c_str ());
    }

  assign_ops.checkelem (static_cast<int> (op), t_lhs, t_rhs) = f;

  return false;
}

bool
octave_value_typeinfo::do_register_assignany_op (octave_value::assign_op op,
						 int t_lhs, assign_op_fcn f)
{
  if (lookup_assignany_op (op, t_lhs))
    {
      std::string op_name = octave_value::assign_op_as_string (op);
      std::string t_lhs_name = types(t_lhs);

      warning ("duplicate assignment operator `%s' for types `%s'",
	       op_name.c_str (), t_lhs_name.c_str ());
    }

  assignany_ops.checkelem (static_cast<int> (op), t_lhs) = f;

  return false;
}

bool
octave_value_typeinfo::do_register_pref_assign_conv (int t_lhs, int t_rhs,
						     int t_result) 
{
  if (lookup_pref_assign_conv (t_lhs, t_rhs) >= 0)
    {
      std::string t_lhs_name = types(t_lhs);
      std::string t_rhs_name = types(t_rhs);

      warning ("overriding assignment conversion for types `%s' and `%s'",
	       t_lhs_name.c_str (), t_rhs_name.c_str ());
    }

  pref_assign_conv.checkelem (t_lhs, t_rhs) = t_result;

  return false;
}

bool
octave_value_typeinfo::do_register_widening_op
  (int t, int t_result, type_conv_fcn f)
{
  if (lookup_widening_op (t, t_result))
    {
      std::string t_name = types(t);
      std::string t_result_name = types(t_result);

      warning ("overriding widening op for `%s' to `%s'",
	       t_name.c_str (), t_result_name.c_str ());
    }

  widening_ops.checkelem (t, t_result) = f;

  return false;
}

octave_value
octave_value_typeinfo::do_lookup_type (const std::string& nm)
{
  octave_value retval;

  for (int i = 0; i < num_types; i++)
    {
      if (nm == types(i))
	{
	  retval = vals(i);
	  retval.make_unique ();
	  break;
	}
    }

  return retval;
}

unary_op_fcn
octave_value_typeinfo::do_lookup_unary_op (octave_value::unary_op op, int t)
{
  return unary_ops.checkelem (static_cast<int> (op), t);
}

non_const_unary_op_fcn
octave_value_typeinfo::do_lookup_non_const_unary_op
  (octave_value::unary_op op, int t)
{
  return non_const_unary_ops.checkelem (static_cast<int> (op), t);
}

binary_op_fcn
octave_value_typeinfo::do_lookup_binary_op (octave_value::binary_op op,
					    int t1, int t2)
{
  return binary_ops.checkelem (static_cast<int> (op), t1, t2);
}

assign_op_fcn
octave_value_typeinfo::do_lookup_assign_op (octave_value::assign_op op,
					    int t_lhs, int t_rhs)
{
  return assign_ops.checkelem (static_cast<int> (op), t_lhs, t_rhs);
}

assign_op_fcn
octave_value_typeinfo::do_lookup_assignany_op (octave_value::assign_op op,
					       int t_lhs)
{
  return assignany_ops.checkelem (static_cast<int> (op), t_lhs);
}

int
octave_value_typeinfo::do_lookup_pref_assign_conv (int t_lhs, int t_rhs)
{
  return pref_assign_conv.checkelem (t_lhs, t_rhs);
}

type_conv_fcn
octave_value_typeinfo::do_lookup_widening_op (int t, int t_result)
{
  return widening_ops.checkelem (t, t_result);
}

string_vector
octave_value_typeinfo::do_installed_type_names (void)
{
  string_vector retval (num_types);

  for (int i = 0;i < num_types; i++)
    retval (i) = types (i);

  return retval;
}

DEFUN (typeinfo, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} typeinfo (@var{expr})\n\
\n\
Return the type of the expression @var{expr}, as a string.  If\n\
@var{EXPR}  is omitted, return an array of strings containing all the\n\
currently installed data types.\n\
@end deftypefn")
{
  octave_value retval;

  int nargin = args.length ();

  if (nargin == 0)
    retval = octave_value_typeinfo::installed_type_names ();
  else if (nargin == 1)
    retval = args(0).type_name ();
  else
    print_usage ("typeinfo");

  return retval;
}

DEFUN (class, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} class (@var{expr})\n\
\n\
Return the class of the expression @var{expr}, as a string.\n\
@end deftypefn")
{
  octave_value retval;

  int nargin = args.length ();

  if (nargin == 1)
    retval = args(0).class_name ();
  else
    print_usage ("class");

  return retval;
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/
