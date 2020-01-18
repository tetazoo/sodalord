// DO NOT EDIT!
// Generated automatically from NLEqn-opts.in.

#if !defined (octave_NLEqn_options_h)
#define octave_NLEqn_options_h 1

#include <cfloat>
#include <cmath>

#include <dColVector.h>
#include <NLFunc.h>


class
NLEqn_options
{
public:

  NLEqn_options (void) { init (); }

  NLEqn_options (const NLEqn_options& opt) { copy (opt); }

  NLEqn_options& operator = (const NLEqn_options& opt)
    {
      if (this != &opt)
        copy (opt);

      return *this;
    }

  ~NLEqn_options (void) { }

  void init (void)
    {
      x_tolerance = ::sqrt (DBL_EPSILON);
      reset = true;
    }

  void copy (const NLEqn_options& opt)
    {
      x_tolerance = opt.x_tolerance;
      reset = opt.reset;
    }

  void set_options (const NLEqn_options& opt) { copy (opt); }

  void set_default_options (void) { init (); }

  void set_tolerance (double val)
    { x_tolerance = (val > 0.0) ? val : ::sqrt (DBL_EPSILON); reset = true; }
  double tolerance (void) const
    { return x_tolerance; }

private:

  double x_tolerance;

protected:

  bool reset;
};

#endif
