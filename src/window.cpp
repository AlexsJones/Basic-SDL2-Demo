#include "window.h"
#include "macro.h"

#include <iostream>
#include <exception>


Window::Window()
	: minWidth(480), minHeight(320)
{
	box.x = box.y = 0;
	box.w = WINDOW_WIDTH;
	box.h = WINDOW_HEIGHT;
}

Window::~Window() {
	SDL_DestroyRenderer(canvas);
	SDL_FreeSurface(windowicon);
	SDL_DestroyWindow(window);
}


SDL_Renderer* Window::create() {
	window = SDL_CreateWindow((TITLE),
				SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				WINDOW_WIDTH, WINDOW_HEIGHT,
				SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL );//| SDL_WINDOW_FULLSCREEN /*| SDL_WINDOW_OPENGL*/);
				
//	SDL_GetCurrentDisplayMode(SDL_GetWindowDisplay(window), &displayMode);
//	SDL_SetWindowDisplayMode(window, &displayMode);
	
	//printf("Window::Error: %s\n\n",SDL_GetError());
	
	windowicon = IMG_Load("icon.png");
	SDL_SetWindowIcon( window, windowicon );
	
	SDL_GetWindowSize( window, &box.w, &box.h );
	
/*	If SDL_RENDERER_PRESENTVSYNC is used, the Max Fps is based on your refreash
 * 	rate. So mine, for example is 60fps, you can only cap fps below this value.
 */
	canvas = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC );
	if ( !canvas ) {
		std::cout << "Failed to create the Renderer.";
		throw std::exception();
	}
	return canvas;
}

void Window::restore() {
	SDL_SetWindowFullscreen(window, SDL_FALSE);
	SDL_SetWindowGrab(window, SDL_FALSE);
}

void Window::fullscreen() {
		SDL_SetWindowFullscreen(window, SDL_TRUE);
		SDL_SetWindowGrab(window, SDL_TRUE);
}

void Window::toggleFullscreen() {
	if (hasFlag(SDL_GetWindowFlags(window), SDL_WINDOW_FULLSCREEN) )
		restore();
	else fullscreen();
}

/** Window::resize()
*	This function automatically sets-up the viewport to the window size at
*	the position(0,0). This allows camera to be centered over player correctly.
* 	resize() also prevents window from being too small.
**/
void Window::resize() {
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

void Window::setMinWidth(Uint w) { minWidth = w; }
void Window::setMinHeight(Uint h) { minHeight = h; }
void Window::setMinSize(Uint w, Uint h) { setMinWidth( w ); setMinHeight( h ); }

const SDL_Rect &Window::getBox() { return box; }

bool Window::isFullscreen() { return hasFlag(SDL_GetWindowFlags(window), SDL_WINDOW_FULLSCREEN); }


void Window::update( SDL_WindowEvent event ) {
	switch ( event.type )
	{
		case SDL_WINDOWEVENT_RESIZED:
			resize();
			break;
		case SDL_WINDOWEVENT_MAXIMIZED:
			break;
		case SDL_WINDOWEVENT_RESTORED:
			break;
			
		case SDL_WINDOWEVENT_SHOWN:
			break;
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			break;
//		case SDL_WINDOWEVENT_ENTER:				//Mouse Entered Window
			break;
			
		case SDL_WINDOWEVENT_MINIMIZED:
		case SDL_WINDOWEVENT_HIDDEN:
		case SDL_WINDOWEVENT_FOCUS_LOST:
//		case SDL_WINDOWEVENT_LEAVE:				//Mouse Left Window
			break;
			
//		case SDL_WINDOWEVENT_CLOSE:
//			break;
		default:
			break;	
	}
}



