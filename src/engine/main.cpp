
#include "engine.h"
#include "log.h"

/** TODO::create a game(or Client) class that interfaces with the engine.
 *  namespace Poc{ class Engine; class Window;}
 *  
 *  I NEED to come up with a name for this *ENGINE*, give it a nice clean API,
 * 	and give it bindings for python.
**/
class MyRect
{
public:
	int x,y;
	int w,h;
};
void Test(SDL_Rect rect)
{
	printf("Yay it worked %d,%d  %d x %d.\n",rect.x,rect.y,rect.w,rect.h);
}

int main(int argc, char *args[])
{
/*	Possibly support command line options...	*/
	printf("Use arrow keys to move\n");
	printf("Press Tab to switch characters\n");
	printf("Press F2 to toggle debugging modes \n");
	printf("Press F11 to toggle Fullscreen \n\n");
	
	Engine engine;
	if (engine.init() == false) {return -1;}
	//Game::Init(); //This would be used to inject content that the engine and menu can use.
	engine.setMenuBackground( "grass" );		//put into a menu loop ---> and menu class
//	engine.menu_loop();
	Pog pog;
	Player pirate( "pirate", 40, 60 );
	//Player monster( "monster", 40, 60 );
	engine.addPlayer(pog);
	engine.addPlayer(pirate);
	//engine.addPlayer(monster);
	
	std::cout << timestamp() << "[Client] Created player types successfully.\n";
	std::cout << timestamp() << "[Client] Entering main game loop.\n";
	
	engine.game_loop();		//----> menu_loop() + game_loop()
	
	SDL_Quit();
	return 0;
}
