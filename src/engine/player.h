#ifndef _ENGINE_PLAYER_H
#define _ENGINE_PLAYER_H

#include <string>
#include "SDL2/SDL_rect.h"

#include "character.h"

/** The goal is to make a game engine that is data driven and dynamically
 * 	creates the content for the game based on scripts.
 * 
 * 	This can be done if player has it's own CollisionComponent. The 
 * 	interface for this component should be able to interact with other
 * 	collision components, maybe through a CollisonComponentManager.
 * 
 * 	Have a previously stored, good position that changes everytime the
 * 	player moves. If he moves into a wall it will restore his x position 
 * 	to the previously known good position, for example. It would need to
 * 	tell physics to hinder the player's x-axis velocity.
 * 
 * 	Need separate box for collisions. 
 *  Possibly AABBox collision detection.
 * 
 * 
 *  A_LEFT
 * 	A_ATTACK
 * 
 * 	S_STEP
 * 	S_ATTACK
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
//		PlayerType type;
		inline void ID(Uint ID){ id = ID; }
				
	public:
		Player();
		Player( std::string filename, int width, int height );

		inline Uint ID(){ return id; }
		
//		inline void setType( const PlayerType& type ){ this->type = type; }
//		inline const PlayerType& getType(){ return type; }	
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
			animation.add( "left", "pog", NULL, frame, 1 );
/*	Should there be a function to assign all frames from one image
 *	to multiple Animations, or even one Animation (with modification).
 * 	There should be a 2d array that specifies a sprite structure.
 */
			frame.y += frame.h;
			animation.add( "right", "pog", NULL, frame, 1 );
			frame.y += frame.h;
			animation.add( "up", "pog", NULL, frame, 1 );
			frame.y += frame.h;
			animation.add( "down", "pog", NULL, frame, 1 );
			frame.y += frame.h;
			animation.add( "up-left", "pog", NULL, frame, 1 );
			frame.y += frame.h;
			animation.add( "up-right", "pog", NULL, frame, 1 );
			frame.y += frame.h;
			animation.add( "down-left", "pog", NULL, frame, 1 );
			frame.y += frame.h;
			animation.add( "down-right", "pog", NULL, frame, 1 );
		}
};

#endif
