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

#ifndef _ENGINE_CHARACTER_H
#define _ENGINE_CHARACTER_H

#include "object.h"
#include "component.h"
#include "animation.h"

/** The goal is to not hard code players(items, monsters, blocks too) in C++,
 *  but provide functionality to build content in a scripting language that
 *  would be loaded on start-up. The server would manage the mods, and send
 *  data(images, sound, etc) to the client. The client shouldn't know anything
 * 	about the mods, but the engine should still be able designed to handle it.
 **/

enum MonsterType { };

enum CharacterType { NPC = 0, PLAYER, MONSTER };

//////////////////
/// Character ///
////////////////

class Character : public AnimatedObject
{
/**	Break it UP!!! Into Components =]
 * Should be CharacterTemplate?? -> Overload the
 * constructor(or create()) function to setup the components.
**/
	protected:
		//std::vector<Component> components; //Why would object have a list of its own components? - ComponentManager?
		
	//MovementComponent
		MovementComponent movement;
		Uint8 ACTION;							//This holds the CharacterActions, 8 bit = 8 flags, BUT
		std::map< std::string, bool > Actions;  //THIS may be used instead (holds id and a value)
		SDL_Rect oldbox;
		
	//PhysicsComponent
		PhysicsComponent physics;
			
		PositionComponent position;
//		AnimationComponent animations;	//	NOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
		InputComponent* input; //Engine Assigns Player1 controls?
		
	//UpdateComponent??	//Could be used for managing which Components update when.	
	//--->Going into PhysicsComponent
//		float timeref;
//		float timestep;
	
	//CharacterComponent??	//Similar to multiple inheritance?
		float damage;
		float health;
	public:
		Character();
		Character(InputComponent* input);
		void TestActions();
		void move(SDL_KeyboardEvent& keyevent); //replace key with an ACTION
		void moveTo();
		void update();
		void update(int acc);
		void animate();
		
		float getMaxVelocity();
		//virtual void setType( const CharacterType& type );
		void switchInput(InputComponent* input);
//		const SDL_Rect &getImage();
//		const SDL_Rect& getBox();

};

#endif
