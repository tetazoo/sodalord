#
# Makefile for octave's doc/refcard directory
#
# John W. Eaton
# jwe@bevo.che.wisc.edu
# University of Wisconsin-Madison
# Department of Chemical Engineering

TOPDIR = ../..

srcdir = .
top_srcdir = ../..


include $(TOPDIR)/Makeconf

INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL}
INSTALL_DATA = ${INSTALL} -m 644

TEX := refcard.tex refcard-a4.tex refcard-legal.tex refcard-letter.tex 

FORMATTED := refcard-a4.dvi refcard-a4.ps refcard-a4.pdf \
	refcard-legal.dvi refcard-legal.ps refcard-legal.pdf \
	refcard-letter.dvi refcard-letter.ps refcard-letter.pdf

DISTFILES := Makefile.in $(TEX) $(FORMATTED)

ifeq ($(wildcard refcard-letter.ps), )
  BINDISTFILES = $(addprefix $(srcdir)/, $(FORMATTED))
else
  BINDISTFILES = $(FORMATTED)
endif

all: $(FORMATTED)

refcard-a4.dvi: refcard-a4.tex refcard.tex
	-TEXINPUTS="$(srcdir):$(TEXINPUTS):"; export TEXINPUTS; \
	  tex $(srcdir)/refcard-a4.tex

refcard-a4.ps: refcard-a4.dvi
	-dvips -T 297mm,210mm -o refcard-a4.ps refcard-a4.dvi

refcard-a4.pdf: refcard-a4.tex refcard.tex
	-TEXINPUTS="$(srcdir):$(TEXINPUTS):"; export TEXINPUTS; \
	  pdftex $(srcdir)/refcard-a4.tex

refcard-legal.dvi: refcard-legal.tex refcard.tex
	-TEXINPUTS="$(srcdir):$(TEXINPUTS):"; export TEXINPUTS; \
	  tex $(srcdir)/refcard-legal.tex

refcard-legal.ps: refcard-legal.dvi
	-dvips -T 14in,8.5in -o refcard-legal.ps refcard-legal.dvi

refcard-legal.pdf: refcard-legal.tex refcard.tex
	-TEXINPUTS="$(srcdir):$(TEXINPUTS):"; export TEXINPUTS; \
	  pdftex $(srcdir)/refcard-legal.tex

refcard-letter.dvi: refcard-letter.tex refcard.tex
	-TEXINPUTS="$(srcdir):$(TEXINPUTS):"; export TEXINPUTS; \
	  tex $(srcdir)/refcard-letter.tex

refcard-letter.ps: refcard-letter.dvi
	-dvips -T 11in,8.5in -o refcard-letter.ps refcard-letter.dvi

refcard-letter.pdf: refcard-letter.tex refcard.tex
	-TEXINPUTS="$(srcdir):$(TEXINPUTS):"; export TEXINPUTS; \
	  pdftex $(srcdir)/refcard-letter.tex

check install install-strip uninstall:
.PHONY: check install install-strip uninstall

tags: $(SOURCES)
	ctags $(SOURCES)

TAGS: $(SOURCES)
	etags $(SOURCES)

mostlyclean clean:
	rm -f refcard-*.log
.PHONY: mostlyclean clean

distclean: clean
	rm -f Makefile
.PHONY: distclean

maintainer-clean: distclean
	rm -f tags TAGS	refcard-*.dvi refcard-*.ps refcard-*.pdf
.PHONY: maintainer-clean

dist: all
	ln $(DISTFILES) ../../`cat ../../.fname`/doc/refcard
.PHONY: dist

bin-dist:
	if [ -n "$(BINDISTFILES)" ]; then \
	  ln $(BINDISTFILES) ../../`cat ../../.fname`/doc/refcard; \
	fi
.PHONY: bin-dist
