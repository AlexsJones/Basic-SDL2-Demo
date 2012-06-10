##The game must be built using 'make' in this directory before running this 
##script. This script links the '.o' files into a static executable. 

DATE=$(date +%Y%m%d)
g++ engine/*.o -Llib -Wl,-Bstatic lib/libSDL2.a lib/libSDL2_image.a lib/libSDL2main.a -lsmpeg -lmikmod -lvorbisfile -lvorbis -logg -lXxf86dga -lXxf86vm -lXv -lXinerama -lXi -lpng -lz -lstdc++ -Wl,-Bdynamic -lpthread -lGL -lX11 -lXext -ldl -lgcc -lGL -lGLU -lpthread -lGLEW -o ../"poc_static-"$DATE
