#ifndef _ENGINE_RESOURCES_H
#define _ENGINE_RESOURCES_H

#include "SDL.h"
#include "window.h"

/**	This will provide a set of functions for loading, retrieving and 
 * 	generally maintaining all resources for the game.(Images, sound, music, etc)
 * 	It may also be used for loading configuration settings, mods, and even menus.
 * 
 * 	Also components.
 * 
 * 	template<tyname T>
 * 	map<std::string, T> components;
 * 	
**/

template<typename T>
map<std::string, T> components;

namespace Resources{
	
inline SDL_Texture* loadImage( std::string filename )
{
	if (imageVault[filename])
		return imageVault[filename];
	else return loadNewImage(filename);
}

SDL_Texture* loadNewImage( std::string filename )
{
	std::string newfilename = IMG_DIR + filename + PNG;

	//if (!fileExists(newfilename);){ //request image from server --> put in IMG_DIR }
	if (fileExists(newfilename)){
		imageVault[filename] = IMG_LoadTexture(Engine::getCanvas(), newfilename.c_str());
		return imageVault[filename];
	}
	
	newfilename = IMG_DIR + filename + JPG;
	imagefile.open(newfilename.c_str());
	if (imagefile != NULL)
		return IMG_LoadTexture(canvas, newfilename.c_str());
	
	printf("Warning:: Failed to Load Image: '%s' in directory: %s\n", filename.c_str(), IMG_DIR);
	printf("	  Please make sure it has a '%s' extension.\n", PNG);
	printf("	  Attempting to use default texture instead...\n\n");
	
	newfilename = IMG_DIR + static_cast<std::string>("default") + PNG;
	imageVault[filename] = IMG_LoadTexture(Engine::getCanvas(), newfilename.c_str());
	return imageVault[filename];
}
	

};

#endif
