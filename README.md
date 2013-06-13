#### Created 2012 by Dan Hatch ####

## NOTE, THIS BUILD DOES NOT CURRENTLY WORK AND I DO NOT KNOW WHY.

## Install SDL2 (Required) ##
-----------------
### Download SDL2:
	hg clone http://hg.libsdl.org/SDL sdl2
	hg clone http://hg.libsdl.org/SDL_image sdl2_image

### Build SDL2 and SDL2_image:
	cd sdl2/ && mv .hg .hg1
	./autogen.sh
	./configure && make && sudo make install
	cd ../
	
	cd sdl2_image/ && mv .hg .hg1
	./autogen.sh
	./configure && make && sudo make install

## How to build the Game ##
-----------------
Go to source directory and compile:
	make

Then go back into the project's root directory and run the game:
	cd ../
	./sdl2-demo

Note: The executable must be run from the project directory
	
