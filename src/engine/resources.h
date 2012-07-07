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

namespace Resources
{
inline SDL_Texture* loadImage( std::string filename )
{
	if (imageVault[filename])
		return imageVault[filename];
	else return loadNewImage(filename);
}

SDL_Texture* loadNewImage( std::string filename )
{
	// Put the new one here from the engine.
}
	

};	/*	namespace Resources	*/

#endif
