#
# Top level Unix style makefile
#
# @author Sean Strout @ RIT CS
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

CXXFLAGS = -g -gdwarf-2 -Wall -Wextra -Weffc++ -pedantic -std=c++17 -pthread -fsanitize=thread -O2

########## End of flags from header.mak

BEES_OBJFILES = bees/bee.o bees/drone.o bees/queen.o bees/resource.o bees/worker.o
UTIL_OBJFILES = util/logger.o util/my_thread.o util/random.o
WORLD_OBJFILES = world/beehive.o world/flower_field.o world/queens_chamber.o
OBJFILES = $(BEES_OBJFILES) $(UTIL_OBJFILES) $(WORLD_OBJFILES)

#
# Main targets
#

.PHONY: all
all: bee_main


parts:
	+$(MAKE) -C bees
	+$(MAKE) -C util
	+$(MAKE) -C world

bee_main: parts $(OBJFILES) bee_main.o
	$(CXX) $(CXXFLAGS) -o bee_main $(OBJFILES) bee_main.o $(CCLIBFLAGS)

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

.PHONY: clean
clean:
	+$(MAKE) -C bees clean
	+$(MAKE) -C util clean
	+$(MAKE) -C world clean
	-/bin/rm -f bee_main.o

.PHONY: realclean
realclean:        clean
	-/bin/rm -f  bee_main

