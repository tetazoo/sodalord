/*
 * System-specific include files for QNX Neutrino
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/neutrino.h>
#include <hw/inout.h>
#include <sys/mman.h>
#include <inttypes.h>

/***************** QNX-Specific inb() and outb() *************************/

/* base address of parallel port I/O */
static uintptr_t mmap_handle[3];

#define INB(register_number) in8(mmap_handle[register_number])
#define OUTB(value, register_number) out8(mmap_handle[register_number], value)

/**************** QNX-specific Initialization Functions *******************/


/* user-land initialization */
int pin_init_user(int base)
{
  int i;

  /* printf("Get permissions.\n"); */
  if (ThreadCtl(_NTO_TCTL_IO, NULL) < 0) {
    printf("Failed to get permsissions.\n");
    perror("gpio");
    return -1;
  }

  for (i = 0; i < 3; i++) {
    if ((mmap_handle[i] = mmap_device_io(1, (base + i))) ==
	(_uintptr)MAP_FAILED) {
      perror("mmap");
      return -1;
    }
  }

  pin_init_internal();
  return 0;
}


