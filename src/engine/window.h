/**     ______________________________________
	   /  _______    _______    ________     /\
      /	 / ___  /\  / ___  /\  / ______/\   / /\
     / 	/ /__/ / / / /  / / / / /\_____\/  / / /
    /  / _____/ / / /  / / / / / /        / / /
   /  / /\____\/ / /__/ / / / /_/___     / / /
  /  /_/ /      /______/ / /_______/\   / / /
 /   \_\/       \______\/  \_______\/  / / /
/_____________________________________/ / /
\_____________________________________\/ /
 \_____________________________________\/

**/

#ifndef _ENGINE_WINDOW_H
#define _ENGINE_WINDOW_H

#include "macro.h"
/**	Note: IF input is not grabbed, everytime window is focused it needs
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
 * 	NOTE: Window's position is absolutely useless
**/
class Window{
	private:
		SDL_Rect box;
		SDL_Window* window;
		SDL_DisplayMode displayMode;
		SDL_Renderer* canvas;
		SDL_Surface* windowicon;
		short MINIMUM_WINDOW_WIDTH;
		short MINIMUM_WINDOW_HEIGHT;
	public:
		Window() : MINIMUM_WINDOW_WIDTH(480), MINIMUM_WINDOW_HEIGHT(320)
		{
			box.x = box.y = 0;
			box.w = WINDOW_WIDTH;
			box.h = WINDOW_HEIGHT;
		}
		
		SDL_Renderer* create()
		{
			window = SDL_CreateWindow((TITLE" "RELEASE" "DATE),
						SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
						WINDOW_WIDTH, WINDOW_HEIGHT,
						SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
						
			SDL_GetCurrentDisplayMode(SDL_GetWindowDisplay(window), &displayMode);
			SDL_SetWindowDisplayMode(window, &displayMode);
			
			//printf("Window::Error: %s\n\n",SDL_GetError());
						
			windowicon = IMG_Load("icon.png");
			SDL_SetWindowIcon( window, windowicon );
			
			SDL_GetWindowSize( window, &box.w, &box.h );
			
			canvas = SDL_CreateRenderer(window, -1, 0 );
			return canvas;
		}

		void restore(){
			SDL_SetWindowFullscreen(window, SDL_FALSE);
			SDL_SetWindowGrab(window, SDL_FALSE);
		}
		
		void fullscreen(){
				SDL_SetWindowFullscreen(window, SDL_TRUE);
				SDL_SetWindowGrab(window, SDL_TRUE);
		}
		
		void toggleFullscreen(){
			if (hasFlag(SDL_GetWindowFlags(window), SDL_WINDOW_FULLSCREEN) )
				restore();
			else fullscreen();
		}
		
/** Window::resize()
*	This function automatically sets-up the viewport to the window size at
*	the position(0,0). This allows camera to be centered over player correctly.
* 	resize() also prevents window from being too small.
**/
		void resize()
		{
			SDL_GetWindowSize( window, &box.w, &box.h );
			if (box.w < MINIMUM_WINDOW_WIDTH){
				box.w = MINIMUM_WINDOW_WIDTH;
				SDL_SetWindowSize(window, box.w, box.h);
			}
			if (box.h < MINIMUM_WINDOW_HEIGHT){
				box.h = MINIMUM_WINDOW_HEIGHT;
				SDL_SetWindowSize(window, box.w, box.h);
			}
			SDL_RenderSetViewport( canvas, &box );
		}
		
		void setMinWidth(Uint w){ MINIMUM_WINDOW_WIDTH = w; }
		void setMinHeight(Uint h){ MINIMUM_WINDOW_HEIGHT = h; }
		void setMinSize(Uint w, Uint h){ setMinWidth( w ); setMinHeight( h ); }
		
		const SDL_Rect &getBox(){ return box; }
		
		bool isFullscreen(){ return hasFlag(SDL_GetWindowFlags(window), SDL_WINDOW_FULLSCREEN); }
		
		~Window()
		{
			SDL_FreeSurface(windowicon);
			SDL_DestroyRenderer(canvas);
			SDL_DestroyWindow(window);
		}

};
#endif
