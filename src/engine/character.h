#ifndef _ENGINE_CHARACTER_H
#define _ENGINE_CHARACTER_H

#include <map>
#include <string>


#include "component/position.h"
#include "component/animation.h"
#include "component/physics.h"
#include "object.h"

namespace Component { class Input; }

class Character : public Object
{
/**	Should be CharacterTemplate?? -> Overload the
 * constructor(or create()) function to setup the components.
**/
	protected:
	//	std::vector<Component> components
		
	//MovementComponent movement;
		Uint8 ACTION;
	/*	The Future, or have a dedicated structure?	*/
		std::map< std::string, bool > Actions;

		Component::Position position;
			SDL_Rect oldbox;			//put into position, along with box
		Component::Physics physics;		
		Component::Animation animation;
		Component::Input* input; //Engine Assigns Player1 controls?
		
	//UpdateComponent??	//Could be used for managing which Components update when.	
	//--->Going into PhysicsComponent
//		float timeref;
//		float timestep;
	
	//CharacterComponent?
		float damage;
		float health;
	public:
		Character();
		Character(Component::Input* input);
		void TestActions();
		void move(SDL_KeyboardEvent& keyevent);
		void moveTo();
		void update();
		void update(int acc);
		
/* Don't need animate() anymore. Instead objects will get a draw() function
 * so they can handle their own rendering. */
		void animate(){}
		void draw(){}

		inline float getMaxVelocity(){ return physics.Velocity(); }
		inline void switchInput(Component::Input* input){ this->input = input; }
		
//		virtual void setType( const CharacterType& type );

		inline const SDL_Rect &getImage(){ return animation(); }
//		inline const SDL_Rect& getBox(){ return box; }
		~Character(){}

};

#endif
