## Process this file with automake to produce Makefile.in

INCLUDES = \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	@PACKAGE_CFLAGS@

bin_PROGRAMS = projetfinal

projetfinal_SOURCES = \
	main.c \
	support.c support.h \
	interface.c interface.h \
	callbacks.c callbacks.h \
	ajoutavis.c ajoutavis.h \
	compte.c compte.h \
	parking.c parking.h \
	reservation.c reservation.h

projetfinal_LDADD = @PACKAGE_LIBS@ $(INTLLIBS)

