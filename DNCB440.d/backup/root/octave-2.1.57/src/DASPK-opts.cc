// DO NOT EDIT!
// Generated automatically from ../liboctave/DASPK-opts.in.

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iomanip>
#include <iostream>

#include "DASPK-opts.h"

#include "defun-dld.h"
#include "pr-output.h"

#include "oct-obj.h"
#include "utils.h"
#include "pager.h"

static DASPK_options daspk_opts;

#define MAX_TOKENS 6

struct DASPK_options_struct
{
  const char *keyword;
  const char *kw_tok[MAX_TOKENS + 1];
  int min_len[MAX_TOKENS + 1];
  int min_toks_to_match;
};

#define NUM_OPTIONS 13

static DASPK_options_struct DASPK_options_table [] =
{
  { "absolute tolerance",
    { "absolute", "tolerance", 0, 0, 0, 0, 0, },
    { 2, 0, 0, 0, 0, 0, 0, }, 1, },

  { "relative tolerance",
    { "relative", "tolerance", 0, 0, 0, 0, 0, },
    { 1, 0, 0, 0, 0, 0, 0, }, 1, },

  { "compute consistent initial condition",
    { "compute", "consistent", "initial", "condition", 0, 0, 0, },
    { 1, 0, 0, 0, 0, 0, 0, }, 1, },

  { "use initial condition heuristics",
    { "use", "initial", "condition", "heuristics", 0, 0, 0, },
    { 1, 0, 0, 0, 0, 0, 0, }, 1, },

  { "initial condition heuristics",
    { "initial", "condition", "heuristics", 0, 0, 0, 0, },
    { 3, 1, 0, 0, 0, 0, 0, }, 2, },

  { "print initial condition info",
    { "print", "initial", "condition", "info", 0, 0, 0, },
    { 1, 0, 0, 0, 0, 0, 0, }, 1, },

  { "exclude algebraic variables from error test",
    { "exclude", "algebraic", "variables", "from", "error", "test", 0, },
    { 2, 0, 0, 0, 0, 0, 0, }, 1, },

  { "algebraic variables",
    { "algebraic", "variables", 0, 0, 0, 0, 0, },
    { 2, 0, 0, 0, 0, 0, 0, }, 1, },

  { "enforce inequality constraints",
    { "enforce", "inequality", "constraints", 0, 0, 0, 0, },
    { 2, 0, 0, 0, 0, 0, 0, }, 1, },

  { "inequality constraint types",
    { "inequality", "constraint", "types", 0, 0, 0, 0, },
    { 3, 0, 0, 0, 0, 0, 0, }, 1, },

  { "initial step size",
    { "initial", "step", "size", 0, 0, 0, 0, },
    { 3, 1, 0, 0, 0, 0, 0, }, 2, },

  { "maximum order",
    { "maximum", "order", 0, 0, 0, 0, 0, },
    { 1, 1, 0, 0, 0, 0, 0, }, 2, },

  { "maximum step size",
    { "maximum", "step", "size", 0, 0, 0, 0, },
    { 1, 1, 0, 0, 0, 0, 0, }, 2, },
};

static void
print_DASPK_options (std::ostream& os)
{
  print_usage ("daspk_options", 1);

  os << "\n"
     << "Options for DASPK include:\n\n"
     << "  keyword                                             value\n"
     << "  -------                                             -----\n";

  DASPK_options_struct *list = DASPK_options_table;

  {
    os << "  "
       << std::setiosflags (std::ios::left) << std::setw (50)
       << list[0].keyword
       << std::resetiosflags (std::ios::left)
       << "  ";

    Array<double> val = daspk_opts.absolute_tolerance ();

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

    Array<double> val = daspk_opts.relative_tolerance ();

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

    int val = daspk_opts.compute_consistent_initial_condition ();

    os << val << "\n";
  }

  {
    os << "  "
       << std::setiosflags (std::ios::left) << std::setw (50)
       << list[3].keyword
       << std::resetiosflags (std::ios::left)
       << "  ";

    int val = daspk_opts.use_initial_condition_heuristics ();

    os << val << "\n";
  }

  {
    os << "  "
       << std::setiosflags (std::ios::left) << std::setw (50)
       << list[4].keyword
       << std::resetiosflags (std::ios::left)
       << "  ";

    Array<double> val = daspk_opts.initial_condition_heuristics ();

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
       << list[5].keyword
       << std::resetiosflags (std::ios::left)
       << "  ";

    int val = daspk_opts.print_initial_condition_info ();

    os << val << "\n";
  }

  {
    os << "  "
       << std::setiosflags (std::ios::left) << std::setw (50)
       << list[6].keyword
       << std::resetiosflags (std::ios::left)
       << "  ";

    int val = daspk_opts.exclude_algebraic_variables_from_error_test ();

    os << val << "\n";
  }

  {
    os << "  "
       << std::setiosflags (std::ios::left) << std::setw (50)
       << list[7].keyword
       << std::resetiosflags (std::ios::left)
       << "  ";

    Array<int> val = daspk_opts.algebraic_variables ();

    if (val.length () == 1)
      {
        os << val(0) << "\n";
      }
    else
      {
        os << "\n\n";
	int len = val.length ();
	Matrix tmp (len, 1);
	for (int i = 0; i < len; i++)
	  tmp(i,0) = val(i);
        octave_print_internal (os, tmp, false, 2);
        os << "\n\n";
      }
  }

  {
    os << "  "
       << std::setiosflags (std::ios::left) << std::setw (50)
       << list[8].keyword
       << std::resetiosflags (std::ios::left)
       << "  ";

    int val = daspk_opts.enforce_inequality_constraints ();

    os << val << "\n";
  }

  {
    os << "  "
       << std::setiosflags (std::ios::left) << std::setw (50)
       << list[9].keyword
       << std::resetiosflags (std::ios::left)
       << "  ";

    Array<int> val = daspk_opts.inequality_constraint_types ();

    if (val.length () == 1)
      {
        os << val(0) << "\n";
      }
    else
      {
        os << "\n\n";
	int len = val.length ();
	Matrix tmp (len, 1);
	for (int i = 0; i < len; i++)
	  tmp(i,0) = val(i);
        octave_print_internal (os, tmp, false, 2);
        os << "\n\n";
      }
  }

  {
    os << "  "
       << std::setiosflags (std::ios::left) << std::setw (50)
       << list[10].keyword
       << std::resetiosflags (std::ios::left)
       << "  ";

    double val = daspk_opts.initial_step_size ();

    os << val << "\n";
  }

  {
    os << "  "
       << std::setiosflags (std::ios::left) << std::setw (50)
       << list[11].keyword
       << std::resetiosflags (std::ios::left)
       << "  ";

    int val = daspk_opts.maximum_order ();

    os << val << "\n";
  }

  {
    os << "  "
       << std::setiosflags (std::ios::left) << std::setw (50)
       << list[12].keyword
       << std::resetiosflags (std::ios::left)
       << "  ";

    double val = daspk_opts.maximum_step_size ();

    os << val << "\n";
  }

  os << "\n";
}

static void
set_DASPK_options (const std::string& keyword, const octave_value& val)
{
  DASPK_options_struct *list = DASPK_options_table;

  if (keyword_almost_match (list[0].kw_tok, list[0].min_len,
           keyword, list[0].min_toks_to_match, MAX_TOKENS))
    {
      Array<double> tmp = val.vector_value ();

      if (! error_state)
        daspk_opts.set_absolute_tolerance (tmp);
    }
  else if (keyword_almost_match (list[1].kw_tok, list[1].min_len,
           keyword, list[1].min_toks_to_match, MAX_TOKENS))
    {
      Array<double> tmp = val.vector_value ();

      if (! error_state)
        daspk_opts.set_relative_tolerance (tmp);
    }
  else if (keyword_almost_match (list[2].kw_tok, list[2].min_len,
           keyword, list[2].min_toks_to_match, MAX_TOKENS))
    {
      int tmp = val.int_value ();

      if (! error_state)
        daspk_opts.set_compute_consistent_initial_condition (tmp);
    }
  else if (keyword_almost_match (list[3].kw_tok, list[3].min_len,
           keyword, list[3].min_toks_to_match, MAX_TOKENS))
    {
      int tmp = val.int_value ();

      if (! error_state)
        daspk_opts.set_use_initial_condition_heuristics (tmp);
    }
  else if (keyword_almost_match (list[4].kw_tok, list[4].min_len,
           keyword, list[4].min_toks_to_match, MAX_TOKENS))
    {
      Array<double> tmp = val.vector_value ();

      if (! error_state)
        daspk_opts.set_initial_condition_heuristics (tmp);
    }
  else if (keyword_almost_match (list[5].kw_tok, list[5].min_len,
           keyword, list[5].min_toks_to_match, MAX_TOKENS))
    {
      int tmp = val.int_value ();

      if (! error_state)
        daspk_opts.set_print_initial_condition_info (tmp);
    }
  else if (keyword_almost_match (list[6].kw_tok, list[6].min_len,
           keyword, list[6].min_toks_to_match, MAX_TOKENS))
    {
      int tmp = val.int_value ();

      if (! error_state)
        daspk_opts.set_exclude_algebraic_variables_from_error_test (tmp);
    }
  else if (keyword_almost_match (list[7].kw_tok, list[7].min_len,
           keyword, list[7].min_toks_to_match, MAX_TOKENS))
    {
      Array<int> tmp = val.int_vector_value ();

      if (! error_state)
        daspk_opts.set_algebraic_variables (tmp);
    }
  else if (keyword_almost_match (list[8].kw_tok, list[8].min_len,
           keyword, list[8].min_toks_to_match, MAX_TOKENS))
    {
      int tmp = val.int_value ();

      if (! error_state)
        daspk_opts.set_enforce_inequality_constraints (tmp);
    }
  else if (keyword_almost_match (list[9].kw_tok, list[9].min_len,
           keyword, list[9].min_toks_to_match, MAX_TOKENS))
    {
      Array<int> tmp = val.int_vector_value ();

      if (! error_state)
        daspk_opts.set_inequality_constraint_types (tmp);
    }
  else if (keyword_almost_match (list[10].kw_tok, list[10].min_len,
           keyword, list[10].min_toks_to_match, MAX_TOKENS))
    {
      double tmp = val.double_value ();

      if (! error_state)
        daspk_opts.set_initial_step_size (tmp);
    }
  else if (keyword_almost_match (list[11].kw_tok, list[11].min_len,
           keyword, list[11].min_toks_to_match, MAX_TOKENS))
    {
      int tmp = val.int_value ();

      if (! error_state)
        daspk_opts.set_maximum_order (tmp);
    }
  else if (keyword_almost_match (list[12].kw_tok, list[12].min_len,
           keyword, list[12].min_toks_to_match, MAX_TOKENS))
    {
      double tmp = val.double_value ();

      if (! error_state)
        daspk_opts.set_maximum_step_size (tmp);
    }
  else
    {
      warning ("daspk_options: no match for `%s'", keyword.c_str ());
    }
}

static octave_value_list
show_DASPK_options (const std::string& keyword)
{
  octave_value retval;

  DASPK_options_struct *list = DASPK_options_table;

  if (keyword_almost_match (list[0].kw_tok, list[0].min_len,
           keyword, list[0].min_toks_to_match, MAX_TOKENS))
    {
      Array<double> val = daspk_opts.absolute_tolerance ();

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
      Array<double> val = daspk_opts.relative_tolerance ();

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
      int val = daspk_opts.compute_consistent_initial_condition ();

      retval = static_cast<double> (val);
    }
  else if (keyword_almost_match (list[3].kw_tok, list[3].min_len,
           keyword, list[3].min_toks_to_match, MAX_TOKENS))
    {
      int val = daspk_opts.use_initial_condition_heuristics ();

      retval = static_cast<double> (val);
    }
  else if (keyword_almost_match (list[4].kw_tok, list[4].min_len,
           keyword, list[4].min_toks_to_match, MAX_TOKENS))
    {
      Array<double> val = daspk_opts.initial_condition_heuristics ();

      if (val.length () == 1)
        {
          retval = val(0);
        }
      else
        {
          retval = ColumnVector (val);
        }
    }
  else if (keyword_almost_match (list[5].kw_tok, list[5].min_len,
           keyword, list[5].min_toks_to_match, MAX_TOKENS))
    {
      int val = daspk_opts.print_initial_condition_info ();

      retval = static_cast<double> (val);
    }
  else if (keyword_almost_match (list[6].kw_tok, list[6].min_len,
           keyword, list[6].min_toks_to_match, MAX_TOKENS))
    {
      int val = daspk_opts.exclude_algebraic_variables_from_error_test ();

      retval = static_cast<double> (val);
    }
  else if (keyword_almost_match (list[7].kw_tok, list[7].min_len,
           keyword, list[7].min_toks_to_match, MAX_TOKENS))
    {
      Array<int> val = daspk_opts.algebraic_variables ();

      if (val.length () == 1)
        {
          retval = static_cast<double> (val(0));
        }
      else
        {
	  int len = val.length ();
	  ColumnVector tmp (len);
	  for (int i = 0; i < len; i++)
	    tmp(i) = val(i);
          retval = tmp;
        }
    }
  else if (keyword_almost_match (list[8].kw_tok, list[8].min_len,
           keyword, list[8].min_toks_to_match, MAX_TOKENS))
    {
      int val = daspk_opts.enforce_inequality_constraints ();

      retval = static_cast<double> (val);
    }
  else if (keyword_almost_match (list[9].kw_tok, list[9].min_len,
           keyword, list[9].min_toks_to_match, MAX_TOKENS))
    {
      Array<int> val = daspk_opts.inequality_constraint_types ();

      if (val.length () == 1)
        {
          retval = static_cast<double> (val(0));
        }
      else
        {
	  int len = val.length ();
	  ColumnVector tmp (len);
	  for (int i = 0; i < len; i++)
	    tmp(i) = val(i);
          retval = tmp;
        }
    }
  else if (keyword_almost_match (list[10].kw_tok, list[10].min_len,
           keyword, list[10].min_toks_to_match, MAX_TOKENS))
    {
      double val = daspk_opts.initial_step_size ();

      retval = val;
    }
  else if (keyword_almost_match (list[11].kw_tok, list[11].min_len,
           keyword, list[11].min_toks_to_match, MAX_TOKENS))
    {
      int val = daspk_opts.maximum_order ();

      retval = static_cast<double> (val);
    }
  else if (keyword_almost_match (list[12].kw_tok, list[12].min_len,
           keyword, list[12].min_toks_to_match, MAX_TOKENS))
    {
      double val = daspk_opts.maximum_step_size ();

      retval = val;
    }
  else
    {
      warning ("daspk_options: no match for `%s'", keyword.c_str ());
    }

  return retval;
}

DEFUN_DLD (daspk_options, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} daspk_options (@var{opt}, @var{val})\n\
When called with two arguments, this function\n\
allows you set options parameters for the function @code{daspk}.\n\
Given one argument, @code{daspk_options} returns the value of the\n\
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
\n\
@example\n\
  abs (local error in x(i)) <= rtol(i) * abs (Y(i)) + atol(i)\n\
@end example\n\
@item \"compute consistent initial condition\"\n\
Denoting the differential variables in the state vector by @samp{Y_d}\n\
and the algebraic variables by @samp{Y_a}, @code{ddaspk} can solve\n\
one of two initialization problems:\n\
\n\
@enumerate\n\
@item Given Y_d, calculate Y_a and Y'_d\n\
@item Given Y', calculate Y.\n\
@end enumerate\n\
\n\
In either case, initial values for the given components are input, and\n\
initial guesses for the unknown components must also be provided as\n\
input.  Set this option to 1 to solve the first problem, or 2 to solve\n\
the second (the default default is 0, so you must provide a set of\n\
initial conditions that are consistent).\n\
\n\
If this option is set to a nonzero value, you must also set the\n\
@code{\"algebraic variables\"} option to declare which variables in the\n\
problem are algebraic.\n\
@item \"use initial condition heuristics\"\n\
Set to a nonzero value to use the initial condition heuristics options\n\
described below.\n\
@item \"initial condition heuristics\"\n\
A vector of the following parameters that can be used to control the\n\
initial condition calculation.\n\
\n\
@table @code\n\
@item MXNIT\n\
Maximum number of Newton iterations (default is 5).\n\
@item MXNJ\n\
Maximum number of Jacobian evaluations (default is 6).\n\
@item MXNH\n\
Maximum number of values of the artificial stepsize parameter to be\n\
tried if the @code{\"compute consistent initial condition\"} option has\n\
been set to 1 (default is 5).\n\
\n\
Note that the maximum number of Newton iterations allowed in all is\n\
@code{MXNIT*MXNJ*MXNH} if the @code{\"compute consistent initial\n\
condition\"} option has been set to 1 and @code{MXNIT*MXNJ} if it is\n\
set to 2.\n\
@item LSOFF\n\
Set to a nonzero value to disable the linesearch algorithm (default is\n\
0).\n\
@item STPTOL\n\
Minimum scaled step in linesearch algorithm (default is eps^(2/3)).\n\
@item EPINIT\n\
Swing factor in the Newton iteration convergence test.  The test is\n\
applied to the residual vector, premultiplied by the approximate\n\
Jacobian.  For convergence, the weighted RMS norm of this vector\n\
(scaled by the error weights) must be less than @code{EPINIT*EPCON},\n\
where @code{EPCON} = 0.33 is the analogous test constant used in the\n\
time steps. The default is @code{EPINIT} = 0.01.\n\
@end table\n\
@item \"print initial condition info\"\n\
Set this option to a nonzero value to display detailed information\n\
about the initial condition calculation (default is 0).\n\
@item \"exclude algebraic variables from error test\"\n\
Set to a nonzero value to exclude algebraic variables from the error\n\
test.  You must also set the @code{\"algebraic variables\"} option to\n\
declare which variables in the problem are algebraic (default is 0).\n\
@item \"algebraic variables\"\n\
A vector of the same length as the state vector.  A nonzero element\n\
indicates that the corresponding element of the state vector is an\n\
algebraic variable (i.e., its derivative does not appear explicitly\n\
in the equation set.\n\
\n\
This option is required by the\n\
@code{compute consistent initial condition\"} and\n\
@code{\"exclude algebraic variables from error test\"} options.\n\
@item \"enforce inequality constraints\"\n\
Set to one of the following values to enforce the inequality\n\
constraints specified by the @code{\"inequality constraint types\"}\n\
option (default is 0).\n\
\n\
@enumerate\n\
@item To have constraint checking only in the initial condition calculation.\n\
@item To enforce constraint checking during the integration.\n\
@item To enforce both options 1 and 2.\n\
@end enumerate\n\
@item \"inequality constraint types\"\n\
A vector of the same length as the state specifying the type of\n\
inequality constraint.  Each element of the vector corresponds to an\n\
element of the state and should be assigned one of the following\n\
codes \n\
\n\
@table @asis\n\
@item -2\n\
Less than zero.\n\
@item -1\n\
Less than or equal to zero.\n\
@item 0\n\
Not constrained.\n\
@item 1\n\
Greater than or equal to zero.\n\
@item 2\n\
Greater than zero.\n\
@end table\n\
\n\
This option only has an effect if the\n\
@code{\"enforce inequality constraints\"} option is nonzero.\n\
@item \"initial step size\"\n\
Differential-algebraic problems may occaisionally suffer from severe\n\
scaling difficulties on the first step.  If you know a great deal\n\
about the scaling of your problem, you can help to alleviate this\n\
problem by specifying an initial stepsize (default is computed\n\
automatically).\n\
@item \"maximum order\"\n\
Restrict the maximum order of the solution method.  This option must\n\
be between 1 and 5, inclusive (default is 5).\n\
@item \"maximum step size\"\n\
Setting the maximum stepsize will avoid passing over very large\n\
regions (default is not specified).\n\
@end table\n\
@end deftypefn")
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin == 0)
    {
      print_DASPK_options (octave_stdout);
    }
  else if (nargin == 1 || nargin == 2)
    {
      std::string keyword = args(0).string_value ();

      if (! error_state)
        {
          if (nargin == 1)
            retval = show_DASPK_options (keyword);
          else
            set_DASPK_options (keyword, args(1));
        }
      else
        error ("daspk_options: expecting keyword as first argument");
    }
  else
    print_usage ("daspk_options");

  return retval;
}
