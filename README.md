#### Created by Dan Hatch 2012 ####

This demo requires SDL2 and SDL2_image.

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
	cd src/
	make

Then go back into the project's root directory and run the game:
	cd ../
	./sdl2-demo

Note: The executable must be run from the project directory
	  Unless you generate a launcher (Only works in Unix environments?):
	./generate_launcher.sh
	
	
