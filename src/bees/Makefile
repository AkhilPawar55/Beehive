#
# Created by gmakemake (Ubuntu Jul 25 2014) on Sun Apr  1 19:16:58 2018
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

CXXFLAGS = -g -gdwarf-2 -Wall -Wextra -Weffc++ -pedantic -std=c++17 

########## End of flags from header.mak


CPP_FILES =	bee.cpp drone.cpp queen.cpp resource.cpp worker.cpp
C_FILES =	
PS_FILES =	
S_FILES =	
H_FILES =	bee.h drone.h queen.h resource.h worker.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	bee.o drone.o queen.o resource.o worker.o 

#
# Main targets
#

all:	 $(OBJFILES)

#
# Dependencies
#

bee.o:	../bees/bee.h ../bees/resource.h ../util/logger.h ../util/my_thread.h ../util/random.h ../world/beehive.h ../world/flower_field.h ../world/queens_chamber.h bee.h drone.h queen.h resource.h worker.h
drone.o:	../bees/bee.h ../bees/resource.h ../util/logger.h ../util/my_thread.h ../util/random.h ../world/beehive.h ../world/queens_chamber.h bee.h drone.h resource.h
queen.o:	../bees/bee.h ../bees/resource.h ../util/logger.h ../util/my_thread.h ../util/random.h ../world/beehive.h ../world/flower_field.h bee.h queen.h ../world/queens_chamber.h resource.h
resource.o:	resource.h
worker.o:	../bees/bee.h ../bees/resource.h ../util/logger.h ../util/my_thread.h ../util/random.h ../world/beehive.h ../world/flower_field.h bee.h resource.h worker.h

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
