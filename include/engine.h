#ifndef _ENGINE_ENGINE_H
#define _ENGINE_ENGINE_H

#include <string>
#include <fstream>

#include <vector>
#include <map>
#include <list>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_video.h"
//#include "SDL/SDL_ttf.h"

typedef unsigned int Uint;

#include "timer.h"
#include "window.h"

#define DATA_DIR "data/"
#define IMG_DIR (DATA_DIR "images/")

#include "map.h"
#include "object.h"
#include "camera.h"

#define MAX_FPS 600

	//std::cout << "Rendering Image " << source << " at ";
	//	std::cout << "(" << sourceclip.x << "," << sourceclip.y << ")[" << sourceclip.w << "x" << sourceclip.h << "] ";
	//	std::cout << "(" << clip.x << "," << clip.y << ")[" << clip.w << "x" << clip.h << "]\n"

class Engine
{
private:
	static Window window;
	static SDL_Renderer* canvas;
	
	SDL_Event event;
	bool quit = false;
	bool isPaused = false;
	Interval<Uint32> hudRefreashInterval = Interval<Uint32>(1000);
	
	Map map;
	Camera camera;
	std::vector<Object> objects;
	Uint ACTIVE_OBJECT = 0;
	
	static std::vector<SDL_Texture*> images;
	static std::map<std::string, Uint> imageIdByName;
	
	Timer<Uint64> timer;
	Ticks HRTicks;
	
	SDL_Rect backgroundClip;
	Uint backgroundTile = 0;
	
public:
	Engine();
	bool init();
	void game_loop();
		void pause();
		void resume();
		void pauseResume();
		void update();
	void handleEvents();
	
	static bool fileExists(std::string filename);

	static SDL_Rect getImageSheetDimensions(Uint image);
	
	//This will be called by objects to get clip of texture from sheet
	static SDL_Rect getImageClip(Uint8 id);
	
	static Uint loadImage( std::string filename );
	static Uint loadNewImage( std::string filename );
	static SDL_Rect setClip( Uint source, int xOffset, int yOffset, int clipWidth, int clipHeight );
	static SDL_Rect setClip( Uint source );

	void drawRect(SDL_Rect rect);
	
	static void applyTexture( Uint source, const SDL_Rect& clip );
	static void applyTexture( Uint source, const SDL_Rect& sourceclip, const SDL_Rect& clip );
	
	static void keepInBounds(SDL_Rect& box, SDL_Rect& Bounds);
		
	void addObject(Object& object);
	void drawObjects();
	void handleInput(SDL_KeyboardEvent& keyevent);
	
	static void tileTexture( Uint source, SDL_Rect& clip);
	void tileTexture( Uint source, SDL_Rect& clip, SDL_Rect bounds );
	void tileTexture2( Uint source, SDL_Rect& clip, SDL_Rect bounds );
	
	void render();
	void renderClear();
	void cleanUp();
	
	static Window* getWindow(){ return &window; }
	inline SDL_Event& getEvent(){ return event; }
	static SDL_Renderer* getCanvas(){ return canvas; }
	
	void setMenuBackground( std::string filename );
	void tileMenuBackground();

	void* loadMap(std::string filename);		
	void debug();
	
	static Uint DEBUG; 
	
	~Engine();
};

#endif

