#ifndef _ENGINE_WINDOW_H
#define _ENGINE_WINDOW_H

#include "SDL2/SDL_image.h"
//#include "SDL2/SDL_render.h"
//#include "SDL2/SDL_events.h"
//#include "SDL2/SDL_rect.h"
#include <string>

#define TITLE "Plane of Craftiness"
#define RELEASE "[ALpha]"
#ifndef DATE
	#define DATE ""
#endif

#ifndef OPENGL_BACKEND
 #define OPENGL_BACKEND 0
#endif

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

typedef unsigned int Uint;

/**	Needs to handle input.
 * Note: IF input is not grabbed, everytime window is focused it needs
 * 			to check if window is fullscreen. Ex. If user alt-tabs out of
 * 			fullscreen, the window looks restored, but behaves oddly.
 * 			So, if window is supposed to be fullscreen, on focus set it to
 * 			fullscreen. This feature could be added as a precaution even if
 * 			input is not grabbed.
 * 
 * 			When window is created it produces "invalid window" warning.
 * 
 * 			There should be some type of scaling(of images) for small windows.
 * 
 * 	NOTE: SDL_Window's position is absolutely useless
**/
class Window
{
	private:
		SDL_Rect box;
		SDL_Window* window;
		SDL_Renderer* canvas;
		SDL_DisplayMode displayMode;
		SDL_Surface* windowicon;
		int minWidth;
		int minHeight;
	public:
		Window();
		SDL_Renderer* create();
		void restore();
		void fullscreen();		
		void toggleFullscreen();
		void resize();
		void setMinWidth(Uint w);
		void setMinHeight(Uint h);
		void setMinSize(Uint w, Uint h);
		const SDL_Rect &getBox();
		bool isFullscreen();
		void update( SDL_WindowEvent event );
		~Window();
};
#endif
