
#include "engine.h"
#include "object.h"
#include "component/animation.h"
#include <iostream>


class Pog : public Object { public: Pog(Engine& engine); };
Pog::Pog(Engine& engine) {
	name = "pog";
	Uint image = engine.loadImage("images/pog.png");
	imageId = image;
	
	box.x = box.y = 0;
	box.w = 47; box.h = 51;
	SDL_Rect frame = {0,0,47,51};
	frame.w = 47;
	frame.h = 51;
	
	animation.add( "left", AnimatedSprite(image, frame) );
	frame.y += frame.h;
	animation.add( "right", AnimatedSprite(image, frame) );
	frame.y += frame.h;
	animation.add( "up", AnimatedSprite(image, frame) );
	frame.y += frame.h;
	animation.add( "down", AnimatedSprite(image, frame) );
	frame.y += frame.h;
	animation.add( "up-left", AnimatedSprite(image, frame) );
	frame.y += frame.h;
	animation.add( "up-right", AnimatedSprite(image, frame) );
	frame.y += frame.h;
	animation.add( "down-left", AnimatedSprite(image, frame) );
	frame.y += frame.h;
	animation.add( "down-right", AnimatedSprite(image, frame) );
	
	animation.get();
	animation.set("down");
	animation.get();
}


class Pirate : public Object { public: Pirate(Engine& engine); };
Pirate::Pirate(Engine& engine) {
	name = "pirate";
	Uint image = engine.loadImage("images/pirate.png");
	imageId = image;
	box.w = 40; box.h = 60;
	SDL_Rect frame = {0,0,40,60};
	
	animation.add( "left", AnimatedSprite(image, frame, 6, 3) );
	frame.y += frame.h;
	animation.add( "right", AnimatedSprite(image, frame, 6, 3) );
	
	animation.setDefaultFrame("left",3);
	animation.setDefaultFrame("right",3);
}


bool makeWorld(Engine& engine) {
	Pog pog(engine);
	engine.addObject(pog);
	
	Pog largePog(engine);
	largePog.resize( 94, 102 );
	engine.addObject(largePog);
	
	Pirate pirate(engine);
	engine.addObject(pirate);
	
	/*Object monster( "monster", 40, 60 );
	monster.resize(80,120);
	engine.addObject(monster);
	Object small_monster( "monster", 20, 30 );
	engine.addObject(small_monster);
	*/
	return true;
}


int main(int argc, char *args[]) {
	printf("Use arrow keys to move\n");
	printf("Press Tab to switch characters\n");
	printf("Press F2 to toggle debugging modes \n");
	printf("Press F4 to toggle Fullscreen \n\n");
	
	//Engine engine;
	Engine engine;
	if (engine.init() == false) { return -1; }
	engine.setMenuBackground( "images/grass.png" );
	
	makeWorld( engine );
	
	std::cout << "[Client] Entering main game loop.\n";
	engine.game_loop();
	return 0;
}


