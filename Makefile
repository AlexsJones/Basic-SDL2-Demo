##  Makefile to build on *nix systems.
DATE=$(shell date +%Y%m%d)

BIN=sdl2-demo
SRCDIR=src
INCLUDEDIR=include
BUILDDIR=build

CXX=g++
CXXFLAGS= -g -c -std=c++0x -Wall -pedantic
LINKERFLAGS=-Wl,-rpath,\$$ORIGIN/lib/ -static-libgcc
DEFINES= -DDATE='"'$$DATE'"'
INCLUDES= -Iinclude -I$(INCLUDEDIR)
LIBS= -Llib  -lSDL2 -lSDL2_image

SOURCES= $(shell find $(SRCDIR) -type f -name "*.cpp")
OBJECTS	:= $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))
#OBJECTS=$(SOURCES:.cpp=.o)

all: init $(BIN)

init:
	@mkdir -p $(BUILDDIR)
	@for SOURCE in $(SOURCES); do \
		export SRCSUBDIR=`find $$SOURCE -printf '%h\n'`; \
		SRCSUBDIR=`echo $$SRCSUBDIR | sed -e s@$(SRCDIR)/@@`; \
		mkdir -p $(BUILDDIR)/$$SRCSUBDIR; \
	done

##  Link Objects
## $@  -  points to the rule: $(BIN)  - which expands to "../sdl2-demo"
## $^  -  points to the dependencies: $(OBJECTS)
$(BIN): $(OBJECTS)
	$(CXX) $(LINKERFLAGS) $^ -o $@ $(LIBS)

##  Compile Objects
## This rule creates the $(OBJECTS)
$(OBJECTS): $(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(DEFINES) $< -o $@ $(INCLUDES)

docs:
	(cat Doxyfile ; echo INPUT="$1") | doxygen -

clean:
	@rm -rd $(BUILDDIR)


.PHONY : all
.PHONY : clean


