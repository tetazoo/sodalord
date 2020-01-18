// DO NOT EDIT!
// Generated automatically from ../liboctave/NLEqn-opts.in.

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iomanip>
#include <iostream>

#include "NLEqn-opts.h"

#include "defun-dld.h"
#include "pr-output.h"

#include "oct-obj.h"
#include "utils.h"
#include "pager.h"

static NLEqn_options fsolve_opts;

#define MAX_TOKENS 1

struct NLEqn_options_struct
{
  const char *keyword;
  const char *kw_tok[MAX_TOKENS + 1];
  int min_len[MAX_TOKENS + 1];
  int min_toks_to_match;
};

#define NUM_OPTIONS 1

static NLEqn_options_struct NLEqn_options_table [] =
{
  { "tolerance",
    { "tolerance", 0, },
    { 0, 0, }, 1, },
};

static void
print_NLEqn_options (std::ostream& os)
{
  print_usage ("fsolve_options", 1);

  os << "\n"
     << "Options for NLEqn include:\n\n"
     << "  keyword                                             value\n"
     << "  -------                                             -----\n";

  NLEqn_options_struct *list = NLEqn_options_table;

  {
    os << "  "
       << std::setiosflags (std::ios::left) << std::setw (50)
       << list[0].keyword
       << std::resetiosflags (std::ios::left)
       << "  ";

    double val = fsolve_opts.tolerance ();

    os << val << "\n";
  }

  os << "\n";
}

static void
set_NLEqn_options (const std::string& keyword, const octave_value& val)
{
  NLEqn_options_struct *list = NLEqn_options_table;

  if (keyword_almost_match (list[0].kw_tok, list[0].min_len,
           keyword, list[0].min_toks_to_match, MAX_TOKENS))
    {
      double tmp = val.double_value ();

      if (! error_state)
        fsolve_opts.set_tolerance (tmp);
    }
  else
    {
      warning ("fsolve_options: no match for `%s'", keyword.c_str ());
    }
}

static octave_value_list
show_NLEqn_options (const std::string& keyword)
{
  octave_value retval;

  NLEqn_options_struct *list = NLEqn_options_table;

  if (keyword_almost_match (list[0].kw_tok, list[0].min_len,
           keyword, list[0].min_toks_to_match, MAX_TOKENS))
    {
      double val = fsolve_opts.tolerance ();

      retval = val;
    }
  else
    {
      warning ("fsolve_options: no match for `%s'", keyword.c_str ());
    }

  return retval;
}

DEFUN_DLD (fsolve_options, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} fsolve_options (@var{opt}, @var{val})\n\
When called with two arguments, this function allows you set options\n\
parameters for the function @code{fsolve}.  Given one argument,\n\
@code{fsolve_options} returns the value of the corresponding option.  If\n\
no arguments are supplied, the names of all the available options and\n\
their current values are displayed.\n\
\n\
Options include\n\
\n\
@table @code\n\
@item \"tolerance\"\n\
Nonnegative relative tolerance.\n\
@end table\n\
@end deftypefn")
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin == 0)
    {
      print_NLEqn_options (octave_stdout);
    }
  else if (nargin == 1 || nargin == 2)
    {
      std::string keyword = args(0).string_value ();

      if (! error_state)
        {
          if (nargin == 1)
            retval = show_NLEqn_options (keyword);
          else
            set_NLEqn_options (keyword, args(1));
        }
      else
        error ("fsolve_options: expecting keyword as first argument");
    }
  else
    print_usage ("fsolve_options");

  return retval;
}
