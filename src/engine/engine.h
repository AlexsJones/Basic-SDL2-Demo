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
//#include "SDL/SDL_ttf.h"	//for fonts

typedef unsigned int Uint;

#include "timer.h"

#include "window.h"

#define DATA_DIR "data/"
#define IMG_DIR (DATA_DIR "images/")

#include "map.h"	//Engine shouldn't have a map?
#include "object.h"
//#include "character.h"
#include "player.h"
#include "camera.h"

#define MAX_FPS 60
#define MAX_PLAYERS 256

/*	TODO:	IMPLEMENT COORDINATES
 * 			Come up with a good structure for all the functions/classes.
 * 			Remove all 'static' variables because Android doesn't like them.
 * 
 * 		Wrap up functionality better 
 * 
 * 	Many engine functions will probably be place into a 
 * 			game class and GUI/menu class.
 * 
 * 		If Engine was a namespace, functions could be forward declared
 * 
 * 		Rename function to getImageDimensions()
 * */
#define ITEM_SHEET "items"
#define BLOCK_SHEET "blocks"
#define PNG ".png"
#define JPG ".jpg"



class Engine
{
	private:
		static Window window;
		static SDL_Renderer* canvas;
		
		SDL_Event event;
		
		bool quit;
		bool isPaused;
//		bool gameStarted;
		Uint hudRefreashRefTime;
		Uint hudRefreashInterval;
		
		Map map;
		Camera camera;
		std::vector<Player> players;
		std::list<Player> renderPlayers;
		Uint ACTIVE_PLAYER;
		
		static std::map<std::string, SDL_Texture*> imageVault;
		
		
		SDL_Rect backgroundClip;
		SDL_Texture* backgroundTile;
		Timer timer;
		
	public:
		Engine();
		bool init();
		//void main_loop();		//this could include the game_loop and menu_loop
		//menu_loop();	
		void game_loop();
			void pause();
			void resume();
			void pauseResume();
			void update();

		static bool fileExists(std::string filename);

		static SDL_Rect getImageSheetDimensions(std::string character);
		
		//This will be called by objects to get clip of texture from sheet
		static SDL_Rect getImageClip(Uint8 id);
		
		static SDL_Texture* loadImage( std::string filename );
		static SDL_Texture* loadNewImage( std::string filename );
		static SDL_Rect setClip( SDL_Texture* source, int xOffset, int yOffset, int clipWidth, int clipHeight );
		static SDL_Rect setClip( SDL_Texture* source );

		void drawRect(SDL_Rect rect);

		static void applyTexture( SDL_Texture* source, SDL_Rect& clip );
		static void applyTexture( SDL_Texture* source, SDL_Rect& sourceclip, SDL_Rect& clip );
		
		static void keepInBounds(SDL_Rect& box, SDL_Rect& Bounds);
		SDL_Texture* loadMap( std::string filename );	
			
		void addPlayer(std::string type);
		void addPlayer(Player &player);
		void showPlayers();
		void handleInput(SDL_KeyboardEvent& keyevent);
		
		static void tileTexture( SDL_Texture* source, SDL_Rect& clip);
		void tileTexture( SDL_Texture* source, SDL_Rect& clip, SDL_Rect bounds );
		void tileTexture2( SDL_Texture* source, SDL_Rect& clip, SDL_Rect bounds );
		
		void render();
		void renderClear();
		void cleanUp();
		
		//getters
		const SDL_Event& getEvent();
		static SDL_Renderer* getCanvas();
		
		void showSplash();
		void closeSplash();
		void setMenuBackground( std::string filename );
		void tileMenuBackground();
		void loadLevel();
		
		void debug();
		
		static Uint ISOMETRIC;
		static Uint DEBUG; 
		
		~Engine();
};
#endif
