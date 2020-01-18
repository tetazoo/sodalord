// DO NOT EDIT!
// Generated automatically from ../liboctave/Quad-opts.in.

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iomanip>
#include <iostream>

#include "Quad-opts.h"

#include "defun-dld.h"
#include "pr-output.h"

#include "oct-obj.h"
#include "utils.h"
#include "pager.h"

static Quad_options quad_opts;

#define MAX_TOKENS 2

struct Quad_options_struct
{
  const char *keyword;
  const char *kw_tok[MAX_TOKENS + 1];
  int min_len[MAX_TOKENS + 1];
  int min_toks_to_match;
};

#define NUM_OPTIONS 2

static Quad_options_struct Quad_options_table [] =
{
  { "absolute tolerance",
    { "absolute", "tolerance", 0, },
    { 1, 0, 0, }, 1, },

  { "relative tolerance",
    { "relative", "tolerance", 0, },
    { 1, 0, 0, }, 1, },
};

static void
print_Quad_options (std::ostream& os)
{
  print_usage ("quad_options", 1);

  os << "\n"
     << "Options for Quad include:\n\n"
     << "  keyword                                             value\n"
     << "  -------                                             -----\n";

  Quad_options_struct *list = Quad_options_table;

  {
    os << "  "
       << std::setiosflags (std::ios::left) << std::setw (50)
       << list[0].keyword
       << std::resetiosflags (std::ios::left)
       << "  ";

    double val = quad_opts.absolute_tolerance ();

    os << val << "\n";
  }

  {
    os << "  "
       << std::setiosflags (std::ios::left) << std::setw (50)
       << list[1].keyword
       << std::resetiosflags (std::ios::left)
       << "  ";

    double val = quad_opts.relative_tolerance ();

    os << val << "\n";
  }

  os << "\n";
}

static void
set_Quad_options (const std::string& keyword, const octave_value& val)
{
  Quad_options_struct *list = Quad_options_table;

  if (keyword_almost_match (list[0].kw_tok, list[0].min_len,
           keyword, list[0].min_toks_to_match, MAX_TOKENS))
    {
      double tmp = val.double_value ();

      if (! error_state)
        quad_opts.set_absolute_tolerance (tmp);
    }
  else if (keyword_almost_match (list[1].kw_tok, list[1].min_len,
           keyword, list[1].min_toks_to_match, MAX_TOKENS))
    {
      double tmp = val.double_value ();

      if (! error_state)
        quad_opts.set_relative_tolerance (tmp);
    }
  else
    {
      warning ("quad_options: no match for `%s'", keyword.c_str ());
    }
}

static octave_value_list
show_Quad_options (const std::string& keyword)
{
  octave_value retval;

  Quad_options_struct *list = Quad_options_table;

  if (keyword_almost_match (list[0].kw_tok, list[0].min_len,
           keyword, list[0].min_toks_to_match, MAX_TOKENS))
    {
      double val = quad_opts.absolute_tolerance ();

      retval = val;
    }
  else if (keyword_almost_match (list[1].kw_tok, list[1].min_len,
           keyword, list[1].min_toks_to_match, MAX_TOKENS))
    {
      double val = quad_opts.relative_tolerance ();

      retval = val;
    }
  else
    {
      warning ("quad_options: no match for `%s'", keyword.c_str ());
    }

  return retval;
}

DEFUN_DLD (quad_options, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} quad_options (@var{opt}, @var{val})\n\
When called with two arguments, this function\n\
allows you set options parameters for the function @code{quad}.\n\
Given one argument, @code{quad_options} returns the value of the\n\
corresponding option.  If no arguments are supplied, the names of all\n\
the available options and their current values are displayed.\n\
\n\
Options include\n\
\n\
@table @code\n\
@item \"absolute tolerance\"\n\
Absolute tolerance; may be zero for pure relative error test.\n\
@item \"relative tolerance\"\n\
Nonnegative relative tolerance.  If the absolute tolerance is zero,\n\
the relative tolerance must be greater than or equal to \n\
@code{max (50*eps, 0.5e-28)}.\n\
@end table\n\
@end deftypefn")
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin == 0)
    {
      print_Quad_options (octave_stdout);
    }
  else if (nargin == 1 || nargin == 2)
    {
      std::string keyword = args(0).string_value ();

      if (! error_state)
        {
          if (nargin == 1)
            retval = show_Quad_options (keyword);
          else
            set_Quad_options (keyword, args(1));
        }
      else
        error ("quad_options: expecting keyword as first argument");
    }
  else
    print_usage ("quad_options");

  return retval;
}
