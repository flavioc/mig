## Process this file with automake to produce Makefile.in.

libexec_PROGRAMS = migcom
bin_SCRIPTS = mig

EXTRA_DIST = gensym.awk cpu.sym

CLEANFILES = cpu.h *.sym[co]

AWK_V = $(AWK_V_$(V))
AWK_V_ = $(AWK_V_$(AM_DEFAULT_VERBOSITY))
AWK_V_0 = @echo "  AWK    $@";

migcom_SOURCES = boolean.h error.c error.h global.c global.h		\
		 header.c lexxer.h lexxer.l message.h mig_string.h	\
		 migcom.c parser.h parser.y routine.c routine.h		\
		 server.c statement.c statement.h string.c		\
		 type.c type.h user.c utils.c utils.h vprint.c write.h
migcom_LDADD = @ALLOCA@ @LEXLIB@

SUFFIXES = .h .symo .symc .sym

.sym.symc:
	$(AWK_V) $(AWK) -f $(srcdir)/gensym.awk $< > $@
.symc.symo:
	$(AM_V_CC) $(TARGET_CC) -S $(TARGET_CPPFLAGS) $(TARGET_CFLAGS) -x c -o $@ $<
.symo.h:
	$(AM_V_GEN) sed -e '/^[^*].*$$/d' -e 's/^[*]/#define/' -e 's/mAgIc[^-0-9]*//' \
	    $< > $@
cpu.symc: $(srcdir)/gensym.awk

$(migcom_OBJECTS): cpu.h
