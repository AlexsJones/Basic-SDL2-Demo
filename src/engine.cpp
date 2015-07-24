
#include "engine.h"
#include "SDL2/SDL_render.h"

#include <algorithm>
#include <iostream>

// TODO Collides
template <typename Object1, typename Object2>
bool collides( Object1& object1, Object2& object2 ) {
	return SDL_HasIntersection(&object1.getBox(), &object2.getBox());
}


bool collides( SDL_Rect rect1, SDL_Rect rect2 ) {
	return SDL_HasIntersection(&rect1, &rect2);
}



Window Engine::window;
SDL_Renderer* Engine::canvas;
std::vector<SDL_Texture*> Engine::images;
std::map<std::string, Uint> Engine::imageIdByName;
Uint Engine::DEBUG(0);


Engine::Engine() {}

bool Engine::init() {
	images.push_back(0);
	
	SDL_Init(SDL_INIT_VIDEO || SDL_INIT_TIMER);
	
	canvas = window.create();
	
	loadNewImage("images/default.png");

	map.load();
	map.generate();
	camera.resize(window.getBox());
	if (map.isActive()) { camera.setBounds(map.getBox()); }
	
	// Provide a sense of how big the map is in relation to player speed
	//printf	("It will take %.2f minutes for player to travel across the entire map\n\n",
	//			(map.getBox().w / spectator.getMaxVelocity()) / 60.f );
	return true;
}

void Engine::pause() {
	timer.pause();
	isPaused = true;
	printf("Game has been paused.\n");
}

void Engine::resume() {
	timer.resume();
	isPaused = false;
	printf("Game has been unpaused.\n");
}

void Engine::pauseResume() {
	if (isPaused) { resume(); isPaused = false; }
	else{ pause(); isPaused = true; }
}


void Engine::game_loop() {
	timer.start();
	while ( quit == false )	{
		HRTicks.start();
		handleEvents();
		update();
		renderClear();
		if (backgroundTile) {
			tileTexture2( backgroundTile, backgroundClip, map.getView(camera.getBox()) );
		}
		drawObjects();
		debug();
		render();
		HRTicks.capFPS( MAX_FPS );
	}
}

void Engine::handleEvents() {
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				quit=true;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) pauseResume();
				if (event.key.keysym.sym == SDLK_F4){ window.toggleFullscreen(); }
				if (event.key.keysym.sym == SDLK_F2){ DEBUG++; if (DEBUG > 3) DEBUG = 0; }
				if (event.key.keysym.sym == SDLK_F1) {
					if ( backgroundTile == loadImage("images/grass.png") ) {
						setMenuBackground("images/stoneblock.png");
					}
					else { setMenuBackground("images/grass.png"); }
				}
				if (event.key.keysym.sym == SDLK_TAB) {
					if(ACTIVE_OBJECT < objects.size() - 1) {
						ACTIVE_OBJECT++;
						camera.follow(&objects[ACTIVE_OBJECT]);
					}
					else{ ACTIVE_OBJECT = 0; camera.follow(&objects[ACTIVE_OBJECT]);}
				}
			if ( !isPaused && map.isActive() && !objects.empty() )
					objects[ACTIVE_OBJECT].move(event.key);
					//handleInput(event.key);			//contains scancode, keycode, and key modifier
				//else if (!isPaused && map.isLoaded()&& objects.empty() )
					//camera.move();
				break;
			case SDL_KEYUP:
				if (map.isActive() && !objects.empty() )
					objects[ACTIVE_OBJECT].move(event.key);
					//handleInput(event.key);
					//printf("Key Pressed: %s\n", SDL_GetKeyName(event.key.keysym.sym));	//converts keycode to normal key name
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (DEBUG) {
					/* If mouseclick interfaces with GUI --> execute element's onClick() function.	*/
					/* Else translate to grid pos + send event to object.	*/
					printf("Mouseclick: (%d, %d)\n", event.motion.x, event.motion.y);
				}
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
}


bool Engine::fileExists(std::string filename) {
	//Need method for checking file on __ANDROID__
	std::ifstream file(filename.c_str());
	if ( !file.is_open() ) printf("Couldn't find %s.\n",filename.c_str());
	return file.is_open();
}

SDL_Rect Engine::setClip( Uint source, int xOffset, int yOffset, int clipWidth, int clipHeight ) {
	SDL_Rect clip;
	clip.x = xOffset;
	clip.y = yOffset;
	SDL_Texture* image = images[source];
	if (image) {
		if (clipWidth == 0) {
			SDL_QueryTexture(image, NULL, NULL, &clipWidth, NULL);
		}
		if (clipHeight == 0) {
			SDL_QueryTexture(image, NULL, NULL, NULL, &clipHeight);
		}
	}
	clip.w = clipWidth;
	clip.h = clipHeight;
	return clip;
}

SDL_Rect Engine::setClip ( Uint source ) {
	SDL_Rect clip = {0,0,0,0};
	int clipWidth = 0;
	int clipHeight = 0;
	SDL_Texture* image = images[source];
	if (image) { SDL_QueryTexture(image, NULL, NULL, &clipWidth, &clipHeight); }
	clip.w = clipWidth;
	clip.h = clipHeight;
	return clip;
}

void Engine::drawRect(SDL_Rect rect) {
	rect.x -= camera.getBox().x;
	rect.y -= camera.getBox().y;
	SDL_RenderDrawRect( Engine::getCanvas(), &rect);
}

Uint Engine::loadImage( std::string filename ) {
	auto it = imageIdByName.find(filename);
	if (it == imageIdByName.end()) {
		//std::cout << "loading new image: " << filename << "\n";
		return loadNewImage(filename);
	}
	else { return it->second; }
}


Uint Engine::loadNewImage( std::string filename ) {
	Uint id = 0;
	std::string fullname = DATA_DIR + filename;
	if ( fileExists(fullname) ) { goto do_load; }
	// Check cache..
	// Request from server
	printf("Warning:: Failed to Load Image: '%s'", filename.c_str());
	printf("	  Attempting to use default texture instead...\n");
	filename = "images/default.png";
	id = imageIdByName[filename];
	if (id) { return id; }
	fullname = DATA_DIR + filename;
	
do_load:
	//std::cout << "Loading image: " << fullname << "\n";
	SDL_Texture* image = IMG_LoadTexture(Engine::getCanvas(), fullname.c_str());
	if (!image) { return 0; }
	images.push_back(image);
	id = images.size()-1;
	imageIdByName[filename] = id;
	return id;
}



SDL_Rect Engine::getImageSheetDimensions(Uint image) {
	SDL_Rect clip;
	clip.x = clip.y = 0;
	SDL_QueryTexture( images[image], NULL, NULL, &clip.w, &clip.h );
	return clip;
}


//apply the entire texture onto an area of the canvas
void Engine::applyTexture( Uint source, const SDL_Rect& clip ) {
	SDL_RenderCopy( Engine::getCanvas(), images[source], NULL, &clip );
}

void Engine::applyTexture( Uint source, const SDL_Rect& sourceclip, const SDL_Rect& clip ) {
	if (source >= images.size()) { return; }
	SDL_RenderCopy( Engine::getCanvas(), images[source], &sourceclip, &clip );
}

//	This version tiles a texture that does not move with the camera.
//	This could be used by the GUI
void Engine::tileTexture( Uint source, SDL_Rect& clip ) {
	//Check if texture fits perfectly in window
	SDL_Rect window = Engine::window.getBox();
	int totalColumns = window.w / clip.w + 1;
	int totalRows = window.h / clip.h + 1;
	
	for (int rowIndex = 0; rowIndex < totalRows; rowIndex++) {
		for (int columnIndex = 0; columnIndex < totalColumns; columnIndex++) {
			clip.x = columnIndex*clip.w;
			clip.y = rowIndex*clip.h;
			applyTexture(source, clip);
		}
	}
}

// Tiled Texture moves with camera.
void Engine::tileTexture( Uint source, SDL_Rect& clip, SDL_Rect bounds ) {
	int totalColumns = bounds.w / clip.w + 1;
	int totalRows = bounds.h / clip.h + 1;
	for (int rowIndex = 0; rowIndex < totalRows; rowIndex++) {
		for (int columnIndex = 0; columnIndex < totalColumns; columnIndex++) {
			clip.x = columnIndex*clip.w - bounds.w/2;
			clip.y = rowIndex*clip.h - bounds.h/2;
			if (collides(clip,camera.getBox())){
				clip.x -= camera.getBox().x;
				clip.y -= camera.getBox().y;
				applyTexture(source, clip);
			}
		}
	}
}


void Engine::tileTexture2( Uint source, SDL_Rect& clip, SDL_Rect bounds ) {
	// !(bounds.h % clip.h) ? bounds.h / clip.h : bounds.h / clip.h + 1;
	int totalColumns = bounds.w / clip.w + 1;
	int totalRows = bounds.h / clip.h + 1;
	for (int rowIndex = 0; rowIndex < totalRows; rowIndex++) {
		for (int columnIndex = 0; columnIndex < totalColumns; columnIndex++) {
			clip.x = columnIndex*clip.w + (bounds.x - camera.getBox().x);
			clip.y = rowIndex*clip.h + (bounds.y - camera.getBox().y);
			applyTexture(source, clip);
		}
	}
}


void Engine::addObject(Object& object) {
	if (map.isActive()) {
		object.ID( objects.size() );
		objects.push_back( object );
		camera.follow(&objects[ACTIVE_OBJECT]);
	}
}


void Engine::update() {
	/*Uint64 newTime = timer.get();
	double frameTime = (newTime - currentTime) / (double)Time::hrTicksPerSecond;
	currentTime = newTime;
	
	// Avoid falling behind.
	frameTime = std::min( frameTime, maxFrameTime );

	// Add it to the previous frame's left-over time.
	availableTime += frameTime;
	
	while ( availableTime >= dt ) {
		systemManager->update( dt );
		entityManager->update();
		
		t += dt;
		availableTime -= dt;
	}*/
	const double dt = 16.66;
	camera.update(dt);
	for( Uint i = 0; i < objects.size(); i++) {
		if (i != ACTIVE_OBJECT) { objects[i].update(dt); }
	}
}


//SDL_SetTextureAlphaMod(images[object.imageId], 128); 					//50% transparent
//SDL_SetTextureBlendMode(images[object.imageId], SDL_BLENDMODE_ADD);	//increases brightness
void Engine::drawObjects() {
	std::vector<Uint> renderObjects;
	for( Uint i = 0; i < objects.size(); ++i) {
		//TODO if is renderable, collides with camera, need render layers
		if( collides(camera, objects[i]) ) { renderObjects.push_back(i); }
		objects[i].getImage();
	}
	std::sort( renderObjects.begin(), renderObjects.end(),
		[this](Uint id1, Uint id2 )->bool{
			return (objects[id1].box.y + objects[id1].box.h)
				< (objects[id2].box.y + objects[id2].box.h);
	});
	SDL_Rect offset = camera.getBox();
	for (Uint i = 0; i < renderObjects.size(); ++i) {
		Object& object = objects[ renderObjects[i] ];
		
		if (DEBUG) { SDL_SetRenderDrawColor(canvas, 0, 255, 255, 255); drawRect( object.getBox() ); }
		
		// Camera position - Object position = Screen position
		SDL_Rect objectBox = object.getBox();
		objectBox.x -= offset.x;
		objectBox.y -= offset.y;
		//SDL_SetTextureColorMod(images[object.imageId], 255,255,255);
		applyTexture( object.imageId, object.getImage(), objectBox );
		//SDL_RenderCopy( Engine::getCanvas(), images[object.imageId],
		//				&object.getImage(), &objectBox );
	}
}


void Engine::keepInBounds(SDL_Rect& box, SDL_Rect& Bounds) {
	if (box.x < Bounds.x) { box.x = Bounds.x; }
	else if (box.x + box.w > Bounds.x + Bounds.w) {
		box.x = Bounds.x + Bounds.w - box.w;
	}
	if (box.y < Bounds.y) { box.y = Bounds.y; }
	else if (box.y + box.h > Bounds.y + Bounds.h) {
		box.y = Bounds.y + Bounds.h - box.h;
	}
}


void Engine::render() { SDL_SetRenderDrawColor(canvas, 50, 150, 50, 255); SDL_RenderPresent(Engine::getCanvas()); }
void Engine::renderClear() { SDL_RenderClear(Engine::getCanvas()); }
                                                                                       
void Engine::setMenuBackground( std::string filename ) {
	backgroundTile = loadNewImage(filename);
	backgroundClip = setClip(backgroundTile);
}

void Engine::tileMenuBackground() { tileTexture(backgroundTile, backgroundClip); }

void Engine::debug() {
	if (!DEBUG) { return; }
	SDL_SetRenderDrawColor(canvas, 255, 0, 0, 255);
	drawRect( camera.getBox() );
	drawRect( map.getBox() );
	if ( !isPaused && DEBUG && hudRefreashInterval() ) {
		printf("Time: %lu  ", timer.getTime() / 1000);
		printf("@  %d fps\n",HRTicks.getFPS());
		if (DEBUG == 2) {
			printf("camera: %d %d\n", camera.getBox().x, camera.getBox().y);
			printf("map: %d %d\n", map.getBox().x, map.getBox().y);
			printf("object: %d %d\n", objects[ACTIVE_OBJECT].getBox().x, objects[0].getBox().y);
			printf("\n");
			setMenuBackground( "images/grass.png" );
		}
	}
}

Engine::~Engine() {
	for ( auto& image: images ) { SDL_DestroyTexture(image); }
	SDL_DestroyRenderer(canvas);
	SDL_Quit();
}


