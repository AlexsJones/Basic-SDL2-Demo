#!/bin/sh

DATE=$(date +%Y%m%d)

Help ()
{	
	echo "Usage: $0 [Options]"
	echo "The Options are:"
	echo "	static 	--Output a static executable"
	echo "	help 		--Show this help message"
	echo "Note that this script requires a Makefile and 'make' to be installed."
	exit 1
}	

BUILD_STATIC=0

ARGS=$#
SHIFT_COUNT=0
if test $ARGS -gt 0
then
while (test $SHIFT_COUNT -le $ARGS)
do
	case  $1  in
			"static")		BUILD_STATIC=1;;
			"help")			Help;;
	esac
	shift ${SHIFT_COUNT}
	SHIFT_COUNT=`expr $SHIFT_COUNT + 1`
done
fi


Build ()
{
if test $BUILD_STATIC -eq 0
	then
	echo "--> Generating Executable File"
	g++ -Wl,-rpath,\$ORIGIN/lib/ -std=c++0x -static-libgcc -g	\
		src/engine/main.cpp 		\
		src/engine/engine.cpp 		\
		src/engine/window.cpp 		\
		src/engine/character.cpp	\
		src/engine/player.cpp 		\
		src/engine/animation.cpp	\
		src/engine/component/input.cpp	\
		src/engine/component/animation.cpp	\
		src/engine/component/physics.cpp	\
	-DDATE='"'$DATE'"' -o sdl2-demo -Iinclude -Iengine -L../lib -lSDL2 -lSDL2_image -Isrc/engine -Isrc/engine/component
else
	ls lib/libSDL2*.a							##	Check for library archives 
	if test $? -eq 0							##	If the command didn't produce any errors
		then									##	Then build the executable
		echo "--> Generating Static Executable"
		g++ engine/*.o engine/component/*.o					\
		-Llib -Wl,-Bstatic									\
		lib/libSDL2.a lib/libSDL2_image.a lib/libSDL2main.a	\
		-lstdc++ -Wl,-Bdynamic -lpthread -lGL -lX11 -lXext -ldl	-lgcc 	\
		`sdl2-config --cflags --static-libs`							\
		-o "sdl2-demo_"$DATE
	else echo "Please copy all the '.a' files from the 'lib' directory of SDL2 to the 'lib' directory in this folder."
	fi
fi
}


##	These statements should be switched a little if we completely switch to make.
if test $BUILD_STATIC -eq 0
	then Build
elif test $BUILD_STATIC -eq 1
	 then
	 echo "--> Building Demo"
##	Static needs to compile object files first, with the way the functions are setup.
	 make
	 Build
fi

