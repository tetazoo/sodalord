#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "parapin.h"

int main(int argc, char *argv[])
{
  int pin;
  if(argc < 2)
    {
      printf("USAGE: setlp0pin pin#\n");
      exit(1);
    }
  pin = atoi(argv[1]);
  if (pin_init_user(LPT1) < 0)
    exit(0);
  pin_output_mode(LP_DATA_PINS | LP_SWITCHABLE_PINS);

  if(pin < 0)  // clear requested
    {
      pin = pin * -1;
      clear_pin(LP_PIN[pin]);
      printf("pin# %d cleared\n", pin);
    }
  else
    {

      set_pin(LP_PIN[pin]);
      printf("pin# %d set.  Run \"setlp0pin -%d\" to clear pin# %d\n", pin, pin, pin);
    }
  return 0;
}
