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
/**	Needs input container that accepts window events.
 * 
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
 * 	NOTE: Window's position is absolutely useless
**/
class Window
{
	private:
		SDL_Rect box;
		SDL_Window* window;
		SDL_DisplayMode displayMode;
		SDL_Renderer* canvas;
		SDL_Surface* windowicon;
		int minWidth;
		int minHeight;
	public:
		Window() : minWidth(480), minHeight(320)
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
			if (box.w < minWidth){
				box.w = minWidth;
				SDL_SetWindowSize(window, box.w, box.h);
			}
			if (box.h < minHeight){
				box.h = minHeight;
				SDL_SetWindowSize(window, box.w, box.h);
			}
			SDL_RenderSetViewport( canvas, &box );
		}
		/*TODO: handling focus, engine mainly needs this?*/
		void setMinWidth(Uint w){ minWidth = w; }
		void setMinHeight(Uint h){ minHeight = h; }
		void setMinSize(Uint w, Uint h){ setMinWidth( w ); setMinHeight( h ); }
		
		const SDL_Rect &getBox(){ return box; }
		
		bool isFullscreen(){ return hasFlag(SDL_GetWindowFlags(window), SDL_WINDOW_FULLSCREEN); }
		
		void update( SDL_WindowEvent event )
		{
			switch ( event.type )
			{
				case SDL_WINDOWEVENT_RESIZED:
					break;
				case SDL_WINDOWEVENT_MAXIMIZED:
					break;
				case SDL_WINDOWEVENT_RESTORED:
					break;
					
				case SDL_WINDOWEVENT_SHOWN:
					break;
				case SDL_WINDOWEVENT_FOCUS_GAINED:
					break;
//				case SDL_WINDOWEVENT_ENTER:				//Mouse Entered Window
					break;
					
				case SDL_WINDOWEVENT_MINIMIZED:
				case SDL_WINDOWEVENT_HIDDEN:
				case SDL_WINDOWEVENT_FOCUS_LOST:
//				case SDL_WINDOWEVENT_LEAVE:				//Mouse Left Window
					break;
					
//				case SDL_WINDOWEVENT_CLOSE:
//					break;
				default:
					break;	
			}
		}
		
		~Window()
		{
			SDL_FreeSurface(windowicon);
			SDL_DestroyRenderer(canvas);
			SDL_DestroyWindow(window);
		}

};
#endif
