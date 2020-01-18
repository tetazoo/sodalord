#
# Parapin Makefile
#
# Jeremy Elson, First released 30 March 2000
#
# $Id: Makefile,v 1.12 2001/12/28 20:47:00 jelson Exp $
#

# Set this flag depending on what OS you are compiling under
OSFLAG := -DPARAPIN_LINUX
#OSFLAG := -DPARAPIN_QNX

CC := gcc
CFLAGS := $(OSFLAG) -O2 -g -Wall

EXAMPLE_DIR := examples
EXAMPLE_PROGRAMS := \
	$(EXAMPLE_DIR)/inputtest \
	$(EXAMPLE_DIR)/outputtest\
	$(EXAMPLE_DIR)/adc0831

LIBPARAPIN_OBJS := parapin.o

###########################################################################


default: libparapin.a $(EXAMPLE_PROGRAMS) kparapin.o

install: libparapin.a
	/usr/bin/install -o bin -g bin -m 755 libparapin.a /usr/local/lib
	/usr/bin/install -o bin -g bin -m 444 parapin.h /usr/local/include


##### libraries

libparapin.a: $(LIBPARAPIN_OBJS)
	ar -cr libparapin.a $(LIBPARAPIN_OBJS)

parapin.o: parapin.c parapin.h
	$(CC) $(CFLAGS) -c parapin.c

kparapin.o: parapin.c parapin.h
	$(CC) $(CFLAGS) -D__KERNEL__ -DMODULE -o kparapin.o -c parapin.c


# Example programs and the test suite

$(EXAMPLE_DIR)/%: $(EXAMPLE_DIR)/%.c libparapin.a parapin.h
	$(CC) $(CFLAGS) -I. -L. $< -o $@ -lparapin


clean:
	rm -f *.[oa] $(EXAMPLE_PROGRAMS)

