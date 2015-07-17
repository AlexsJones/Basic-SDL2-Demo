#ifndef _ENGINE_CHARACTER_H
#define _ENGINE_CHARACTER_H

#include <map>
#include <string>


#include "component/position.h"
#include "component/animation.h"
#include "component/physics.h"
#include "object.h"

//#include "component/input.h"
namespace Component { class Input; }

class Character : public Object
{
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
		Component::Input* input; //Engine Assigns Player1 controls*?
		
		//CharacterComponent?
		float damage;
		float health;
	public:
		Character();
		Character(Component::Input* input);
		bool TestActions(std::string action);
		void move(SDL_KeyboardEvent& keyevent);
		void moveTo();
		void update();
		void update(int acc);
		
		void animate(){}
		void draw(){}

		inline float getMaxVelocity(){ return physics.Velocity(); }
		inline void switchInput(Component::Input* input){ this->input = input; }
		
//		virtual void setType( const CharacterType& type );

		inline const SDL_Rect &getImage(){
			return animation();
		}
		
//		inline const SDL_Rect& getBox(){ return box; }
		~Character(){}

};

#endif
