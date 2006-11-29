## Process this file with automake to produce Makefile.in.

AUTOMAKE_OPTIONS = gnu
libexec_PROGRAMS = migcom
bin_SCRIPTS = mig

TARGET_CPPFLAGS = @TARGET_CPPFLAGS@
TARGET_CFLAGS = @TARGET_CFLAGS@

EXTRA_DIST = gensym.awk cpu.sym

CLEANFILES = cpu.h *.sym[co]

migcom_SOURCES = alloc.h boolean.h error.c error.h global.c global.h	\
		 header.c lexxer.h lexxer.l message.h mig_string.h	\
		 migcom.c parser.h parser.y routine.c routine.h		\
		 server.c statement.c statement.h string.c		\
		 type.c type.h user.c utils.c utils.h vprint.c write.h
migcom_LDADD = @ALLOCA@ @LEXLIB@

SUFFIXES = .h .symo .symc .sym

.sym.symc:
	$(AWK) -f $(srcdir)/gensym.awk $< > $@
.symc.symo:
	$(TARGET_CC) -S $(TARGET_CPPFLAGS) $(TARGET_CFLAGS) -x c -o $@ $<
.symo.h:
	sed -e '/^[^*].*$$/d' -e 's/^[*]/#define/' -e 's/mAgIc[^-0-9]*//' \
	    $< > $@
cpu.symc: $(srcdir)/gensym.awk

$(migcom_OBJECTS): cpu.h
