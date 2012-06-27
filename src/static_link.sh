##	Plane of Craftiness
##
##	This script links the '.o' object files into a static executable.
##	TODO::	This file needs to be modified, figure out which libs my game actually uses.
##	HINT::	Use linux-app-checker

DATE=$(date +%Y%m%d)

function Build()
{
	echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	echo "|  Creating static BIN file  |"

	g++ engine/*.o engine/component/.o* -Llib -Wl,-Bstatic lib/libSDL2.a lib/libSDL2_image.a lib/libSDL2main.a -lsmpeg -lmikmod -lvorbisfile -lvorbis -logg -lXxf86dga -lXxf86vm -lXv -lXinerama -lXi -lpng -lz -lstdc++ -Wl,-Bdynamic -lpthread -lGL -lX11 -lXext -ldl -lgcc -lGL -lGLU -lpthread -lGLEW -o ../"poc_static-"$DATE
}

## Send err stream to /dev/null
ls engine/main.o

if test $@ -eq 0
	then Build
	else echo "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
		 echo "XX  Building Plane of Craftiness  XX"
		 echo "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
		 make
		 Build
		 echo "|  Cleaning up....           |"
		 echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
		 make clean
fi
