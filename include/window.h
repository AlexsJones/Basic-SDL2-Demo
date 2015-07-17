#ifndef _ENGINE_WINDOW_H
#define _ENGINE_WINDOW_H

#include "SDL2/SDL_image.h"
//#include "SDL2/SDL_render.h"
//#include "SDL2/SDL_events.h"
//#include "SDL2/SDL_rect.h"
#include <string>

#define TITLE "Plane of Craftiness[Alpha]"
#ifndef DATE
	#define DATE ""
#endif

#ifndef OPENGL_BACKEND
 #define OPENGL_BACKEND 0
#endif

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

typedef unsigned int Uint;

/**
 * 	Wrapper for SDL_Window*.
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
		
		SDL_Window* getWindow(){return window;}
		~Window();
};

#endif

