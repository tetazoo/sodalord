// DO NOT EDIT!
// Generated automatically from ../liboctave/DASRT-opts.in.

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iomanip>
#include <iostream>

#include "DASRT-opts.h"

#include "defun-dld.h"
#include "pr-output.h"

#include "oct-obj.h"
#include "utils.h"
#include "pager.h"

static DASRT_options dasrt_opts;

#define MAX_TOKENS 3

struct DASRT_options_struct
{
  const char *keyword;
  const char *kw_tok[MAX_TOKENS + 1];
  int min_len[MAX_TOKENS + 1];
  int min_toks_to_match;
};

#define NUM_OPTIONS 6

static DASRT_options_struct DASRT_options_table [] =
{
  { "absolute tolerance",
    { "absolute", "tolerance", 0, 0, },
    { 1, 0, 0, 0, }, 1, },

  { "relative tolerance",
    { "relative", "tolerance", 0, 0, },
    { 1, 0, 0, 0, }, 1, },

  { "initial step size",
    { "initial", "step", "size", 0, },
    { 1, 0, 0, 0, }, 1, },

  { "maximum order",
    { "maximum", "order", 0, 0, },
    { 1, 1, 0, 0, }, 2, },

  { "maximum step size",
    { "maximum", "step", "size", 0, },
    { 1, 1, 0, 0, }, 2, },

  { "step limit",
    { "step", "limit", 0, 0, },
    { 1, 0, 0, 0, }, 1, },
};

static void
print_DASRT_options (std::ostream& os)
{
  print_usage ("dasrt_options", 1);

  os << "\n"
     << "Options for DASRT include:\n\n"
     << "  keyword                                             value\n"
     << "  -------                                             -----\n";

  DASRT_options_struct *list = DASRT_options_table;

  {
    os << "  "
       << std::setiosflags (std::ios::left) << std::setw (50)
       << list[0].keyword
       << std::resetiosflags (std::ios::left)
       << "  ";

    Array<double> val = dasrt_opts.absolute_tolerance ();

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

    Array<double> val = dasrt_opts.relative_tolerance ();

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
       << list[2].keyword
       << std::resetiosflags (std::ios::left)
       << "  ";

    double val = dasrt_opts.initial_step_size ();

    os << val << "\n";
  }

  {
    os << "  "
       << std::setiosflags (std::ios::left) << std::setw (50)
       << list[3].keyword
       << std::resetiosflags (std::ios::left)
       << "  ";

    int val = dasrt_opts.maximum_order ();

    os << val << "\n";
  }

  {
    os << "  "
       << std::setiosflags (std::ios::left) << std::setw (50)
       << list[4].keyword
       << std::resetiosflags (std::ios::left)
       << "  ";

    double val = dasrt_opts.maximum_step_size ();

    os << val << "\n";
  }

  {
    os << "  "
       << std::setiosflags (std::ios::left) << std::setw (50)
       << list[5].keyword
       << std::resetiosflags (std::ios::left)
       << "  ";

    int val = dasrt_opts.step_limit ();

    os << val << "\n";
  }

  os << "\n";
}

static void
set_DASRT_options (const std::string& keyword, const octave_value& val)
{
  DASRT_options_struct *list = DASRT_options_table;

  if (keyword_almost_match (list[0].kw_tok, list[0].min_len,
           keyword, list[0].min_toks_to_match, MAX_TOKENS))
    {
      Array<double> tmp = val.vector_value ();

      if (! error_state)
        dasrt_opts.set_absolute_tolerance (tmp);
    }
  else if (keyword_almost_match (list[1].kw_tok, list[1].min_len,
           keyword, list[1].min_toks_to_match, MAX_TOKENS))
    {
      Array<double> tmp = val.vector_value ();

      if (! error_state)
        dasrt_opts.set_relative_tolerance (tmp);
    }
  else if (keyword_almost_match (list[2].kw_tok, list[2].min_len,
           keyword, list[2].min_toks_to_match, MAX_TOKENS))
    {
      double tmp = val.double_value ();

      if (! error_state)
        dasrt_opts.set_initial_step_size (tmp);
    }
  else if (keyword_almost_match (list[3].kw_tok, list[3].min_len,
           keyword, list[3].min_toks_to_match, MAX_TOKENS))
    {
      int tmp = val.int_value ();

      if (! error_state)
        dasrt_opts.set_maximum_order (tmp);
    }
  else if (keyword_almost_match (list[4].kw_tok, list[4].min_len,
           keyword, list[4].min_toks_to_match, MAX_TOKENS))
    {
      double tmp = val.double_value ();

      if (! error_state)
        dasrt_opts.set_maximum_step_size (tmp);
    }
  else if (keyword_almost_match (list[5].kw_tok, list[5].min_len,
           keyword, list[5].min_toks_to_match, MAX_TOKENS))
    {
      int tmp = val.int_value ();

      if (! error_state)
        dasrt_opts.set_step_limit (tmp);
    }
  else
    {
      warning ("dasrt_options: no match for `%s'", keyword.c_str ());
    }
}

static octave_value_list
show_DASRT_options (const std::string& keyword)
{
  octave_value retval;

  DASRT_options_struct *list = DASRT_options_table;

  if (keyword_almost_match (list[0].kw_tok, list[0].min_len,
           keyword, list[0].min_toks_to_match, MAX_TOKENS))
    {
      Array<double> val = dasrt_opts.absolute_tolerance ();

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
      Array<double> val = dasrt_opts.relative_tolerance ();

      if (val.length () == 1)
        {
          retval = val(0);
        }
      else
        {
          retval = ColumnVector (val);
        }
    }
  else if (keyword_almost_match (list[2].kw_tok, list[2].min_len,
           keyword, list[2].min_toks_to_match, MAX_TOKENS))
    {
      double val = dasrt_opts.initial_step_size ();

      retval = val;
    }
  else if (keyword_almost_match (list[3].kw_tok, list[3].min_len,
           keyword, list[3].min_toks_to_match, MAX_TOKENS))
    {
      int val = dasrt_opts.maximum_order ();

      retval = static_cast<double> (val);
    }
  else if (keyword_almost_match (list[4].kw_tok, list[4].min_len,
           keyword, list[4].min_toks_to_match, MAX_TOKENS))
    {
      double val = dasrt_opts.maximum_step_size ();

      retval = val;
    }
  else if (keyword_almost_match (list[5].kw_tok, list[5].min_len,
           keyword, list[5].min_toks_to_match, MAX_TOKENS))
    {
      int val = dasrt_opts.step_limit ();

      retval = static_cast<double> (val);
    }
  else
    {
      warning ("dasrt_options: no match for `%s'", keyword.c_str ());
    }

  return retval;
}

DEFUN_DLD (dasrt_options, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} dasrt_options (@var{opt}, @var{val})\n\
When called with two arguments, this function\n\
allows you set options parameters for the function @code{dasrt}.\n\
Given one argument, @code{dasrt_options} returns the value of the\n\
corresponding option.  If no arguments are supplied, the names of all\n\
the available options and their current values are displayed.\n\
\n\
Options include\n\
\n\
@table @code\n\
@item \"absolute tolerance\"\n\
Absolute tolerance.  May be either vector or scalar.  If a vector, it\n\
must match the dimension of the state vector, and the relative\n\
tolerance must also be a vector of the same length.\n\
@item \"relative tolerance\"\n\
Relative tolerance.  May be either vector or scalar.  If a vector, it\n\
must match the dimension of the state vector, and the absolute\n\
tolerance must also be a vector of the same length.\n\
\n\
The local error test applied at each integration step is\n\
@example\n\
  abs (local error in x(i)) <= rtol(i) * abs (Y(i)) + atol(i)\n\
@end example\n\
@item \"initial step size\"\n\
Differential-algebraic problems may occaisionally suffer from severe\n\
scaling difficulties on the first step.  If you know a great deal\n\
about the scaling of your problem, you can help to alleviate this\n\
problem by specifying an initial stepsize.\n\
@item \"maximum order\"\n\
Restrict the maximum order of the solution method.  This option must\n\
be between 1 and 5, inclusive.\n\
@item \"maximum step size\"\n\
Setting the maximum stepsize will avoid passing over very large\n\
regions.\n\
@item \"step limit\"\n\
Maximum number of integration steps to attempt on a single call to the\n\
underlying Fortran code.\n\
@end table\n\
@end deftypefn")
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin == 0)
    {
      print_DASRT_options (octave_stdout);
    }
  else if (nargin == 1 || nargin == 2)
    {
      std::string keyword = args(0).string_value ();

      if (! error_state)
        {
          if (nargin == 1)
            retval = show_DASRT_options (keyword);
          else
            set_DASRT_options (keyword, args(1));
        }
      else
        error ("dasrt_options: expecting keyword as first argument");
    }
  else
    print_usage ("dasrt_options");

  return retval;
}
