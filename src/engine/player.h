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
 * 	about the mods, but the engine should still be able designed to handle it.
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
		Uint ID;
		PlayerType type;
		void setID(Uint ID){ this->ID = ID; }
		
	public:
		Player();
		Player( std::string filename, int width, int height );

		void setType( const PlayerType& type );
		
		const PlayerType& getType();
//		SDL_Texture* getImage();
};
#endif
