#include <iostream>
#include <ctime>
#include <sstream>
#include "engine.h"

/**TODO::create a game(or Client) class that interfaces with the engine.
 * 
 * 	namespace Pog{ class Engine; class Window;}
 * 
 * 	Possibly have different streams:[Client|Server|Info] That go through
 * 	a stream which timestamps them. Need some kind of system for this.
**/

std::string timestamp()
{
	std::ostringstream stream;   
	time_t rawtime;
	tm * timeinfo;

	time(&rawtime);
	timeinfo = localtime( &rawtime );
	//std::cout << asctime(timeinfo) << "\n";
	
	//Month
	//(timeinfo->tm_mon < 10) ? stream <<"0"<<timeinfo->tm_mon+1 : stream <<timeinfo->tm_mon+1;
	//Day
	//(timeinfo->tm_mday < 10) ? stream <<"0"<<timeinfo->tm_mday : stream <<timeinfo->tm_mday;
	//Year
	//stream << (timeinfo->tm_year)+1900;
	//stream << ":: ";
	//Hour
	(timeinfo->tm_hour < 10) ? stream <<"0"<<timeinfo->tm_hour : stream <<timeinfo->tm_hour;
	stream << ":";
	//Minutes
	(timeinfo->tm_min < 10) ? stream <<"0"<<timeinfo->tm_min : stream <<timeinfo->tm_min;
	//Seconds
	stream << ":" << timeinfo->tm_sec << ":: "; //Ex:: << timestamp() << [Client] Recieved World List from Server."
	
	//stream 	<<"0"<<timeinfo->tm_hour
			//<<":"<<timeinfo->tm_min<<":"<<timeinfo->tm_sec;
	return stream.str(); //return the stream as a sting
}

int main(int argc, char *args[])
{
	printf("Use arrow keys to move\n");
	printf("Press Tab to switch characters\n");
	printf("Press F2 to toggle debugging modes \n");
	printf("Press F11 to toggle Fullscreen \n\n");
	
	Engine engine;
	if (engine.init() == false) {return -1;}
	//Game::Init(); //This would be used to inject content that the engine and menu can use.
	engine.setMenuBackground( "grass" );		//put into a menu loop ---> and menu class
//	engine.menu_loop();
	engine.addPlayer("pirate");
	engine.addPlayer("monster");
	engine.addPlayer("monster");
	
	std::cout << timestamp() << "\n";
	
	engine.game_loop();		//----> menu_loop() + game_loop()
	
	SDL_Quit();
	return 0;
}
