/**     ______________________________________
       /  _______    _______    ________     /\
      /	 / ___  /\  / ___  /\  / ______/\   / /\
     / 	/ /__/ / / / /  / / / / /\_____\/  / / /
    /  / _____/ / / /  / / / / / /        / / /
   /  / /\____\/ / /__/ / / / /_/___     / / /
  /  /_/ /      /______/ / /_______/\   / / /
 /   \_\/       \______\/  \_______\/  / / /
/_____________________________________/ / /
\_____________________________________\/ /
 \_____________________________________\/

**/

#ifndef _ENGINE_PLAYER_H
#define _ENGINE_PLAYER_H

#include "object.h"
#include "character.h"

/** The goal is to not hard code players(items, monsters, blocks too) in C++,
 *  but provide functionality to build content in a scripting language that
 *  would be loaded on start-up. The server would manage the mods, and send
 *  data(images, sound, etc) to the client. The client shouldn't know anything
 * 	about the mods, but the engine should still be able to handle it.
 **/

enum PlayerType
{
	PIRATE = 1,
	NINJA,
	SAMURAI,
	MILITARY
};

class Player : public Character
{
	friend class Engine;
	private:
		Uint id;
		PlayerType type;
		void ID(Uint ID);
				
	public:
		Player();
		Player( std::string filename, int width, int height );

		void setType( const PlayerType& type );
		
		Uint ID();
		const PlayerType& getType();
};

///////////////////////////
///	Definition of POG	///
///////////////////////////
/**	This is precisely the type of code that needs to be in a script.
 * 	What if you want to fine tune the animation speed?
 * 		You would need to tweak..compile...test...tweak...compile...etc
 * 
 * 	Objects need two core functions that can be redefined.
 * 		update()
 * 		draw()
 * 	More Complex objects have Components....Can you modify code of a
 * 	component or derive a class in a script. This will need to be answered
 * 	soon.
 * 
 * 	...I guess there should be a ComponentManager
 * 	
 **/
class Pog : public Player
{
	private:
		
	public:
		Pog()
		{
			name = "pog";
			box.w = 47;
			box.h = 51;
			SDL_Rect frame = {0,0,47,51};
			animation.add( "left", "pog", NULL, frame, 1/*, 0	/*optional defaultFrame*/);
			frame.y += box.h;
			animation.add( "right", "pog", NULL, frame, 1 );
			frame.y += box.h;
			animation.add( "up", "pog", NULL, frame, 1 );
			frame.y += box.h;
			animation.add( "down", "pog", NULL, frame, 1 );
			frame.y += box.h;
			animation.add( "up-left", "pog", NULL, frame, 1 );
			frame.y += box.h;
			animation.add( "up-right", "pog", NULL, frame, 1 );
			frame.y += box.h;
			animation.add( "down-left", "pog", NULL, frame, 1 );
			frame.y += box.h;
			animation.add( "down-right", "pog", NULL, frame, 1 );
		}
};

#endif
