##  Makefile to build on *nix systems.
##
##
DATE=$(shell date +%Y%m%d)

PREFIX=../

BIN=$(PREFIX)/sdl2-demo

CC=g++
CFLAGS= -g -c -std=c++0x -Wall -pedantic
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


all: $(BIN)

##  Link Objects
## $@  -  points to the rule: $(BIN)  - which expands to "../sdl2-demo"
## $^  -  points to the dependencies: $(OBJECTS)
$(BIN): $(OBJECTS)
	$(CC) $(LINKERFLAGS) $^ -o $@ $(LIBS)

##  Compile Objects
## This rule creates the $(OBJECTS)
.cpp.o:
	$(CC) $(CFLAGS) $(DEFINES) $< -o $@ $(INCLUDES)

clean:
	rm $(OBJECTS)


.PHONY : all
.PHONY : clean


