#
# Created by gmakemake (Ubuntu Jul 25 2014) on Sun Apr  1 19:16:51 2018
#

#
# Definitions
#

.SUFFIXES:
.SUFFIXES:	.a .o .c .C .cpp .s .S
.c.o:
		$(COMPILE.c) $<
.C.o:
		$(COMPILE.cc) $<
.cpp.o:
		$(COMPILE.cc) $<
.S.s:
		$(CPP) -o $*.s $<
.s.o:
		$(COMPILE.cc) $<
.c.a:
		$(COMPILE.c) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.C.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.cpp.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%

CC =		gcc
CXX =		g++

RM = rm -f
AR = ar
LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c
CPP = $(CPP) $(CPPFLAGS)
########## Flags from header.mak

CXXFLAGS = -g -gdwarf-2 -Wall -Wextra -Weffc++ -pedantic -std=c++17 -lpthread

########## End of flags from header.mak


CPP_FILES =	beehive.cpp flower_field.cpp queens_chamber.cpp
C_FILES =	
PS_FILES =	
S_FILES =	
H_FILES =	beehive.h flower_field.h queens_chamber.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	beehive.o flower_field.o queens_chamber.o 

#
# Main targets
#

all:	$(OBJFILES)

#
# Dependencies
#

beehive.o:	../bees/bee.h ../bees/resource.h ../util/logger.h ../util/my_thread.h ../util/random.h beehive.h flower_field.h queens_chamber.h 
flower_field.o:	../bees/bee.h ../bees/resource.h ../bees/worker.h ../util/logger.h ../util/my_thread.h ../util/random.h ../world/beehive.h ../world/flower_field.h flower_field.h queens_chamber.h
queens_chamber.o:	../bees/bee.h ../bees/drone.h ../bees/resource.h ../util/logger.h ../util/my_thread.h ../util/random.h ../world/beehive.h ../world/queens_chamber.h flower_field.h queens_chamber.h 

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm -f $(OBJFILES) core

realclean:        clean
	-/bin/rm -f 
