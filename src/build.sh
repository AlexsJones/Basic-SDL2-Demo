##	Plane of Craftiness
##
##	NOTE: This file may eventually be depreciated.
##		This script is slower than running 'make' because it re-builds the entire project.
##		The Makefile fails to set the DATE, but isn't necessarily needed.

#!/bin/sh

DATE=$(date +%Y%m%d)

Help ()
{	
	echo "Usage: $0 [Options]"
	echo "The Options are:"
	echo "	static 	--Output a static executable"
	echo "	no-cleanup	--Don't remove the object files '.o'"
	echo "	help 		--Show this help message"
	echo "Note that this script requires a Makefile and 'make' to be installed."
	echo "Copyright 2012 by Dan Hatch <danhatch333@gmail.com>"
	exit 1
}	

BUILD_STATIC=0
NO_CLEANUP=0

ARGS=$#
SHIFT_COUNT=0
if test $ARGS -gt 0
then
while (test $SHIFT_COUNT -le $ARGS)
do
	case  $1  in
			"static")		BUILD_STATIC=1;;
			"no-cleanup")	NO_CLEANUP=1;;
			"help")			Help;;
	esac
	shift
	SHIFT_COUNT=`expr $SHIFT_COUNT + 1`
done
fi

Build ()
{
if test $BUILD_STATIC -eq 0
	then
	echo "--> Generating Executable File"
	g++ -Wl,-rpath,\$ORIGIN/lib/ -std=c++0x -static-libgcc -g	\
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
else
	ls lib/libSDL2*.a							##	Check for library archives 
	if test $? -eq 0							##	If the command didn't produce any errors
		then									##	Then build the executable
		echo "--> Generating Static Executable"
		g++ engine/*.o engine/component/*.o							\
		-Llib -Wl,-Bstatic lib/libSDL2.a lib/libSDL2_image.a		\
		lib/libSDL2main.a -lsmpeg -lmikmod -lvorbisfile -lvorbis	\
		-logg -lXxf86dga -lXxf86vm -lXv -lXinerama -lXi -lpng -lz	\
		-lstdc++ -Wl,-Bdynamic -lpthread -lGL -lX11 -lXext -ldl		\
		-lgcc -lGL -lGLU -lpthread -lGLEW							\
		-o ../"poc_static-"$DATE
	else echo "Please copy all the '.a' files from the 'lib' directory of SDL2 to the 'lib' directory in this folder."
	fi
fi
}

##	These statements should be switched a little if we completely switch to make.
if test $BUILD_STATIC -eq 0
	then Build
elif test $BUILD_STATIC -eq 1
	 then
	 echo "--> Building Plane of Craftiness"
##	Static needs to compile object files first, with the way the functions are setup.
	 make
	 Build
	 if test $NO_CLEANUP -eq 0
		 then
		 echo "--> Cleaning up...."
		 make clean > /dev/null
	 fi 
fi
