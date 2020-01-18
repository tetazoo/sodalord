// DO NOT EDIT!
// Generated automatically from ../liboctave/ODESSA-opts.in.

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iomanip>
#include <iostream>

#include "ODESSA-opts.h"

#include "defun-dld.h"
#include "pr-output.h"

#include "oct-obj.h"
#include "utils.h"
#include "pager.h"

static ODESSA_options odessa_opts;

#define MAX_TOKENS 3

struct ODESSA_options_struct
{
  const char *keyword;
  const char *kw_tok[MAX_TOKENS + 1];
  int min_len[MAX_TOKENS + 1];
  int min_toks_to_match;
};

#define NUM_OPTIONS 8

static ODESSA_options_struct ODESSA_options_table [] =
{
  { "absolute tolerance",
    { "absolute", "tolerance", 0, 0, },
    { 1, 0, 0, 0, }, 1, },

  { "relative tolerance",
    { "relative", "tolerance", 0, 0, },
    { 1, 0, 0, 0, }, 1, },

  { "integration method",
    { "integration", "method", 0, 0, },
    { 3, 0, 0, 0, }, 1, },

  { "initial step size",
    { "initial", "step", "size", 0, },
    { 3, 0, 0, 0, }, 1, },

  { "maximum order",
    { "maximum", "order", 0, 0, },
    { 2, 1, 0, 0, }, 2, },

  { "maximum step size",
    { "maximum", "step", "size", 0, },
    { 2, 1, 0, 0, }, 2, },

  { "minimum step size",
    { "minimum", "step", "size", 0, },
    { 2, 0, 0, 0, }, 1, },

  { "step limit",
    { "step", "limit", 0, 0, },
    { 1, 0, 0, 0, }, 1, },
};

static void
print_ODESSA_options (std::ostream& os)
{
  print_usage ("odessa_options", 1);

  os << "\n"
     << "Options for ODESSA include:\n\n"
     << "  keyword                                             value\n"
     << "  -------                                             -----\n";

  ODESSA_options_struct *list = ODESSA_options_table;

  {
    os << "  "
       << std::setiosflags (std::ios::left) << std::setw (50)
       << list[0].keyword
       << std::resetiosflags (std::ios::left)
       << "  ";

    Array<double> val = odessa_opts.absolute_tolerance ();

    if (val.length () == 1)
      {
        os << val(0) << "\n";
      }
    else
      {
        os << "\n\n";
        Matrix tmp = Matrix (ColumnVector (val));
        octave_print_internal (os, tmp, false, 2);
        os << "\n\n";
      }
  }

  {
    os << "  "
       << std::setiosflags (std::ios::left) << std::setw (50)
       << list[1].keyword
       << std::resetiosflags (std::ios::left)
       << "  ";

    double val = odessa_opts.relative_tolerance ();

    os << val << "\n";
  }

  {
    os << "  "
       << std::setiosflags (std::ios::left) << std::setw (50)
       << list[2].keyword
       << std::resetiosflags (std::ios::left)
       << "  ";

    os << odessa_opts.integration_method () << "\n";
  }

  {
    os << "  "
       << std::setiosflags (std::ios::left) << std::setw (50)
       << list[3].keyword
       << std::resetiosflags (std::ios::left)
       << "  ";

    double val = odessa_opts.initial_step_size ();

    os << val << "\n";
  }

  {
    os << "  "
       << std::setiosflags (std::ios::left) << std::setw (50)
       << list[4].keyword
       << std::resetiosflags (std::ios::left)
       << "  ";

    int val = odessa_opts.maximum_order ();

    os << val << "\n";
  }

  {
    os << "  "
       << std::setiosflags (std::ios::left) << std::setw (50)
       << list[5].keyword
       << std::resetiosflags (std::ios::left)
       << "  ";

    double val = odessa_opts.maximum_step_size ();

    os << val << "\n";
  }

  {
    os << "  "
       << std::setiosflags (std::ios::left) << std::setw (50)
       << list[6].keyword
       << std::resetiosflags (std::ios::left)
       << "  ";

    double val = odessa_opts.minimum_step_size ();

    os << val << "\n";
  }

  {
    os << "  "
       << std::setiosflags (std::ios::left) << std::setw (50)
       << list[7].keyword
       << std::resetiosflags (std::ios::left)
       << "  ";

    int val = odessa_opts.step_limit ();

    os << val << "\n";
  }

  os << "\n";
}

static void
set_ODESSA_options (const std::string& keyword, const octave_value& val)
{
  ODESSA_options_struct *list = ODESSA_options_table;

  if (keyword_almost_match (list[0].kw_tok, list[0].min_len,
           keyword, list[0].min_toks_to_match, MAX_TOKENS))
    {
      Array<double> tmp = val.vector_value ();

      if (! error_state)
        odessa_opts.set_absolute_tolerance (tmp);
    }
  else if (keyword_almost_match (list[1].kw_tok, list[1].min_len,
           keyword, list[1].min_toks_to_match, MAX_TOKENS))
    {
      double tmp = val.double_value ();

      if (! error_state)
        odessa_opts.set_relative_tolerance (tmp);
    }
  else if (keyword_almost_match (list[2].kw_tok, list[2].min_len,
           keyword, list[2].min_toks_to_match, MAX_TOKENS))
    {
      std::string tmp = val.string_value ();

      if (! error_state)
        odessa_opts.set_integration_method (tmp);
    }
  else if (keyword_almost_match (list[3].kw_tok, list[3].min_len,
           keyword, list[3].min_toks_to_match, MAX_TOKENS))
    {
      double tmp = val.double_value ();

      if (! error_state)
        odessa_opts.set_initial_step_size (tmp);
    }
  else if (keyword_almost_match (list[4].kw_tok, list[4].min_len,
           keyword, list[4].min_toks_to_match, MAX_TOKENS))
    {
      int tmp = val.int_value ();

      if (! error_state)
        odessa_opts.set_maximum_order (tmp);
    }
  else if (keyword_almost_match (list[5].kw_tok, list[5].min_len,
           keyword, list[5].min_toks_to_match, MAX_TOKENS))
    {
      double tmp = val.double_value ();

      if (! error_state)
        odessa_opts.set_maximum_step_size (tmp);
    }
  else if (keyword_almost_match (list[6].kw_tok, list[6].min_len,
           keyword, list[6].min_toks_to_match, MAX_TOKENS))
    {
      double tmp = val.double_value ();

      if (! error_state)
        odessa_opts.set_minimum_step_size (tmp);
    }
  else if (keyword_almost_match (list[7].kw_tok, list[7].min_len,
           keyword, list[7].min_toks_to_match, MAX_TOKENS))
    {
      int tmp = val.int_value ();

      if (! error_state)
        odessa_opts.set_step_limit (tmp);
    }
  else
    {
      warning ("odessa_options: no match for `%s'", keyword.c_str ());
    }
}

static octave_value_list
show_ODESSA_options (const std::string& keyword)
{
  octave_value retval;

  ODESSA_options_struct *list = ODESSA_options_table;

  if (keyword_almost_match (list[0].kw_tok, list[0].min_len,
           keyword, list[0].min_toks_to_match, MAX_TOKENS))
    {
      Array<double> val = odessa_opts.absolute_tolerance ();

      if (val.length () == 1)
        {
          retval = val(0);
        }
      else
        {
          retval = ColumnVector (val);
        }
    }
  else if (keyword_almost_match (list[1].kw_tok, list[1].min_len,
           keyword, list[1].min_toks_to_match, MAX_TOKENS))
    {
      double val = odessa_opts.relative_tolerance ();

      retval = val;
    }
  else if (keyword_almost_match (list[2].kw_tok, list[2].min_len,
           keyword, list[2].min_toks_to_match, MAX_TOKENS))
    {
      retval = odessa_opts.integration_method ();
    }
  else if (keyword_almost_match (list[3].kw_tok, list[3].min_len,
           keyword, list[3].min_toks_to_match, MAX_TOKENS))
    {
      double val = odessa_opts.initial_step_size ();

      retval = val;
    }
  else if (keyword_almost_match (list[4].kw_tok, list[4].min_len,
           keyword, list[4].min_toks_to_match, MAX_TOKENS))
    {
      int val = odessa_opts.maximum_order ();

      retval = static_cast<double> (val);
    }
  else if (keyword_almost_match (list[5].kw_tok, list[5].min_len,
           keyword, list[5].min_toks_to_match, MAX_TOKENS))
    {
      double val = odessa_opts.maximum_step_size ();

      retval = val;
    }
  else if (keyword_almost_match (list[6].kw_tok, list[6].min_len,
           keyword, list[6].min_toks_to_match, MAX_TOKENS))
    {
      double val = odessa_opts.minimum_step_size ();

      retval = val;
    }
  else if (keyword_almost_match (list[7].kw_tok, list[7].min_len,
           keyword, list[7].min_toks_to_match, MAX_TOKENS))
    {
      int val = odessa_opts.step_limit ();

      retval = static_cast<double> (val);
    }
  else
    {
      warning ("odessa_options: no match for `%s'", keyword.c_str ());
    }

  return retval;
}

DEFUN_DLD (odessa_options, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} odessa_options (@var{opt}, @var{val})\n\
When called with two arguments, this function\n\
allows you set options parameters for the function @code{odessa}.\n\
Given one argument, @code{odessa_options} returns the value of the\n\
corresponding option.  If no arguments are supplied, the names of all\n\
the available options and their current values are displayed.\n\
\n\
Options include\n\
\n\
@table @code\n\
@item \"absolute tolerance\"\n\
Absolute tolerance.  May be either vector or scalar.  If a vector, it\n\
must match the dimension of the state vector.\n\
@item \"relative tolerance\"\n\
Relative tolerance parameter.  Unlike the absolute tolerance, this\n\
parameter may only be a scalar.\n\
\n\
The local error test applied at each integration step is\n\
\n\
@example\n\
  abs (local error in x(i)) <= rtol * abs (y(i)) + atol(i)\n\
@end example\n\
@item \"integration method\"\n\
A string specifing the method of integration to use to solve the ODE\n\
system.  Valid values are\n\
\n\
@table @asis\n\
@item \"adams\"\n\
@itemx \"non-stiff\"\n\
No Jacobian used (even if it is available).\n\
@item \"bdf\"\n\
@item \"stiff\"\n\
Use stiff backward differentiation formula (BDF) method.  If a\n\
function to compute the Jacobian is not supplied, @code{lsode} will\n\
compute a finite difference approximation of the Jacobian matrix.\n\
@end table\n\
@item \"initial step size\"\n\
The step size to be attempted on the first step (default is determined\n\
automatically).\n\
@item \"maximum order\"\n\
Restrict the maximum order of the solution method.  If using the Adams\n\
method, this option must be between 1 and 12.  Otherwise, it must be\n\
between 1 and 5, inclusive.\n\
@item \"maximum step size\"\n\
Setting the maximum stepsize will avoid passing over very large\n\
regions  (default is not specified).\n\
@item \"minimum step size\"\n\
The minimum absolute step size allowed (default is 0).\n\
@item \"step limit\"\n\
Maximum number of steps allowed (default is 100000).\n\
@end table\n\
@end deftypefn")
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin == 0)
    {
      print_ODESSA_options (octave_stdout);
    }
  else if (nargin == 1 || nargin == 2)
    {
      std::string keyword = args(0).string_value ();

      if (! error_state)
        {
          if (nargin == 1)
            retval = show_ODESSA_options (keyword);
          else
            set_ODESSA_options (keyword, args(1));
        }
      else
        error ("odessa_options: expecting keyword as first argument");
    }
  else
    print_usage ("odessa_options");

  return retval;
}
