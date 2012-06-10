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

#ifndef _ENGINE_COMPONENT_COMPONENT_H
#define _ENGINE_COMPONENT_COMPONENT_H


#include <string>
#include <vector>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_keycode.h>

class Component
{
	public:
		virtual void update() = 0;
};

enum Movement //Primitives (very primitive)
{
	LEFT 	= 	1<<1,
	RIGHT 	=	1<<2,
	UP 		=	1<<3,
	DOWN 	=	1<<4,
	ATTACK 	=	1<<5
/**
	UNUSED	=	1<<6
	UNUSED	=	1<<7
	UNUSED	=	1<<8
**/	
};

class MovementComponent : public Component
{
	private:
	public:
		void update();
};


struct fPoint{
	float x; float y;
};
class PhysicsComponent : public Component
{
	private:
		fPoint pos;
		float velocity;
		fPoint vel;
		SDL_Point acc;
		float accstep;
		float deaccstep;
		
		float timeref;
		float timestep;
		
	public:
		PhysicsComponent();
		float Velocity();
		void update();
		void update(unsigned char& ACTION, SDL_Rect& box);
};
class PositionComponent : public Component
{
	private:
	public:
		void update();
};


struct KeyBinding
{
	SDL_Keycode key;
	std::string action;
	//modifier?
};

class InputComponent : public Component
{
	private:
		//static std::vector<Input>* inputComponents;
	/*	InputComponentManager can keep track of all keybindings to match
	 * 	input to the keycodes.
	 *  OR
	 *  Engine assigns the keys to the object's inputcomponent
	 */
		std::vector<KeyBinding> keyBindings;
	public:
		InputComponent();
		void update();
		void update(int ACTION);
		void checkFor(SDL_Keycode key);
};
#endif
