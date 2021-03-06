#
# Makefile for octave's doc/interpreter directory
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

SUB_SOURCE := arith.txi audio.txi basics.txi bugs.txi \
	container.txi control.txi cp-idx.txi data.txi \
	debug.txi diffeq.txi emacs.txi errors.txi eval.txi \
	expr.txi finance.txi fn-idx.txi func.txi gpl.txi \
	grammar.txi image.txi install.txi intro.txi io.txi \
	linalg.txi matrix.txi nonlin.txi numbers.txi \
	op-idx.txi optim.txi plot.txi poly.txi preface.txi \
	quad.txi quaternion.txi set.txi signal.txi stats.txi \
	stmt.txi stream.txi strings.txi struct.txi system.txi \
	tips.txi var.txi vr-idx.txi

SOURCES := $(SUB_SOURCE)

MAIN_TEXINFO := $(srcdir)/octave.texi

SUB_TEXINFO := $(SUB_SOURCE:.txi=.texi)

TEXINFO := $(MAIN_TEXINFO) $(SUB_TEXINFO)

FORMATTED = octave.dvi octave.ps \
	octave.info octave.info-[0-9]* \
	octave.html octave_*.html

MAN_BASE := mkoctfile octave octave-bug octave-config
MAN_SRC := $(addsuffix .1, $(MAN_BASE))

DISTFILES = Makefile.in dir munge-texi.cc $(MAN_SRC) \
  $(SOURCES) $(TEXINFO) $(FORMATTED)

ifeq ($(wildcard octave.info), )
  BINDISTFILES = $(addprefix $(srcdir)/, $(MAN_SRC) $(FORMATTED))
else
  BINDISTFILES = $(addprefix $(srcdir)/, $(MAN_SRC)) $(FORMATTED)
endif

# Look for version.h to get version information.
xfiles := $(TOPDIR)/src/version.h $(srcdir)/$(TOPDIR)/src/version.h

version_file := $(firstword $(foreach file, $(xfiles), $(wildcard $(file))))

SPELL = $(patsubst %.texi, %.spell, $(TEXINFO))

%.spell : %.texi
	rm -f $@
	$(SED) -e 's/@@/ at /g' -e 's/@[a-zA-Z]*//g' $< | spell > $@.tmp
	mv $@.tmp $@

all: octave.info octave.dvi octave.ps octave_toc.html
.PHONY: all

$(TEXINFO): src-DOCSTRINGS scripts-DOCSTRINGS munge-texi$(BUILD_EXEEXT)

munge-texi$(BUILD_EXEEXT): munge-texi.cc
	$(BUILD_CXX) $(BUILD_CXXFLAGS) -o $@ $^ $(BUILD_LDFLAGS)

src-DOCSTRINGS:
	$(MAKE) -C ../../src DOCSTRINGS
.PHONY: src-DOCSTRINGS

scripts-DOCSTRINGS:
	$(MAKE) -C ../../scripts DOCSTRINGS
.PHONY: scripts-DOCSTRINGS

%.texi : %.txi
	@echo making $@ from $<
	@./munge-texi \
	  -d $(TOPDIR)/src/DOCSTRINGS \
	  -d $(TOPDIR)/scripts/DOCSTRINGS < $< > $@.t
	@$(top_srcdir)/move-if-change $@.t $@

octave.info: $(MAIN_TEXINFO) $(SUB_TEXINFO) ../conf.texi
	-makeinfo -I$(srcdir) -I$(srcdir)/.. $<

octave.dvi: $(MAIN_TEXINFO) $(SUB_TEXINFO) ../conf.texi
	-TEXINPUTS="$(srcdir):$(srcdir)/..:$(TEXINPUTS):"; \
	  export TEXINPUTS; \
	  $(TEXI2DVI) $<

octave.ps: octave.dvi
	-dvips -o octave.ps octave.dvi

../../INSTALL.OCTAVE: install.texi
	rm -f INSTALL
	-makeinfo -D INSTALLONLY \
	  --no-validate --no-headers --no-split --output INSTALL \
	  -I$(srcdir) -I$(srcdir)/.. $<
	mv INSTALL ../../INSTALL.OCTAVE

../../BUGS: bugs.texi
	rm -f BUGS
	-makeinfo -D BUGSONLY \
	  --no-validate --no-headers --no-split --output BUGS \
	  -I$(srcdir) -I$(srcdir)/.. $<
	mv BUGS ../../BUGS

# These option forms are supported by texi2html 1.65 and probably also
# more recent versions.
octave_toc.html: $(MAIN_TEXINFO) $(SUB_TEXINFO)
	-texi2html -expandinfo -split_chapter -I . -I $(srcdir)/.. $<

check: all
.PHONY: check

install install-strip: all
	$(top_srcdir)/mkinstalldirs $(DESTDIR)$(man1dir) $(DESTDIR)$(infodir)
	@if test -d $(DESTDIR)$(man1dir); then \
	  for f in $(MAN_BASE); do \
	    rm -f $(DESTDIR)$(man1dir)/$$f$(man1ext); \
	    echo "installing $(srcdir)/$$f.1 in $(DESTDIR)$(man1dir)"; \
	    $(INSTALL_DATA) $(srcdir)/$$f.1 $(DESTDIR)$(man1dir)/$$f$(man1ext); \
	  done ; \
	fi
	@if test -d $(DESTDIR)$(infodir); then \
	  rm -f $(DESTDIR)$(infodir)/octave.info*; \
	  echo "installing info files in $(DESTDIR)$(infodir)"; \
	  if test -f octave.info; then \
	    for f in octave.info*; do \
	      $(INSTALL_DATA) $$f $(DESTDIR)$(infodir)/$$f; \
	    done; \
	  else \
	    for f in $(srcdir)/octave.info*; do \
	      $(INSTALL_DATA) $$f $(DESTDIR)$(infodir)/`basename $$f`; \
	    done; \
	  fi; \
	  if test -f $(DESTDIR)$(infodir)/dir; then \
	    if grep "^\* Octave: (octave)." $(DESTDIR)$(infodir)/dir > /dev/null; then \
	      true; \
	    else \
	      echo ""; \
	      echo "You should add the following entry"; \
	      echo ""; \
	      echo "* Octave: (octave)."; \
	      echo "	Interactive language for numerical computations."; \
	      echo ""; \
	      echo "to $(DESTDIR)$(infodir)/dir."; \
	      echo ""; \
	    fi; \
	  else \
	    echo "installing $(srcdir)/dir in $(DESTDIR)$(infodir)"; \
	    $(INSTALL_DATA) $(srcdir)/dir $(DESTDIR)$(infodir)/dir; \
	  fi; \
	fi
.PHONY: install install-strip

uninstall:
	rm -f $(infodir)/octave.info*
	for f in $(MAN_BASE); do rm -f $(DESTDIR)$(man1dir)/$$f$(man1ext); done
.PHONY: uninstall

tags: $(SOURCES)
	ctags $(SOURCES)

TAGS: $(SOURCES)
	etags $(SOURCES)

spell: $(SPELL)
.PHONY: spell

mostlyclean clean:
	rm -f octave.cp octave.fn octave.in \
	octave.ky octave.op octave.pg octave.rd octave.tp octave.vr \
	octave.cps octave.fns octave.ins octave.kys octave.ops \
	octave.pgs octave.rds octave.tps octave.vrs octave.aux \
	octave.log octave.toc \
	munge-texi$(BUILD_EXEEXT) munge-texi.o
.PHONY: mostlyclean clean

distclean: clean
	rm -f Makefile 
.PHONY: distclean

maintainer-clean: distclean clean-texi
	rm -f tags TAGS $(FORMATTED)
.PHONY: maintainer-clean

clean-texi:
	rm -f $(SUB_TEXINFO)
.PHONY: clean-texi

dist: clean-texi all
	ln $(DISTFILES) ../../`cat ../../.fname`/doc/interpreter
.PHONY: dist

bin-dist:
	if [ -n "$(BINDISTFILES)" ]; then \
	  ln $(BINDISTFILES) ../../`cat ../../.fname`/doc/interpreter; \
	fi
.PHONY: bin-dist
