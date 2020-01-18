/*#define DEBUG*/
/*
 * parapin
 *
 * $Id: parapin.c,v 1.14 2000/12/08 13:12:32 jelson Exp $
 *
 * $Log: parapin.c,v $
 * Revision 1.14  2000/12/08 13:12:32  jelson
 * Oops... refixed the extern-c problem for C++ compiling
 *
 * Revision 1.13  2000/12/08 13:01:24  jelson
 * Added "extern C" so it compiles using C++
 *
 * Revision 1.12  2000/10/31 06:24:42  jelson
 * Roughly split parapin into architecture-dependant and architecture-
 * independant files, and added a port to QNX.
 *
 * Revision 1.11  2000/10/30 23:42:01  jelson
 * -- redesigned initialization with a more minimalist style - we don't
 *    try to reset the parallel port to a known state, but instead let
 *    it ride
 * -- various minor bugfixes w.r.t. how pins are get/set - i.e. doing read
 *    before write for safety.
 *
 * Revision 1.10  2000/03/25 00:58:36  jelson
 * fixed bug in interrupt handling
 *
 * Revision 1.9  2000/03/24 21:13:46  jelson
 * more changes for interrupt handling
 *
 * Revision 1.8  2000/03/24 01:39:03  jelson
 * More functions in support of interrupt handling
 *
 * Revision 1.7  2000/03/23 01:25:09  jelson
 * Corrected bit number of IRQ enable line
 *
 * Revision 1.6  2000/03/22 05:06:28  jelson
 * Mostly minor interface changes (e.g., changes to constant names) to make
 * the interface cleaner... correcting problems that came up when I was writing
 * the documentation.
 *
 * Added a way to pass a pointer to an interrupt handler through parapin to
 * the kernel.
 *
 * Revision 1.5  2000/03/14 23:57:48  jelson
 * mostly minor changes -- cleanup for public release
 *
 * Revision 1.4  2000/03/14 21:12:42  jelson
 * Made parapin more kernel friendly -- it now has different initialization
 * functions for user-land use vs. kernel-land use.  The kernel version of
 * the library uses the "parport" functions to register itself as a parallel
 * device and claim exclusive access to the parallel port.
 *
 * Revision 1.3  2000/03/08 01:34:26  jelson
 * Minor changes to make parapin kernel-friendly
 *
 * Revision 1.2  1999/05/26 06:43:39  jelson
 * *** empty log message ***
 *
 * Revision 1.1  1999/05/24 03:59:30  jelson
 * first version of new parapin programming library
 *
 */

#include "parapin.h"

/* prototypes for functions defined later in the file */
static void pin_init_internal();

#ifdef PARAPIN_LINUX
# include "parapin-linux.h"
#endif

#ifdef PARAPIN_QNX
# include "parapin-qnx.h"
#endif


/* most recently read or written values of the three parallel port I/O
 * registers.  kept in TRUE logic; i.e. the actual high/low electrical
 * state on the pins, NOT the values of register bits. */
static int lp_register[3];

/* masks of pins that we currently allow input and output on */
static int lp_input_pins;
static int lp_output_pins;



/************************* Basic Utilities *****************************/


#ifdef DEBUG
char *bin_to_char(int num)
{
  int i;
  static char buf[9];

  buf[8] = '\0';

  for (i = 0; i < 8; i++) {
    if (num & (1 << i))
      buf[7-i] = '1';
    else
      buf[7-i] = '0';
  }

  return buf;
      
}
#endif

/* read a byte from an I/O port (base + regnum), correct for inverted
 * logic on some bits, and store in the lp_register variable.  Return
 * the value read.  */
static inline int read_register(int regnum)
{
#ifdef DEBUG
  int result;

  result = (lp_register[regnum] = (INB(regnum) ^ lp_invert_masks[regnum]));

  printf("read %s from register %d\n", bin_to_char(result), regnum);

  return result;
#else
  return lp_register[regnum] = (INB(regnum) ^ lp_invert_masks[regnum]);
#endif
}


/* store the written value in the lp_register variable, correct for
 * inverted logic on some bits, and write a byte to an I/O port (base
 * + regnum) */
static inline void write_register(int value, int regnum) 
{
#ifdef DEBUG
  printf("writing %s to register %d\n",
	 bin_to_char(value ^ lp_invert_masks[regnum]), regnum);
#endif
  OUTB((lp_register[regnum] = value) ^ lp_invert_masks[regnum], regnum);
}


/********************* Initialization *************************************/


/* Initialization that kernel-mode and user-mode have in common */
static void pin_init_internal()
{
  /* i've redesigned how the library is initialized with a very
   * minimalist approach: instead of trying to figure out what values
   * are "safe", we just avoid touching the parallel port registers
   * *at all* until the user tells us to do so.  accordingly, all
   * switchable pins are in neither input nor output mode to start
   * with.  this enforces the fact that outputs/inputs can not be used
   * until a pin is explicitly configured as either an input or output
   * pin.
   *
   * note that it is always legal to read from and write to the
   * "pseudo pins" of INPUT_MODE and IRQ_MODE because these are
   * actually control bits.
   */

  lp_output_pins = LP_INPUT_MODE | LP_IRQ_MODE;
  lp_input_pins = LP_ALWAYS_INPUT_PINS | LP_INPUT_MODE | LP_IRQ_MODE;
}



/******************** Pin Setting and Clearing **************************/


/* set output pins in the data register.  we'll do read-before-write,
 * just to be safe.*/
static inline void set_datareg(int pins)
{
  write_register(read_register(0) | pins, 0);
}

/* clear output pins in the data register.  we'll do
 * read-before-write, just to be safe. */
static inline void clear_datareg(int pins)
{
  write_register((read_register(0) & (~pins)), 0);
}

/* set output pins in the control register */
static inline void set_controlreg(int pins)
{
  /* the control register requires:
   *    - switchable pins that are currently being used as inputs must be 1
   *    - all other pins may be either set or cleared
   */

  /* read existing register into lp_register[2] */
  read_register(2);

  /* set the requested bits to 1, leaving the others unchanged */
  lp_register[2] |= pins;

  /* set all inputs to one (they may have been read as 0's!) 1 */
  lp_register[2] |= (0x0f & ((lp_input_pins & LP_SWITCHABLE_PINS) >> 16));

  /* write it back */
  write_register(lp_register[2], 2);
}


/* clear output pins in the control register */
static inline void clear_controlreg(int pins)
{
  /* the control register requires:
   *    - switchable pins that are currently being used as inputs must be 1
   *    - all other pins may be either set or cleared
   */

  /* read existing register into lp_register[2] */
  read_register(2);

  /* clear the requested pins, leaving others unchanged */
  lp_register[2] &= (~pins);

  /* set all inputs to one (they may have been read as 0's!) 1 */
  lp_register[2] |= (0x0f & ((lp_input_pins & LP_SWITCHABLE_PINS) >> 16));

  /* write it back */
  write_register(lp_register[2], 2);
}



/*
 * externally visible function: set_pin(int pins)
 *
 * this can be used to set any number of pins without disturbing other pins.
 *
 * example: set_pin(LP_PIN02 | LP_PIN05 | LP_PIN07)
 */
void set_pin(int pins)
{
  /* make sure the user is only trying to set an output pin */
  pins &= lp_output_pins;

  /* is user trying to set pins high that are data-register controlled? */
  if (pins & LPBASE0_MASK)
    set_datareg(pins & LPBASE0_MASK);

  /* is user trying to set pins high that are control-register controlled? */
  if (pins & LPBASE2_MASK)
    set_controlreg((pins & LPBASE2_MASK) >> 16);
}

/*
 * externally visible function: clear_pin(int pins)
 *
 * same interface as set_pin, except that it clears instead
 */
void clear_pin(int pins)
{
  /* make sure the user is only trying to set an output pin */
  pins &= lp_output_pins;

  /* is user trying to clear pins that are data-register controlled? */
  if (pins & LPBASE0_MASK)
    clear_datareg(pins & LPBASE0_MASK);

  /* is user trying to clear pins that are control-register controlled? */
  if (pins & LPBASE2_MASK)
    clear_controlreg((pins & LPBASE2_MASK) >> 16);
}


/*
 * a different interface to set_pin and change_pin;
 *
 * change_pin(X, LP_SET) is the same as set_pin(X);
 * change_pin(X, LP_CLEAR) is the same as clear_pin(X);
 */
void change_pin(int pins, int mode)
{
  if (mode == LP_SET)
    set_pin(pins);
  else if (mode == LP_CLEAR)
    clear_pin(pins);
}


/* pin_is_set: takes any number of pins to check, and returns a
 * corresponding bitvector with 1's set on pins that are electrically
 * high. */
int pin_is_set(int pins)
{
  int result = 0;

  /* make sure the user is only trying to read an output pin */
  pins &= lp_input_pins;

  if (pins & LPBASE0_MASK) {
    result |= (read_register(0) & (pins & LPBASE0_MASK));
  }

  if (pins & LPBASE1_MASK) {
    result |= ((read_register(1) & ((pins & LPBASE1_MASK) >> 8)) << 8);
  }

  if (pins & LPBASE2_MASK) {
    result |= ((read_register(2) & ((pins & LPBASE2_MASK) >> 16)) << 16);
  }

  return result;
}



/************************* Direction Changing *****************************/

/* change the data pins (pins 2-9) to input mode */
static void dataline_input_mode()
{
#ifdef DEBUG
  printf("setting input mode on data pins\n");
#endif
  lp_input_pins |= LP_DATA_PINS;
  lp_output_pins &= (~LP_DATA_PINS);
  set_pin(LP_INPUT_MODE);
}


static void dataline_output_mode()
{
#ifdef DEBUG
  printf("setting output mode on data pins\n");
#endif
  lp_input_pins &= (~LP_DATA_PINS);
  lp_output_pins |= LP_DATA_PINS;
  clear_pin(LP_INPUT_MODE);
}


static void controlreg_input_mode(int pins)
{
#ifdef DEBUG
  printf("setting control-reg input mode\n");
#endif
  lp_input_pins |= pins;
  lp_output_pins &= (~pins);
  set_controlreg(0);
}

static void controlreg_output_mode(int pins)
{
#ifdef DEBUG
  printf("setting control-reg output mode\n");
#endif
  lp_input_pins &= (~pins);
  lp_output_pins |= pins;
  set_controlreg(0);
}


/* user-visible function to change pins to input mode */
void pin_input_mode(int pins)
{
  if (pins & LP_DATA_PINS)
    dataline_input_mode();
  if (pins & LP_SWITCHABLE_PINS)
    controlreg_input_mode(pins & LP_SWITCHABLE_PINS);
}

/* user-visible function to change pins to output mode */
void pin_output_mode(int pins)
{
  if (pins & LP_DATA_PINS)
    dataline_output_mode();
  if (pins & LP_SWITCHABLE_PINS)
    controlreg_output_mode(pins & LP_SWITCHABLE_PINS);
}

/* another interface to pin_input_mode and pin_output_mode */
void pin_mode(int pins, int mode)
{
  if (mode == LP_INPUT)
    pin_input_mode(pins);
  if (mode == LP_OUTPUT)
    pin_output_mode(pins);
}

