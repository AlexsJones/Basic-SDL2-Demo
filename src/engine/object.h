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

#ifndef _ENGINE_OBJECT_H
#define _ENGINE_OBJECT_H

#include "animation.h"
#include "component.h"

/**	TODO: Need method for objects to effect each other.
 * 		Objects could have a clip type
 * 			or
 * 		Object could have a function that another object triggers 
 *	
**/
 
enum ObjectType //update to 'enum class'?
{	
	NONE 		= 0x00,
	ITEM 		= 0x01,
	BLOCK		= 0x02,
	CHARACTER 	= 0x03
	//PLAYER?
};

class iObject
{
	protected:
		SDL_Rect box;
	public:
		iObject() {box.x = box.y = box.w = box.h = 0;}
		virtual void update() { }
		const SDL_Rect& getBox(){ return box; }
};
class Object : public iObject
{
	public: //Public because engine currently access ID directly.
		Uint8 ID;
		std::string name;
		ObjectType objectType;
		
		Object() : objectType(NONE){}
		Object(ObjectType type) : objectType(type){}
		void resize(Uint w, Uint h){box.w = w; box.h = h;}
		
		// Needed for the engine to sort the objects for rendering. Could also be used as a Z index?
		bool operator<(const Object cObject) const { return box.y + box.h < cObject.box.y + cObject.box.h; }
		~Object(){}
};

class SimpleAnimatedObject: public Object
{
	protected:
		Animation animation; //single animation.
	public:
		SimpleAnimatedObject(ObjectType type) : Object(type){}
		virtual void animate(){ }
		const SDL_Rect &getImage(){ return animation(); }
};

class AnimatedObject: public Object
{
	protected:
		AnimationComponent animation; //multiple Animations
	public:
		AnimatedObject(ObjectType type) : Object(type){}
		virtual void animate(){ }
		const SDL_Rect &getImage(){ return animation(); }
};

class Item : public Object
{
	public:
		Item() : Object(ITEM) {}
};

class Block : public Object
{
	public:
		Block() : Object(BLOCK){}
};
#endif
