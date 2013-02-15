
#include "engine.h"

#include <algorithm>

/*	Instantiation of some static variables :(	*/
	Window Engine::window;
	SDL_Renderer* Engine::canvas;
	std::map<std::string, SDL_Texture*> Engine::imageVault;
	Uint Engine::DEBUG(0);

Engine::Engine()
	: quit(false), isPaused(false), hudRefreashInterval(1000), ACTIVE_PLAYER(0), backgroundTile(NULL)
{
}

bool Engine::init()
{
	SDL_Init(SDL_INIT_VIDEO || SDL_INIT_TIMER);
	
	canvas = window.create();
	map.load();
	camera.resize(window.getBox());
	if (map.isActive()) { camera.setBounds(map.getBox()); }
	
/*	Prevent 'players' vector from re-allocating when new players are added */
	players.reserve(MAX_PLAYERS);
	
/*	Provide a sense of how big the map is in relation to player speed.	*/
	//printf	("It will take %.2f minutes for player to travel across the entire map\n\n",
	//			(map.getBox().w / spectator.getMaxVelocity()) / 60.f );
	return true;
}

void Engine::pause()
{
	timer.pause();
	isPaused = true;
	printf("Game has been paused.\n");
}

void Engine::resume()
{
	timer.resume();
	isPaused = false;
	printf("Game has been unpaused.\n");
}

void Engine::pauseResume()
{
	if (isPaused){
		resume(); isPaused = false; }
	else{ pause(); isPaused = true; }
}

/*	 Start of the Main Game Loop 	*/
void Engine::game_loop()
{
	timer.start();
//	gameStarted = true;
	while ( quit == false )		//	&& menu == false		//engine.menu_loop()
	{
		HRTicks.start();
		//pollEvents();
		while (SDL_PollEvent(&event))
		{
			switch (event.type){
				case SDL_QUIT:
					quit=true;
					break;
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE) pauseResume();
					if (event.key.keysym.sym == SDLK_F11){ window.toggleFullscreen(); }
					if (event.key.keysym.sym == SDLK_F2){ DEBUG++; if (DEBUG > 3) DEBUG = 0; }
					if (event.key.keysym.sym == SDLK_F1)
					{
						if ( backgroundTile == loadImage("grass") ){
							setMenuBackground("grass(old)");
						}
						else { setMenuBackground("grass"); }
					}
					//Todo, change switch players to an android compatible button.
					if (event.key.keysym.sym == SDLK_TAB)
					//if (event.key.keysym.sym == SDLK_q)
					{
						if(ACTIVE_PLAYER < players.size() - 1){
							ACTIVE_PLAYER++;
							camera.follow(&players[ACTIVE_PLAYER]);
						}
						else{ ACTIVE_PLAYER = 0; camera.follow(&players[ACTIVE_PLAYER]);}
					}	
				if ( !isPaused && map.isActive() && !players.empty() )
						players[ACTIVE_PLAYER].move(event.key);
//						handleInput(event.key);			//contains scancode, keycode, and key modifier
//				else if (!isPaused && map.isLoaded()&& players.empty() )
//						camera.move();
				break;
				case SDL_KEYUP:
					if (map.isActive() && !players.empty() )
						players[ACTIVE_PLAYER].move(event.key);
						//handleInput(event.key);
//					printf("Key Pressed: %s\n", SDL_GetKeyName(event.key.keysym.sym));	//converts keycode to normal key name
					break;
				case SDL_MOUSEBUTTONDOWN:
					if (DEBUG)
				/*	If mouseclick interfaces with GUI --> execute element's onClick() function.	*/
				/*	Else translate to grid pos + send event to object.	*/
						printf("Mouseclick: (%d, %d)\n", event.motion.x, event.motion.y);
					break;
				case SDL_WINDOWEVENT:
					window.update(event.window);
					if ( event.window.event == SDL_WINDOWEVENT_RESIZED ){
						window.resize();
						camera.resize(window.getBox());
					}
					break;
				default: break;
			}
				
		}
		renderClear();

		update();
	//	render();	
/** ALL Rendering is done after this point **/	
		
		if (backgroundTile)
		{	
		/*	This is ugly.	*/		
			tileTexture2( backgroundTile, backgroundClip, map.getView(camera.getBox()) );
		//	tileMenuBackground();
		}
		
		drawPlayers();
		
		debug();

		render();
		timer.update();
		HRTicks.capFPS( MAX_FPS );
	}
}
/* END of Main Game Loop	*/

inline bool Engine::fileExists(std::string filename){
	//Need method for checking file on __ANDROID__
	std::ifstream file(filename.c_str());
	return file.is_open();
}

SDL_Rect Engine::setClip ( SDL_Texture* source, int xOffset, int yOffset, int clipWidth, int clipHeight )
{
	SDL_Rect clip;
	clip.x = xOffset;
	clip.y = yOffset;
	if (source){
		if (clipWidth == 0){SDL_QueryTexture(source, NULL, NULL, &clipWidth, NULL);}
		if (clipHeight == 0){SDL_QueryTexture(source, NULL, NULL, NULL, &clipHeight);}
	}
	clip.w = clipWidth;
	clip.h = clipHeight;
	return clip;
}

SDL_Rect Engine::setClip ( SDL_Texture* source )
{
	SDL_Rect clip = {0,0,0,0};
	int clipWidth = 0;
	int clipHeight = 0;
	if (source){
		{SDL_QueryTexture(source, NULL, NULL, &clipWidth, &clipHeight);}
	}
	clip.w = clipWidth;
	clip.h = clipHeight;
	return clip;
}

void Engine::drawRect(SDL_Rect rect)
{
	rect.x -= camera.getBox().x;
	rect.y -= camera.getBox().y;
	SDL_RenderDrawRect( Engine::getCanvas(), &rect);
}

SDL_Texture* Engine::loadImage( std::string filename )
{
	if (imageVault[filename])
		return imageVault[filename];
	else return loadNewImage(filename);
}
#include <iostream>
SDL_Texture* Engine::loadNewImage( std::string filename )
{
	std::string newfilename = IMG_DIR + filename + PNG;
	imageVault[filename] = IMG_LoadTexture(Engine::getCanvas(), newfilename.c_str());
	return imageVault[filename];
	
//	if (fileExists( filename )){
//		imageVault[filename] = IMG_LoadTexture(Engine::getCanvas(), filename.c_str());
//		return imageVault[filename];
//	}
	
	//if (!fileExists(newfilename);){ //request image from server --> put in IMG_DIR }
	//if (fileExists(newfilename)){
	//	imageVault[filename] = IMG_LoadTexture(Engine::getCanvas(), newfilename.c_str());
	//	return imageVault[filename];
	//}

	newfilename = IMG_DIR + filename + JPG;
	if (fileExists(newfilename)){
		imageVault[filename] = IMG_LoadTexture(Engine::getCanvas(), newfilename.c_str());
		return imageVault[filename];
	}
	
	printf("Warning:: Failed to Load Image: '%s' in directory: %s\n", filename.c_str(), IMG_DIR);
	printf("	  Attempting to use default texture instead...\n\n");
	
	newfilename = IMG_DIR + static_cast<std::string>("default");
	imageVault[filename] = IMG_LoadTexture(Engine::getCanvas(), newfilename.c_str());
	return imageVault[filename];
}

SDL_Rect Engine::getImageSheetDimensions(std::string character){
	SDL_Rect image;
	SDL_QueryTexture( Engine::loadImage(character), NULL, NULL, &image.w, &image.h );
	return image;
}

SDL_Rect Engine::getImageClip(Uint8 id){//for blocks and items
	SDL_Rect clip;
//	clip.x =  Engine::setClip( image, x, y, BLOCK_SIZE, BLOCK_SIZE )
	return clip;
}

//apply the entire texture onto an area of the canvas
void Engine::applyTexture( SDL_Texture* source, SDL_Rect& clip ){
	SDL_RenderCopy( Engine::getCanvas(), source, NULL, &clip );
}

void Engine::applyTexture( SDL_Texture* source, SDL_Rect& sourceclip, SDL_Rect& clip ){
	SDL_RenderCopy( Engine::getCanvas(), source, &sourceclip, &clip );
}

//	This version tiles a texture that does not move with the camera.
//	This could be used by the GUI
void Engine::tileTexture( SDL_Texture* source, SDL_Rect& clip)
{
	//Check if texture fits perfectly in window
	SDL_Rect window = Engine::window.getBox();
	int totalColumns = window.w / clip.w + 1;
	int totalRows = window.h / clip.h + 1;
	
	for (int rowIndex = 0; rowIndex < totalRows; rowIndex++){
		for (int columnIndex = 0; columnIndex < totalColumns; columnIndex++){
			clip.x = columnIndex*clip.w;
			clip.y = rowIndex*clip.h;
			applyTexture( source, clip );
		}
	}
}

void Engine::addPlayer(Player &player)
{
	if (map.isActive()){
		if (players.size() >= MAX_PLAYERS){
			printf("Warning:: Failed to add new player\n");
			printf("	  Maximum amount of Players allowed is %d.\n\n", MAX_PLAYERS);
			return;
		}
	player.ID( players.size() );
	players.push_back( player );
	camera.follow(&players[ACTIVE_PLAYER]);
	}
}

template <typename Object1, typename Object2>
bool collides( Object1 &object1, Object2 &object2 ){		
	return SDL_HasIntersection(&object1.getBox(), &object2.getBox());
}

bool collides( SDL_Rect rect1, SDL_Rect rect2 ){		
	return SDL_HasIntersection(&rect1, &rect2);
}


/**	Should objects control how their drawn, and engine just handles what objects to draw.
 * 	This would allow greater flexibility with special abilities, and engine
 * 	wouldn't need to know much.
**/
template <typename Object>		//does this need to be a template if all clases are based on Object?(polymorphism)
void draw( Object &object, SDL_Rect offset)
{
	SDL_Rect objectBox = object.getBox();
/*	Camera position - Object position = Screen position	*/
	objectBox.x -= offset.x;
	objectBox.y -= offset.y;
	switch (object.objectType)
	{
		case CHARACTER:
		{
			//SDL_SetTextureAlphaMod(Engine::loadImage(object.name), 128); 					//50% transparent
			//SDL_SetTextureBlendMode(Engine::loadImage(object.name), SDL_BLENDMODE_ADD);		//increases brightness
			SDL_SetTextureColorMod(Engine::loadImage(object.name), 255,255,255);		//doesn't effect image
			/*Make this apply_texture whenever I can*/
			SDL_RenderCopy( Engine::getCanvas(), Engine::loadImage(object.name),
							&object.getImage(), &objectBox );	//	clip of image, clip on screen
			break;
		}
		default: break;
	}
}

void Engine::update()
{
/**	This function currently updates all players and the camera, then sorts
 * 	them into the correct order for rendering.
 * 	TODO: Need ID/username system for players.
 * 			Need to modify for ability to sort and store objects too.
 * 	
 * 	Note: STL containers(vector,list...) cannot store pointers or references. 
**/
	renderPlayers.clear();
	
	camera.update();
	for( Uint i = 0; i< players.size(); i++)
	{
		if (i != ACTIVE_PLAYER)
			players[i].update();
		if( collides(camera, players[i]) ){
			renderPlayers.push_back(players[i]);
		}
	}
	renderPlayers.sort();
}

void Engine::drawPlayers()
{
/**	This function cycles through all players that are stored in the
 * 	renderPlayers.
**/
	for( std::list<Player>::iterator playerIndex = renderPlayers.begin();
			playerIndex != renderPlayers.end(); playerIndex++ ){
			if (DEBUG){
				SDL_SetRenderDrawColor(canvas, 0, 255, 255, 255);
				drawRect( players[playerIndex->ID()].getBox() );
			}
			draw(players[playerIndex->ID()], camera.getBox());
		}
}

void Engine::keepInBounds(SDL_Rect& box, SDL_Rect& Bounds){
	if (box.x < Bounds.x){ box.x = Bounds.x; }
	else if (box.x + box.w > Bounds.x + Bounds.w){ box.x = Bounds.x + Bounds.w - box.w; }
	if (box.y < Bounds.y){ box.y = Bounds.y; }
	else if (box.y + box.h > Bounds.y + Bounds.h){ box.y = Bounds.y + Bounds.h - box.h; }
}

//Tiled Texture moves with camera.
void Engine::tileTexture( SDL_Texture* source, SDL_Rect& clip, SDL_Rect bounds)
{
	int totalColumns = bounds.w / clip.w + 1;
	int totalRows = bounds.h / clip.h + 1;
	
	for (int rowIndex = 0; rowIndex < totalRows; rowIndex++)
	{
		for (int columnIndex = 0; columnIndex < totalColumns; columnIndex++)
		{
			clip.x = columnIndex*clip.w - bounds.w/2;
			clip.y = rowIndex*clip.h - bounds.h/2;
			if (collides(clip,camera.getBox())){
				clip.x -= camera.getBox().x;
				clip.y -= camera.getBox().y;
	/* Why */	applyTexture( source, clip );
			}
		}
	}
}

/*	This is currently used to tile a texture whose bounds is based on the camera.
 * 	Tile a floor, then render it with respect to the camera.
 * 	Ok...There shouldn't be specialized functions that render things slightly 
 * 	differently?? Or is this an exception....Or make Camera a scene?, and and....IDK 
 * 	OR THIS: Map is a scene, which automatically offsets what it renders based
 * 	on the Camera....So scenes handle their own rendering...
 */ 
 #include "SDL2/SDL_render.h"
void Engine::tileTexture2( SDL_Texture* source, SDL_Rect& clip, SDL_Rect bounds )
{
	// !(bounds.h % clip.h) ? bounds.h / clip.h : bounds.h / clip.h + 1;
	int totalColumns = bounds.w / clip.w + 1;
	int totalRows = bounds.h / clip.h + 1;
	
	for (int rowIndex = 0; rowIndex < totalRows; rowIndex++)
	{
		for (int columnIndex = 0; columnIndex < totalColumns; columnIndex++)
		{
			clip.x = columnIndex*clip.w + (bounds.x - camera.getBox().x);
			clip.y = rowIndex*clip.h + (bounds.y - camera.getBox().y);
			applyTexture( source, clip );
		}
	}
}

void Engine::render(){ SDL_SetRenderDrawColor(canvas, 50, 150, 50, 255); SDL_RenderPresent(Engine::getCanvas()); }
void Engine::renderClear(){ SDL_RenderClear(Engine::getCanvas()); }
                                                                                       
void Engine::setMenuBackground( std::string filename ){
	backgroundTile = loadNewImage(filename);
	backgroundClip = setClip(backgroundTile);
}

void Engine::tileMenuBackground(){ tileTexture(backgroundTile, backgroundClip); }

void Engine::debug()
{
	if (DEBUG){
		SDL_SetRenderDrawColor(canvas, 255, 0, 0, 255);
		drawRect( camera.getBox() );
		drawRect( map.getBox() );
		if ( !isPaused && DEBUG && hudRefreashInterval() ){
			printf("Time: %lu  ", timer.getTime() / 1000);
			printf("@  %d fps\n",HRTicks.getFPS());
			if (DEBUG == 2){
				printf("camera: %d %d\n", camera.getBox().x, camera.getBox().y);
				printf("map: %d %d\n", map.getBox().x, map.getBox().y);
				printf("player: %d %d\n", players[ACTIVE_PLAYER].getBox().x, players[0].getBox().y);
				printf("\n");
				
		/** Use this to Tile a Custom texture to see how well it tiles **/ 
				setMenuBackground( "grass" );
				
			}
		}
	}
}

Engine::~Engine(){
/** May need to clean-up image vault. Since the
 * 	SDL_Textures* cannot be dealloc. with delete command the map<> may not
 * 	be able to automatically clean-up after itself.
**/
/**
	if (!imageVault.empty()){
		for ( auto texIndex: imageVault ){
			SDL_DestroyTexture(imageVault[texIndex]);
		}
	}
**/
	SDL_DestroyRenderer(canvas);
	SDL_Quit();
}
