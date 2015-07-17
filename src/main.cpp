
#include "engine.h"

#include <iostream>

int main(int argc, char *args[])
{
	printf("Use arrow keys to move\n");
	printf("Press Tab to switch characters\n");
	printf("Press F2 to toggle debugging modes \n");
	printf("Press F11 to toggle Fullscreen \n\n");
	
	//Engine engine;
	Engine engine;
	if (engine.init() == false) {return -1;}
	engine.setMenuBackground( "grass" );
	
	//engine.registerCharacter(Character actor){character_db.add(actor.name(),actor);}
	
	Pog pog;
	engine.addPlayer(pog);
	
	Pog largePog;
	largePog.resize( 94, 102 );
	engine.addPlayer(largePog);
	
	Player pirate( "pirate", 40, 60 );
	engine.addPlayer(pirate);
	
	/*Player monster( "monster", 40, 60 );
	monster.resize(80,120);
	engine.addPlayer(monster);
	
	Player small_monster( "monster", 40, 60 );
	engine.addPlayer(small_monster);
	*/
	
	std::cout << "[Client] Created player types successfully.\n";
	std::cout << "[Client] Entering main game loop.\n";
	
	engine.game_loop();		//----> menu_loop() + game_loop()
	
	//engine.quit();
	SDL_Quit();
	return 0;
}
