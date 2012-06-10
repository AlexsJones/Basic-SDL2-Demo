## Makefile to build Plane of Craftiness on *nix systems.
##date doesn't work yet..
DATE= $(date +%Y%m%d)

CC=g++
BIN=../poc	##$(DATE)
CFLAGS= -c -std=c++0x -Wall -pedantic
LINKERFLAGS=-Wl,-rpath,\$$ORIGIN/lib/ -static-libgcc
DEFINES= -DDATE='"'$$DATE'"'
INCLUDES= -Iinclude -Iengine
LIBS= -L../lib  -lSDL2 -lSDL2_image
SOURCEDIR=$PWD
SOURCES= 		\
	engine/main.cpp 	\
	engine/engine.cpp 	\
	engine/character.cpp	\
	engine/player.cpp 	\
	engine/animation.cpp	\
	engine/component.cpp	\

OBJECTS=$(SOURCES:.cpp=.o) ##$(INCLUDES)
##INSTALL=install
##PREFIX=$PWD/../
##BINDIR=$(PREFIX)/bin
##DATADIR=$(PREFIX)/data
.PHONY=clean install dist

all: $(BIN)

##install: $(BIN)
##	$(INSTALL) -d $(BINDIR)
##	$(INSTALL) $(BIN) $(BINDIR)/$(BIN)
##	$(INSTALL) -d $(DATADIR)

clean:
	rm $(OBJECTS)

$(BIN): $(OBJECTS)
	$(CC) $(LINKERFLAGS) $^ -o $@ $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $(DEFINES) $< -o $@ $(INCLUDES)

