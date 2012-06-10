
#include "engine.h"

#include <algorithm>

/** Instantiation of some static variables **/
	Window Engine::window;
	SDL_Renderer* Engine::canvas;
	std::map<std::string, SDL_Texture*> Engine::imageVault;
	Uint Ticks::startTicks;
	Uint Ticks::deltaTicks;
	Uint Ticks::fps;
	Uint Engine::ISOMETRIC(0);
	Uint Engine::DEBUG(0);


Engine::Engine()
	: quit(false), isPaused(false), hudRefreashRefTime(0), hudRefreashInterval(1000), ACTIVE_PLAYER(0), backgroundTile(NULL)
{
}

bool Engine::init()
{
	SDL_Init(SDL_INIT_VIDEO || SDL_INIT_TIMER);
	
	canvas = window.create();
	
	map.load();
	camera.resize(window.getBox());
	
	if (map.isActive()) { camera.setMap(map.getBox()); }
	
	//Prevent 'players' vector from re-allocating when new players are added
	players.reserve(MAX_PLAYERS);
	
	//Add invisible spectator to move around, this may be removed soon
		Player spectator;
		//addPlayer(spectator);
	//printf( "Spectator is at %d,%d\n", players[0].getBox().x ,players[0].getBox().y );
	
	//Provide a sense of how big the map is in relation to player speed.
	printf	("It will take %.2f minutes for player to travel across the entire map\n\n",
			(map.getBox().w / spectator.getMaxVelocity()) / 60.f );

	return true;
}

void Engine::pause(){
		timer.pause();
		isPaused = true;
		printf("Game has been paused\n");
}
void Engine::resume(){
		timer.resume();
		isPaused = false;
		printf("Game has been unpaused\n");
}
void Engine::pauseResume(){
	if (isPaused){
		resume(); isPaused = false; }
	else{ pause(); isPaused = true; }
}

//###### Start of the Main Game Loop ########
void Engine::game_loop()
{
	timer.start();
//	gameStarted = true;
	while ( quit == false )		//	&& menu == false		//engine.menu_loop()
	{
		Ticks::start();
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
					if (event.key.keysym.sym == SDLK_F1){
						if (ISOMETRIC){ ISOMETRIC = 0; setMenuBackground("grass");}
						else { ISOMETRIC = 1; setMenuBackground("grass(old)");}
					}
					if (event.key.keysym.sym == SDLK_TAB){
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
					//if mouseclick interfaces with GUI --> do this
					//else translate to grid pos + send event to object
						printf("Mouseclick: (%d, %d)\n", event.motion.x, event.motion.y);
					break;
				case SDL_WINDOWEVENT:
					if (event.window.event == SDL_WINDOWEVENT_RESIZED){
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
		if (backgroundTile){		
			tileTexture2(backgroundTile, backgroundClip, map.getView(camera.getBox()));
		//	tileMenuBackground();
		}
		showPlayers();
		
		debug();

		render();
		timer.update();
		Ticks::capFPS( MAX_FPS );
	}
}
//######## End Game Loop ########

inline bool Engine::fileExists(std::string filename){
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

void Engine::drawRect(SDL_Rect rect)
{
	SDL_Rect offset = rect;
	offset.x -= camera.getBox().x;
	offset.y -= camera.getBox().y;
	SDL_RenderDrawRect( Engine::getCanvas(), &offset);
}

/** All loading or requesting of images goes through this function
 * 	TODO:Add support for fetching from server so if user deleted img or
 * 	the client needs an image for a certain mod, it will receive it.
 * 	Start new thread for getting image.
 * 
 * 	...
 **/
 
inline SDL_Texture* Engine::loadImage( std::string filename )
{
	if (imageVault[filename])
		return imageVault[filename];
	else return loadNewImage(filename);
}

SDL_Texture* Engine::loadNewImage( std::string filename )
{
	std::string newfilename = IMG_DIR + filename + PNG;

	//if (!fileExists(newfilename);){ //request image from server --> put in IMG_DIR }
	if (fileExists(newfilename)){
		imageVault[filename] = IMG_LoadTexture(Engine::getCanvas(), newfilename.c_str());
		return imageVault[filename];
	}
//	NOTE: Enforcing PNG format!!
//	newfilename = IMG_DIR + filename + JPG;
//	imagefile.open(newfilename.c_str());
//	if (imagefile != NULL)
//		return IMG_LoadTexture(canvas, newfilename.c_str());
	
	printf("Warning:: Failed to Load Image: '%s' in directory: %s\n", filename.c_str(), IMG_DIR);
	printf("	  Please make sure it has a '%s' extension.\n", PNG);
	printf("	  Attempting to use default texture instead...\n\n");
	
	newfilename = IMG_DIR + static_cast<std::string>("default") + PNG;
	imageVault[filename] = IMG_LoadTexture(Engine::getCanvas(), newfilename.c_str());
	return imageVault[filename];
}

SDL_Rect Engine::getImageSheetDimensions(std::string character){
	SDL_Rect image;
	SDL_QueryTexture( Engine::loadImage(character), NULL, NULL, &image.w, &image.h );
	return image;
}

inline SDL_Rect Engine::getImageClip(Uint8 id){//for blocks and items
	SDL_Rect clip;
//	clip.x =  Engine::setClip( image, x, y, BLOCK_SIZE, BLOCK_SIZE )
	return clip;
}

//apply the entire texture onto an area of the canvas
inline void Engine::applyTexture( SDL_Texture* source, SDL_Rect& clip ){
	SDL_RenderCopy( Engine::getCanvas(), source, NULL, &clip );
}

inline void Engine::applyTexture( SDL_Texture* source, SDL_Rect& sourceclip, SDL_Rect& clip ){
	SDL_RenderCopy( Engine::getCanvas(), source, &sourceclip, &clip );
}

//This version tiles a texture that does not move with the camera.
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

int Engine::addPlayer(std::string type )
{
	if (map.isActive()){
		if (players.size() >= MAX_PLAYERS){
			printf("Warning:: Failed to add new player\n");
			printf("	  Maximum amount of Players allowed is %d.\n\n", MAX_PLAYERS);
			return 1;
		}
		//hard-coded player size, maybe will be used as default? 		//not here though
		Player playerX( type, 40, 60 );
		playerX.ID = players.size();
		players.push_back( playerX );
		camera.follow(&players[ACTIVE_PLAYER]);
	}
	return 0;
}

void Engine::addPlayer(Player &player)
{
	player.ID = players.size();
	players.push_back( player );
	camera.follow(&players[ACTIVE_PLAYER]);
}

template <typename Object1, typename Object2>
inline bool collides( Object1 &object1, Object2 &object2 ){		
	return SDL_HasIntersection(&object1.getBox(), &object2.getBox());
}

inline bool collides( SDL_Rect rect1, SDL_Rect rect2 ){		
	return SDL_HasIntersection(&rect1, &rect2);
}


/**	Should objects control how their drawn, and engine tells it where to draw.
 * 	This would allow greater flexibility with special abilities, and engine
 * 	wouldn't need to know much.
**/
template <typename Object>
void show( Object &object, SDL_Rect offset)
{
	SDL_Rect objectBox = object.getBox();
	objectBox.x -= offset.x;
	objectBox.y -= offset.y;
	object.animate(); //should this be removed? or changed to draw()?
	switch (object.objectType)
	{
		case CHARACTER:
		{
			//if ( object.isDead() ){
			//	Ghost Mode:
			//	SDL_SetTextureBlendMode(Engine::loadImage(object.name), SDL_BLENDMODE_ADD);		//increases brightness
			//	SDL_SetTextureAlphaMod(Engine::loadImage(object.name), 128); 					//50% transparent
			//}
			SDL_RenderCopy( Engine::getCanvas(), Engine::loadImage(object.name),
							&object.getImage(), &objectBox );
			break;
		}
/**		case ITEM:
 			SDL_RenderCopy(Engine::getCanvas(), Engine::loadImage(ITEM_SHEET),
 			 				object.getImage(), &objectBox );
 			break;
		case BLOCK:
			SDL_RenderCopy( Engine::getCanvas(), Engine::loadImage(BLOCK_SHEET),
			 				object.getImage(), &objectBox );
			break;
**/
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
 * 
**/
	renderPlayers.clear();
	
	players[ACTIVE_PLAYER].update();
	camera.update();
	for( Uint i = 0; i< players.size(); i++){
		if (i != ACTIVE_PLAYER)
			players[i].update();
		if( collides(camera, players[i]) ){
			renderPlayers.push_back(players[i]);
		}
	}
	renderPlayers.sort();
}

//player needs to collide with map other objects.

void Engine::showPlayers()
{
/**	This function cycles through all players that are stored in the
 * 	renderPlayers.
**/
	for( auto playerIndex: renderPlayers ){
			if (DEBUG)
				drawRect( players[playerIndex.ID].getBox() );
			show(players[playerIndex.ID], camera.getBox());
		}
}

void Engine::handleInput(SDL_KeyboardEvent& keyevent) //currently not used anymore
{
//	if keysym matches player controls
//	if inventory ----> do something
	players[ACTIVE_PLAYER].move(keyevent);
//	else pass to engine(e.g. show menu, pause/resume game, navigate menu, show text console, talk)
}

inline void Engine::keepInBounds(SDL_Rect& box, SDL_Rect& Bounds){
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
	
	for (int rowIndex = 0; rowIndex < totalRows; rowIndex++){
		for (int columnIndex = 0; columnIndex < totalColumns; columnIndex++){
			clip.x = columnIndex*clip.w - bounds.w/2;
			clip.y = rowIndex*clip.h - bounds.h/2;
			if (collides(clip,camera.getBox())){
				clip.x -= camera.getBox().x;
				clip.y -= camera.getBox().y;
				applyTexture( source, clip );
			}
		}
	}
}
//This is currently used to tile a texture whose bounds is based on the camera.
//There for
void Engine::tileTexture2( SDL_Texture* source, SDL_Rect& clip, SDL_Rect bounds )
{
	// !(bounds.h % clip.h) ? bounds.h / clip.h : bounds.h / clip.h + 1;
	int totalColumns = bounds.w / clip.w + 1;
	int totalRows = bounds.h / clip.h + 1;
	
	for (int rowIndex = 0; rowIndex < totalRows; rowIndex++){
		for (int columnIndex = 0; columnIndex < totalColumns; columnIndex++){
			clip.x = columnIndex*clip.w + (bounds.x - camera.getBox().x);
			clip.y = rowIndex*clip.h + (bounds.y - camera.getBox().y);
			applyTexture( source, clip );
		}
	}
}

inline void Engine::render(){ SDL_RenderPresent(Engine::getCanvas()); }
inline void Engine::renderClear(){ SDL_RenderClear(Engine::getCanvas()); }
                                                                                       
void Engine::showSplash(){}
void Engine::closeSplash(){}

inline void Engine::setMenuBackground( std::string filename ){
	backgroundTile = loadNewImage(filename);
	backgroundClip = setClip(backgroundTile, 0, 0, 0, 0);
}

//void Engine::tileMenuBackground(){ tileTexture(backgroundTile, backgroundClip); }
inline void Engine::tileMenuBackground(){ tileTexture(backgroundTile, backgroundClip); }

//SDL_Texture* Engine::loadMap(std::string filename){}
void Engine::loadLevel(){}

//getters
const SDL_Event& Engine::getEvent(){ return event; }
SDL_Renderer* Engine::getCanvas(){ return canvas; }

void Engine::debug()
{
	if (DEBUG){
		drawRect( camera.getBox() );
		drawRect( map.getBox() );
		if ( !isPaused && DEBUG && Timer::updateInterval(hudRefreashInterval, hudRefreashRefTime )){
			printf("Time: %d  ", timer.getGameTime() / 1000);
			printf("@  %d fps\n",Ticks::getFPS());
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
