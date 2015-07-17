#ifndef _ENGINE_PLAYER_H
#define _ENGINE_PLAYER_H

#include <string>
#include "SDL2/SDL_rect.h"

#include "character.h"


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

/**	This is the type of code that needs to be in a script. **/
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
