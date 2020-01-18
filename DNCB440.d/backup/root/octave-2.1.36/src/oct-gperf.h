/* ANSI-C code produced by gperf version 2.7.2 */
/* Command-line: gperf -t -C -D -E -G -L ANSI-C -H octave_kw_hash -N octave_kw_lookup octave.gperf  */

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
  while_kw
};

struct octave_kw { const char *name; int tok; octave_kw_id kw_id; };
enum
  {
    TOTAL_KEYWORDS = 34,
    MIN_WORD_LENGTH = 2,
    MAX_WORD_LENGTH = 22,
    MIN_HASH_VALUE = 2,
    MAX_HASH_VALUE = 56
  };

/* maximum key range = 55, duplicates = 1 */

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
      57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57,  5, 57, 20, 10, 30,
       0,  0,  0, 15, 15,  5, 57,  0,  5, 57,
      40,  0,  0, 57, 10,  0, 25,  0, 57, 15,
      57,  5, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57
    };
  return len + asso_values[(unsigned char)str[len - 1]] + asso_values[(unsigned char)str[0]];
}

static const struct octave_kw wordlist[] =
  {
    {"do", DO, do_kw},
    {"end", END, end_kw},
    {"else", ELSE, else_kw},
    {"endif", END, endif_kw},
    {"elseif", ELSEIF, elseif_kw},
    {"if", IF, if_kw},
    {"endwhile", END, endwhile_kw},
    {"otherwise", OTHERWISE, otherwise_kw},
    {"until", UNTIL, until_kw},
    {"for", FOR, for_kw},
    {"break", BREAK, break_kw},
    {"endfor", END, endfor_kw},
    {"__FILE__", TEXT, magic_file_kw},
    {"__LINE__", NUM, magic_line_kw},
    {"while", WHILE, while_kw},
    {"switch", SWITCH, switch_kw},
    {"unwind_protect_cleanup", CLEANUP, unwind_protect_cleanup_kw},
    {"endswitch", END, endswitch_kw},
    {"global", GLOBAL, global_kw},
    {"end_try_catch", END, end_try_catch_kw},
    {"all_va_args", ALL_VA_ARGS, all_va_args_kw},
    {"try", TRY, try_kw},
    {"case", CASE, case_kw},
    {"static", STATIC, static_kw},
    {"continue", CONTINUE, continue_kw},
    {"unwind_protect", UNWIND, unwind_protect_kw},
    {"replot", PLOT, replot_kw},
    {"end_unwind_protect", END, end_unwind_protect_kw},
    {"gplot", PLOT, gplot_kw},
    {"gsplot", PLOT, gsplot_kw},
    {"function", FCN, function_kw},
    {"catch", CATCH, catch_kw},
    {"endfunction", END, endfunction_kw},
    {"return", FUNC_RET, return_kw}
  };

static const signed char gperf_lookup[] =
  {
     -1,  -1,   0,   1,   2,   3,   4,   5,   6,   7,
      8,  -1,  -1,   9,  -1,  10,  11,  -1, -64,  -1,
     14,  15,  16,  -1,  17,  -1,  18,  -1,  19, -22,
     -2,  20,  -1,  21,  22,  -1,  23,  -1,  24,  25,
     -1,  26,  -1,  27,  -1,  28,  29,  -1,  30,  -1,
     31,  32,  -1,  -1,  -1,  -1,  33
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
          else if (index < -TOTAL_KEYWORDS)
            {
              register int offset = - 1 - TOTAL_KEYWORDS - index;
              register const struct octave_kw *wordptr = &wordlist[TOTAL_KEYWORDS + gperf_lookup[offset]];
              register const struct octave_kw *wordendptr = wordptr + -gperf_lookup[offset + 1];

              while (wordptr < wordendptr)
                {
                  register const char *s = wordptr->name;

                  if (*str == *s && !strcmp (str + 1, s + 1))
                    return wordptr;
                  wordptr++;
                }
            }
        }
    }
  return 0;
}
