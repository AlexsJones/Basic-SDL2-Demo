##	Plane of Craftiness
##
##NOTE: This file may eventually be depreciated.
##		This script is slower than running 'make' because it re-builds the entire project.
##		The Makefile fails to set the DATE, but isn't necessarily needed.

#!/bin/sh
DATE=$(date +%Y%m%d)
g++ -Wl,-rpath,\$ORIGIN/lib/ -std=c++0x -static-libgcc 		\
	engine/main.cpp 		\
	engine/engine.cpp 		\
	engine/window.cpp 		\
	engine/character.cpp	\
	engine/player.cpp 		\
	engine/animation.cpp	\
	engine/component/input.cpp	\
	engine/component/animation.cpp	\
	engine/component/physics.cpp	\
-DDATE='"'$DATE'"' -o ../poc -Iinclude -Iengine -L../lib -lSDL2 -lSDL2_image
