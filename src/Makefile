##	Plane of Craftiness
##
##  Makefile to build on *nix systems.
##
##
##  'make install' shouldn't build the project. It should only install a built
##	project. It will be disabled for now.
##
##  date doesn't work yet..
DATE=$(date +%Y%m%d)

PREFIX=../
INSTALL_PREFIX=/opt/PlaneOfCraftiness/

DATADIR=$(PREFIX)/data
BINDIR=$(PREFIX)
LIBDIR=$(PREFIX)/lib
BIN=$(PREFIX)/poc	##$(DATE)

CC=g++
CFLAGS= -c -std=c++0x -Wall -pedantic
LINKERFLAGS=-Wl,-rpath,\$$ORIGIN/lib/ -static-libgcc
DEFINES= -DDATE='"'$$DATE'"'
INCLUDES= -Iinclude -Iengine
LIBS= -L$(PREFIX)/lib  -lSDL2 -lSDL2_image
SOURCEDIR=.
SOURCES= 					\
	engine/main.cpp 		\
	engine/engine.cpp 		\
	engine/window.cpp 		\
	engine/character.cpp	\
	engine/player.cpp 		\
	engine/animation.cpp	\
	engine/component/input.cpp	\
	engine/component/animation.cpp	\
	engine/component/physics.cpp

OBJECTS=$(SOURCES:.cpp=.o) ##$(INCLUDES)

INSTALL=install
#INSTALL_PREFIX=/opt/PlaneOfCraftiness/
INSTALL_BINDIR=$(INSTALL_PREFIX)/
INSTALL_DATADIR=$(INSTALL_PREFIX)/data
INSTALL_LIBDIR=$(INSTALL_PREFIX)/data
##.PHONY=clean install dist

all: $(BIN)

##  This is a TEST
PROJECT_DIRS=				\
			$(PREFIX)/		\
			$(PREFIX)/data	\
			$(PREFIX)/lib
##  INSTALL_DIRS will be PROJECT_DIRS with the INSTALL_PREFIX instead
INSTALL_DIRS=$(PROJECT_DIRS:$(PREFIX)=$(INSTALL_PREFIX))

install: $(INSTALL_DIRS)
	
$(PREFIX)$(INSTALL_PREFIX):
	echo $@
	echo $<
	$(INSTALL) -d $@
	$(INSTALL) $< $@
##  END of TEST

#install: $(BIN)
#	$(INSTALL) -d $(INSTALL_BINDIR)
#	$(INSTALL) $(BIN) $(INSTALL_BINDIR)
#	$(INSTALL) -d $(INSTALL_DATADIR)
#	$(INSTALL) $(DATADIR) $(INSTALL_DATADIR)

##  Link Objects
$(BIN): $(OBJECTS)
	$(CC) $(LINKERFLAGS) $^ -o $@ $(LIBS)

##  Compile Objects
.cpp.o:
	$(CC) $(CFLAGS) $(DEFINES) $< -o $@ $(INCLUDES)

clean:
	rm $(OBJECTS)
