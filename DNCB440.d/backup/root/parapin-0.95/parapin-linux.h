/*
 * System-specific include files for Linux
 */


#ifdef __KERNEL__

#include <linux/config.h>
#include <linux/kernel.h>
#ifdef MODULE
#include <linux/module.h>
#endif /* MODULE */
#include <linux/stddef.h>
#include <asm/io.h>
#include <asm/irq.h>
#include <linux/delay.h>
#include <linux/ioport.h>
#include <linux/parport.h>
#include <linux/parport_pc.h>
#include <linux/interrupt.h>
#include <linux/version.h>

#define printf printk

/* parallel port we found and device we registered */
struct parport *parapin_port = NULL;
struct pardevice *parapin_dev = NULL;

/* was the system configured to use the interrupt before we got here? */
static int old_irq_mode = 0;
static int have_irq_handler = 0;

#else /* __KERNEL__ */

#include <stdio.h>
#include <linux/ioport.h>
#include <sys/io.h>

#endif /* __KERNEL__ */

/***************** Linux-Specific inb() and outb() *************************/

/* base address of parallel port I/O */
static int lp_base;

#define INB(register_number) inb(lp_base + register_number)
#define OUTB(value, register_number) outb(value, lp_base + register_number)

/**************** Linux-specific Initialization Functions *******************/


#ifdef __KERNEL__

/* kernel-mode parallel port initialization.  the 'lpt' argument is
 * the LP number of the port that you want.  this code will
 * EXCLUSIVELY claim the parallel port; i.e., so that other devices
 * connected to the same parallel port will not be able to use it
 * until you call the corresponding pin_release().  */
int pin_init_kernel(int lpt, void (*irq_func)(int, void *, struct pt_regs *))
{
  /* find the port */
  for (parapin_port = parport_enumerate(); parapin_port != NULL;
       parapin_port = parapin_port->next)
    if (parapin_port->number == lpt)
      break;

  if (parapin_port == NULL) {
    printk("parapin: init failed, parallel port lp%d not found\n", lpt);
    return -ENODEV;
  }

  /* now register the device on the port for exclusive access */
  parapin_dev = parport_register_device(parapin_port,
					"parapin", /* name for debugging */
					NULL, /* preemption callback */
					NULL, /* wakeup callback */
					irq_func, /* interrupt callback */
					PARPORT_DEV_EXCL, /* flags */
					NULL); /* user data */
  if (parapin_dev == NULL)
    return -ENODEV;

  /* ok - all systems go.  claim the parallel port. */
  parport_claim(parapin_dev);

  /* remember the LP base of our parallel port */
  lp_base = parapin_port->base;

  /* put us into bidir mode if we have an ECR */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,4,0)
  if (parapin_port->modes & PARPORT_MODE_PCECR)
    parport_pc_write_econtrol(parapin_port, 0x20);
#else
  {
    struct parport_pc_private *priv = parapin_port->private_data;
    if (priv->ecr)
      outb(0x20, ECONTROL(parapin_port));
  }
#endif

  /* initialize the state of the registers */
  pin_init_internal();

  /* remember the current state of the interrupt enable flag */
  old_irq_mode = pin_is_set(LP_IRQ_MODE);
  have_irq_handler = (irq_func != NULL);

  /* disable interrupts */
  pin_disable_irq();

  /* tell the user what's happening */
  printk("parapin: claiming %s at 0x%lx, irq %d\n", parapin_port->name,
         parapin_port->base, parapin_port->irq);

  return 0;
}


/* this must be called by kernel programs when you're done using the
   parallel port.  it releases the port to be used by other apps. */
void pin_release()
{
  /* restore interrupts to their former state */
  change_pin(LP_IRQ_MODE, old_irq_mode ? LP_SET : LP_CLEAR);

  /* release and unregister the parallel port */
  parport_release(parapin_dev);
  parport_unregister_device(parapin_dev);
}


/* are interrupts available? */
int pin_have_irq()
{
  return (parapin_port && have_irq_handler && (parapin_port->irq >= 0));
}

/* turn interrupts on */
void pin_enable_irq()
{
  if (pin_have_irq()) {
    set_pin(LP_IRQ_MODE);
    udelay(10); /* wait for the spurious interrupt (if any) to pass */
    enable_irq(parapin_port->irq);
  }
}

/* turn interrupts off */
void pin_disable_irq()
{
  if (parapin_port && parapin_port->irq >= 0)
    disable_irq(parapin_port->irq);
  clear_pin(LP_IRQ_MODE);
}


#else  /* user-space-only functions */

/* user-land initialization */
int pin_init_user(int base)
{
  lp_base = base;

  /* get write permission to the I/O port */
  if (ioperm(lp_base, 3, 1) < 0) {
    perror("can't get IO permissions!");
    return -1;
  }

  pin_init_internal();
  return 0;
}

#endif /* __KERNEL__ */

