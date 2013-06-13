#ifndef _ENGINE_RESOURCES_H
#define _ENGINE_RESOURCES_H

#include "SDL.h"
#include "window.h"

/**	
 * 	Fetches and stores Images.
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
