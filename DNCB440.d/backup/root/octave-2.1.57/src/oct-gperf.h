/* ANSI-C code produced by gperf version 3.0.1 */
/* Command-line: gperf -t -C -D -E -G -L ANSI-C -H octave_kw_hash -N octave_kw_lookup octave.gperf  */
/* Computed positions: -k'2-3' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif

#line 1 "octave.gperf"


enum octave_kw_id
{
  all_va_args_kw,
  break_kw,
  case_kw,
  catch_kw,
  continue_kw,
  do_kw,
  else_kw,
  elseif_kw,
  end_kw,
  end_try_catch_kw,
  end_unwind_protect_kw,
  endfor_kw,
  endfunction_kw,
  endif_kw,
  endswitch_kw,
  endwhile_kw,
  for_kw,
  function_kw,
  global_kw,
  gplot_kw,
  gsplot_kw,
  if_kw,
  magic_file_kw,
  magic_line_kw,
  otherwise_kw,
  replot_kw,
  return_kw,
  static_kw,
  switch_kw,
  try_kw,
  until_kw,
  unwind_protect_kw,
  unwind_protect_cleanup_kw,
  varargin_kw,
  varargout_kw,
  while_kw
};

#line 44 "octave.gperf"
struct octave_kw { const char *name; int tok; octave_kw_id kw_id; };
enum
  {
    TOTAL_KEYWORDS = 37,
    MIN_WORD_LENGTH = 2,
    MAX_WORD_LENGTH = 22,
    MIN_HASH_VALUE = 2,
    MAX_HASH_VALUE = 75
  };

/* maximum key range = 74, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
octave_kw_hash (register const char *str, register unsigned int len)
{
  static const unsigned char asso_values[] =
    {
      76, 76, 76, 76, 76, 76, 76, 76, 76, 76,
      76, 76, 76, 76, 76, 76, 76, 76, 76, 76,
      76, 76, 76, 76, 76, 76, 76, 76, 76, 76,
      76, 76, 76, 76, 76, 76, 76, 76, 76, 76,
      76, 76, 76, 76, 76, 76, 76, 76, 76, 76,
      76, 76, 76, 76, 76, 76, 76, 76, 76, 76,
      76, 76, 76, 76, 76, 76, 76, 76, 76, 76,
      30, 76, 76, 76, 76, 76, 25, 76, 76, 76,
      76, 76, 76, 76, 76, 76, 76, 76, 76, 76,
      76, 76, 76, 76, 76, 20, 76, 15, 76, 76,
       5, 30,  0, 76, 30, 40, 76, 76, 10, 76,
       0, 30, 25, 76, 10, 10,  0, 40, 76,  5,
      76, 15, 76, 76, 76, 76, 76, 76, 76, 76,
      76, 76, 76, 76, 76, 76, 76, 76, 76, 76,
      76, 76, 76, 76, 76, 76, 76, 76, 76, 76,
      76, 76, 76, 76, 76, 76, 76, 76, 76, 76,
      76, 76, 76, 76, 76, 76, 76, 76, 76, 76,
      76, 76, 76, 76, 76, 76, 76, 76, 76, 76,
      76, 76, 76, 76, 76, 76, 76, 76, 76, 76,
      76, 76, 76, 76, 76, 76, 76, 76, 76, 76,
      76, 76, 76, 76, 76, 76, 76, 76, 76, 76,
      76, 76, 76, 76, 76, 76, 76, 76, 76, 76,
      76, 76, 76, 76, 76, 76, 76, 76, 76, 76,
      76, 76, 76, 76, 76, 76, 76, 76, 76, 76,
      76, 76, 76, 76, 76, 76, 76, 76, 76, 76,
      76, 76, 76, 76, 76, 76
    };
  register int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[2]];
      /*FALLTHROUGH*/
      case 2:
        hval += asso_values[(unsigned char)str[1]];
        break;
    }
  return hval;
}

static const struct octave_kw wordlist[] =
  {
#line 67 "octave.gperf"
    {"if", IF, if_kw},
#line 75 "octave.gperf"
    {"until", UNTIL, until_kw},
#line 54 "octave.gperf"
    {"end", END, end_kw},
#line 59 "octave.gperf"
    {"endif", END, endif_kw},
#line 57 "octave.gperf"
    {"endfor", END, endfor_kw},
#line 61 "octave.gperf"
    {"endwhile", END, endwhile_kw},
#line 60 "octave.gperf"
    {"endswitch", END, endswitch_kw},
#line 58 "octave.gperf"
    {"endfunction", END, endfunction_kw},
#line 55 "octave.gperf"
    {"end_try_catch", END, end_try_catch_kw},
#line 76 "octave.gperf"
    {"unwind_protect", UNWIND, unwind_protect_kw},
#line 49 "octave.gperf"
    {"catch", CATCH, catch_kw},
#line 72 "octave.gperf"
    {"static", STATIC, static_kw},
#line 56 "octave.gperf"
    {"end_unwind_protect", END, end_unwind_protect_kw},
#line 52 "octave.gperf"
    {"else", ELSE, else_kw},
#line 53 "octave.gperf"
    {"elseif", ELSEIF, elseif_kw},
#line 77 "octave.gperf"
    {"unwind_protect_cleanup", CLEANUP, unwind_protect_cleanup_kw},
#line 74 "octave.gperf"
    {"try", TRY, try_kw},
#line 48 "octave.gperf"
    {"case", CASE, case_kw},
#line 46 "octave.gperf"
    {"all_va_args", ALL_VA_ARGS, all_va_args_kw},
#line 51 "octave.gperf"
    {"do", DO, do_kw},
#line 78 "octave.gperf"
    {"varargin", VARARGIN, varargin_kw},
#line 79 "octave.gperf"
    {"varargout", VARARGOUT, varargout_kw},
#line 71 "octave.gperf"
    {"return", FUNC_RET, return_kw},
#line 50 "octave.gperf"
    {"continue", CONTINUE, continue_kw},
#line 68 "octave.gperf"
    {"otherwise", OTHERWISE, otherwise_kw},
#line 65 "octave.gperf"
    {"gplot", PLOT, gplot_kw},
#line 66 "octave.gperf"
    {"gsplot", PLOT, gsplot_kw},
#line 62 "octave.gperf"
    {"for", FOR, for_kw},
#line 47 "octave.gperf"
    {"break", BREAK, break_kw},
#line 64 "octave.gperf"
    {"global", GLOBAL, global_kw},
#line 63 "octave.gperf"
    {"function", FCN, function_kw},
#line 69 "octave.gperf"
    {"persistent", STATIC, static_kw},
#line 73 "octave.gperf"
    {"switch", SWITCH, switch_kw},
#line 82 "octave.gperf"
    {"__LINE__", NUM, magic_line_kw},
#line 81 "octave.gperf"
    {"__FILE__", STRING, magic_file_kw},
#line 70 "octave.gperf"
    {"replot", PLOT, replot_kw},
#line 80 "octave.gperf"
    {"while", WHILE, while_kw}
  };

static const signed char gperf_lookup[] =
  {
    -1, -1,  0, -1, -1,  1, -1, -1,  2, -1,  3,  4, -1,  5,
     6, -1,  7, -1,  8,  9, 10, 11, -1, 12, 13, -1, 14, 15,
    16, 17, -1, 18, 19, 20, 21, -1, 22, -1, 23, 24, 25, 26,
    -1, 27, -1, 28, 29, -1, 30, -1, 31, 32, -1, 33, -1, -1,
    -1, -1, 34, -1, -1, 35, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, 36
  };

#ifdef __GNUC__
__inline
#endif
const struct octave_kw *
octave_kw_lookup (register const char *str, register unsigned int len)
{
  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = octave_kw_hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register int index = gperf_lookup[key];

          if (index >= 0)
            {
              register const char *s = wordlist[index].name;

              if (*str == *s && !strcmp (str + 1, s + 1))
                return &wordlist[index];
            }
        }
    }
  return 0;
}
