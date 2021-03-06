#
# Makefile for octave's liboctave directory
#
# John W. Eaton
# jwe@bevo.che.wisc.edu
# University of Wisconsin-Madison
# Department of Chemical Engineering

TOPDIR = ..

srcdir = .
top_srcdir = ..


include $(TOPDIR)/Makeconf

INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL}
INSTALL_DATA = ${INSTALL} -m 644

LINK_DEPS = \
  -L../libcruft -L../glob -L. $(RLD_FLAG) \
  $(LIBCRUFT) $(BLAS_LIBS) $(FFTW_LIBS) $(LIBREADLINE) -lglob $(LIBS) $(FLIBS)

MATRIX_INC := Array.h Array2.h Array3.h ArrayN.h DiagArray2.h \
	Array-flags.h Array-util.h ArrayN-idx.h MArray-defs.h \
	MArray.h MArray2.h MDiagArray2.h Matrix.h MArrayN.h \
	base-lu.h dim-vector.h mx-base.h mx-op-defs.h mx-ops.h \
	mx-defs.h mx-ext.h CColVector.h CDiagMatrix.h CMatrix.h \
	CNDArray.h CRowVector.h CmplxAEPBAL.h CmplxCHOL.h \
	CmplxDET.h CmplxHESS.h CmplxLU.h CmplxQR.h CmplxQRP.h \
	CmplxSCHUR.h CmplxSVD.h EIG.h boolMatrix.h boolNDArray.h \
	chMatrix.h chNDArray.h dColVector.h dDiagMatrix.h dMatrix.h \
	dNDArray.h dRowVector.h dbleAEPBAL.h dbleCHOL.h dbleDET.h \
	dbleHESS.h dbleLU.h dbleQR.h dbleQRP.h dbleSCHUR.h dbleSVD.h

MX_OP_INC := $(shell $(AWK) -f $(srcdir)/mk-ops.awk prefix=mx list_h_files=1 $(srcdir)/mx-ops)

VX_OP_INC := $(shell $(AWK) -f $(srcdir)/mk-ops.awk prefix=vx list_h_files=1 $(srcdir)/vx-ops)

OPTS_INC_DATA := DASPK-opts.in DASRT-opts.in DASSL-opts.in \
	LSODE-opts.in NLEqn-opts.in ODESSA-opts.in Quad-opts.in

OPTS_INC := $(OPTS_INC_DATA:.in=.h)

INCLUDES := Bounds.h CollocWt.h DAE.h DAEFunc.h DAERT.h \
	DAERTFunc.h DASPK.h DASRT.h DASSL.h FEGrid.h \
	LinConst.h LP.h LPsolve.h LSODE.h NLConst.h NLEqn.h \
	NLFunc.h NLP.h ODE.h ODEFunc.h ODES.h ODESFunc.h \
	ODESSA.h Objective.h QP.h Quad.h Range.h base-dae.h \
	base-de.h base-min.h byte-swap.h cmd-edit.h cmd-hist.h \
	data-conv.h dir-ops.h file-ops.h file-stat.h getopt.h \
	glob-match.h idx-vector.h kpse-xfns.h \
	lo-ieee.h lo-mappers.h lo-specfun.h lo-sstream.h \
	lo-sysdep.h lo-utils.h mach-info.h oct-alloc.h oct-cmplx.h \
	oct-env.h oct-fftw.h oct-getopt.h oct-group.h oct-passwd.h \
	oct-rand.h oct-rl-edit.h oct-rl-hist.h oct-shlib.h \
	oct-syscalls.h oct-time.h pathlen.h pathsearch.h \
	prog-args.h so-array.h statdefs.h str-vec.h sun-utils.h sysdir.h \
	systime.h syswait.h \
	$(OPTS_INC) \
	$(MATRIX_INC) \
	$(MX_OP_INC) \
	$(VX_OP_INC)

TEMPLATE_SRC := Array.cc ArrayN.cc DiagArray2.cc \
	MArray.cc MArray2.cc MArrayN.cc MDiagArray2.cc base-lu.cc

TI_SRC := Array-C.cc Array-b.cc Array-ch.cc Array-i.cc Array-d.cc \
	Array-s.cc Array-so.cc Array-str.cc Array-idx-vec.cc \
	MArray-C.cc MArray-ch.cc MArray-i.cc MArray-d.cc MArray-s.cc

MATRIX_SRC := Array-flags.cc Array-util.cc CColVector.cc \
	CDiagMatrix.cc CMatrix.cc CNDArray.cc CRowVector.cc \
	CmplxAEPBAL.cc CmplxCHOL.cc CmplxDET.cc CmplxHESS.cc \
	CmplxLU.cc CmplxQR.cc CmplxQRP.cc CmplxSCHUR.cc CmplxSVD.cc \
	EIG.cc boolMatrix.cc boolNDArray.cc chMatrix.cc \
	chNDArray.cc dColVector.cc  dDiagMatrix.cc dMatrix.cc \
	dNDArray.cc dRowVector.cc dbleAEPBAL.cc dbleCHOL.cc \
	dbleDET.cc dbleHESS.cc dbleLU.cc dbleQR.cc dbleQRP.cc \
	dbleSCHUR.cc dbleSVD.cc

MX_OP_SRC := $(shell $(AWK) -f $(srcdir)/mk-ops.awk prefix=mx list_cc_files=1 $(srcdir)/mx-ops)

VX_OP_SRC := $(shell $(AWK) -f $(srcdir)/mk-ops.awk prefix=vx list_cc_files=1 $(srcdir)/vx-ops)

LIBOCTAVE_CXX_SOURCES := Bounds.cc CollocWt.cc \
	DASPK.cc DASRT.cc DASSL.cc FEGrid.cc LinConst.cc \
	LPsolve.cc LSODE.cc NLEqn.cc ODES.cc ODESSA.cc \
	Quad.cc Range.cc data-conv.cc dir-ops.cc \
	file-ops.cc file-stat.cc glob-match.cc idx-vector.cc \
	lo-ieee.cc lo-mappers.cc lo-specfun.cc lo-sysdep.cc \
	lo-utils.cc mach-info.cc oct-alloc.cc oct-env.cc \
	oct-fftw.cc oct-group.cc oct-passwd.cc oct-rand.cc oct-shlib.cc \
	oct-syscalls.cc oct-time.cc prog-args.cc so-array.cc str-vec.cc \
	$(TEMPLATE_SRC) \
	$(TI_SRC) \
	$(MATRIX_SRC) \
	$(MX_OP_SRC) \
	$(VX_OP_SRC)

LIBOCTAVE_C_SOURCES := f2c-main.c filemode.c getopt.c getopt1.c \
	lo-cieee.c lo-cutils.c mkdir.c oct-getopt.c rename.c \
	rmdir.c strftime.c strptime.c tempname.c tempnam.c

LIBOCTAVE_SOURCES := $(LIBOCTAVE_CXX_SOURCES) $(LIBOCTAVE_C_SOURCES)

LIBOCT_READLINE_CXX_SOURCES := cmd-edit.cc cmd-hist.cc

LIBOCT_READLINE_C_SOURCES := oct-rl-edit.c oct-rl-hist.c

LIBOCT_READLINE_SOURCES := $(LIBOCT_READLINE_CXX_SOURCES) $(LIBOCT_READLINE_C_SOURCES)

LIBOCT_PATHSEARCH_CXX_SOURCES := pathsearch.cc

LIBOCT_PATHSEARCH_C_SOURCES := kpse-xfns.c

LIBOCT_PATHSEARCH_SOURCES := \
	$(LIBOCT_PATHSEARCH_C_SOURCES) $(LIBOCT_PATHSEARCH_CXX_SOURCES)

SOURCES := \
	$(LIBOCTAVE_SOURCES) \
	$(LIBOCT_READLINE_SOURCES) \
	$(LIBOCT_PATHSEARCH_SOURCES)

EXTRAS := mx-inlines.cc kpse.cc

INCLUDES_FOR_INSTALL := $(INCLUDES) $(TEMPLATE_SRC) $(EXTRAS)

DISTFILES := Makefile.in ChangeLog mk-ops.awk mx-ops vx-ops \
	$(SOURCES) $(INCLUDES) $(EXTRAS) $(OPTS_INC_DATA)

ifeq ($(SHARED_LIBS), true)
  BINDISTLIBS = liboctave/liboctave
  BINDISTFILES = liboctave.$(SHLEXT_VER)
endif

MAKEDEPS_1 := $(patsubst %.cc, %.d, $(SOURCES))
MAKEDEPS := $(patsubst %.c, %.d, $(MAKEDEPS_1))

LIBOCTAVE_OBJECTS := \
	$(LIBOCTAVE_CXX_SOURCES:.cc=.o) \
	$(LIBOCTAVE_C_SOURCES:.c=.o) \
	$(LIBOCT_READLINE_CXX_SOURCES:.cc=.o) \
	$(LIBOCT_READLINE_C_SOURCES:.c=.o) \
	$(LIBOCT_PATHSEARCH_CXX_SOURCES:.cc=.o) \
	$(LIBOCT_PATHSEARCH_C_SOURCES:.c=.o)

ifeq ($(SHARED_LIBS), true)
  ifdef CXXPICFLAG
    LIBOCTAVE_PICOBJ := $(addprefix pic/, $(LIBOCTAVE_OBJECTS))
  else
    LIBOCTAVE_PICOBJ := $(LIBOCTAVE_OBJECTS)
  endif
endif

all: libraries
.PHONY: all

objects: $(OBJECTS)

stmp-pic: pic
	@if [ -f stmp-pic ]; then \
	  true; \
	else \
	  echo "touch stmp-pic"; \
	  touch stmp-pic; \
	fi

pic:
	@if [ -d pic ]; then \
	  true; \
	else \
	  echo "mkdir pic"; \
	  mkdir pic; \
	fi

stamp-prereq: $(OPTS_INC) $(VX_OP_INC) $(VX_OP_SRC) $(MX_OP_INC) $(MX_OP_SRC) mx-ops.h
	touch stamp-prereq

ifeq ($(SHARED_LIBS), true)
  ifeq ($(STATIC_LIBS), true)
    libraries: \
	stamp-prereq \
	liboctave.$(LIBEXT) liboctave.$(SHLEXT_VER)
  else
    libraries: \
	stamp-prereq \
	liboctave.$(SHLEXT_VER)
  endif
else
  ifeq ($(STATIC_LIBS), true)
    libraries: \
	stamp-prereq \
	liboctave.$(LIBEXT)
  else
    libraries: stamp-prereq
  endif
endif
.PHONY: libraries

liboctave.$(LIBEXT): $(LIBOCTAVE_OBJECTS)
	rm -f $@
	$(TEMPLATE_AR) $(TEMPLATE_ARFLAGS) $@ $(LIBOCTAVE_OBJECTS)
	$(RANLIB) $@

liboctave.$(SHLEXT_VER): liboctave.$(SHLEXT)
	rm -f $@
	$(LN_S) $< $@

liboctave.$(SHLEXT): $(LIBOCTAVE_PICOBJ)
	rm -f $@
	$(SH_LD) $(SH_LDFLAGS) $(SONAME_FLAGS) -o $@ \
	$(LIBOCTAVE_PICOBJ) $(LINK_DEPS)

$(LIBOCTAVE_PICOBJ): stmp-pic

check: all
.PHONY: check

install: install-lib install-inc
.PHONY: install

install-strip:
	$(MAKE) INSTALL_PROGRAM="$(INSTALL_PROGRAM) -s" install
.PHONY: install-strip

install-lib:
	$(top_srcdir)/mkinstalldirs $(DESTDIR)$(octlibdir)
	if $(STATIC_LIBS); then \
	  rm -f $(DESTDIR)$(octlibdir)/liboctave.$(LIBEXT); \
	  $(INSTALL_DATA) liboctave.$(LIBEXT) \
	    $(DESTDIR)$(octlibdir)/liboctave.$(LIBEXT); \
	  $(RANLIB) $(DESTDIR)$(octlibdir)/liboctave.$(LIBEXT); \
	fi
	if $(SHARED_LIBS); then \
	  rm -f $(DESTDIR)$(octlibdir)/liboctave.$(SHLLIB_VER); \
	  $(INSTALL) \
	    liboctave.$(SHLLIB) $(DESTDIR)$(octlibdir)/liboctave.$(SHLLIB_VER); \
	  rm -f $(DESTDIR)$(octlibdir)/liboctave.$(SHLLIB); \
	  $(LN_S) liboctave.$(SHLLIB_VER) $(DESTDIR)$(octlibdir)/liboctave.$(SHLLIB); \
	  if  test x$(SHLBIN) != x ; then \
	    rm -f $(DESTDIR)$(bindir)/liboctave.$(SHLBIN); \
	    $(INSTALL_PROGRAM) \
	      liboctave.$(SHLBIN) $(DESTDIR)$(bindir)/liboctave.$(SHLBIN); \
	  fi; \
	fi
.PHONY: install-lib

install-inc:
	$(top_srcdir)/mkinstalldirs $(DESTDIR)$(octincludedir)/octave
	for f in $(INCLUDES_FOR_INSTALL); do \
	  rm -f $(DESTDIR)$(octincludedir)/octave/$$f; \
	  if [ -f $$f ]; then \
	    $(INSTALL_DATA) $$f $(DESTDIR)$(octincludedir)/octave/$$f; \
	  else \
	    $(INSTALL_DATA) $(srcdir)/$$f $(DESTDIR)$(octincludedir)/octave/$$f; \
	  fi ; \
	done
.PHONY: install-inc

uninstall:
	rm -f $(DESTDIR)$(octlibdir)/liboctave.$(LIBEXT)
	rm -f $(DESTDIR)$(octlibdir)/liboctave.$(SHLLIB)
	rm -f $(DESTDIR)$(octlibdir)/liboctave.$(SHLLIB_VER)
	if test x$(SHLBIN) != x; then \
	  rm -f $(DESTDIR)$(bindir)/liboctave.$(SHLBIN); \
	  rm -f $(DESTDIR)$(bindir)/liboctave.$(SHLBIN_VER); \
	fi
	for f in $(INCLUDES); do rm -f $(DESTDIR)$(octincludedir)/octave/$$f; done
.PHONY: uninstall

tags: $(SOURCES)
	ctags $(SOURCES)

TAGS: $(SOURCES)
	etags $(SOURCES)

clean:
	rm -f *.$(LIBEXT) *.o *.d pic/*.o
	-rmdir pic
	rm -f stmp-pic
	if $(SHARED_LIBS); then rm -f *.$(SHLEXT_VER) *.$(SHLEXT); fi
.PHONY: clean

mostlyclean: clean
.PHONY: mostlyclean

distclean: clean
	rm -f Makefile so_locations stamp-prereq $(OPTS_INC)
	rm -f mx-ops.h $(MX_OP_INC) $(VX_OP_INC) $(MX_OP_SRC) $(VX_OP_SRC)
.PHONY: distclean

maintainer-clean: distclean
	rm -f tags TAGS
.PHONY: maintainer-clean

dist: stamp-prereq
	ln $(DISTFILES) ../`cat ../.fname`/liboctave
.PHONY: dist

bin-dist:
	if [ -n "$(BINDISTFILES)" ]; then \
	  ln $(BINDISTFILES) ../`cat ../.fname`/liboctave; \
	fi
	if [ -n "$(BINDISTLIBS)" ]; then \
	  echo $(BINDISTLIBS) >> ../`cat ../.fname`/LIBRARIES; \
	fi
.PHONY: bin-dist

$(OPTS_INC) : %.h : %.in $(top_srcdir)/mk-opts.pl
	@echo making $@ from $<
	@perl $(top_srcdir)/mk-opts.pl --opt-class-header $< > $@-t
	@$(top_srcdir)/move-if-change $@-t $@

$(VX_OP_INC) $(VX_OP_SRC) : $(srcdir)/mk-ops.awk vx-ops
	$(AWK) -f $(srcdir)/mk-ops.awk prefix=vx $(srcdir)/vx-ops

$(MX_OP_INC) $(MX_OP_SRC) : $(srcdir)/mk-ops.awk mx-ops
	$(AWK) -f $(srcdir)/mk-ops.awk prefix=mx $(srcdir)/mx-ops

mx-ops.h : $(srcdir)/mk-ops.awk mx-ops
	$(AWK) -f $(srcdir)/mk-ops.awk prefix=mx make_inclusive_header=mx-ops.h $(srcdir)/mx-ops > $@-t
	$(top_srcdir)/move-if-change $@-t $@


# If missing, GNU make attempts to create them in the reverse of the
# order in which they are listed here.  We rely on that fact to ensure
# that defaults.h is created before trying to create the .d files.
# Hmm.  I wonder if we can count on that...

ifndef omit_deps
-include $(MAKEDEPS) stamp-prereq
endif
