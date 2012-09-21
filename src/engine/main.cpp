
#include "engine.h"
#include "log.h"

/** TODO::create a game(or Client) class that interfaces with the engine.
 *  namespace Poc{ class Engine; class Window;}
 *  
 *  I NEED to come up with a name for this *ENGINE*, give it a nice clean API,
 * 	and give it bindings for python.
**/

int main(int argc, char *args[])
{
/*	Possibly support command line options...	*/
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
	
	Player monster( "monster", 40, 60 );
	monster.resize(80,120);
	engine.addPlayer(monster);

	
	std::cout << timestamp() << "[Client] Created player types successfully.\n";
	std::cout << timestamp() << "[Client] Entering main game loop.\n";
	
	engine.game_loop();		//----> menu_loop() + game_loop()
	
	//engine.quit();
	SDL_Quit();
	return 0;
}
