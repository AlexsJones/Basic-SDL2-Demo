#ifndef _ENGINE_OBJECT_H
#define _ENGINE_OBJECT_H

#include "animation.h"

enum ObjectType //TODO:Get rid of this.
{	
	NONE 		= 0x00,
	ITEM 		= 0x01,
	BLOCK		= 0x02,
	CHARACTER 	= 0x03
	//PLAYER
};

class iObject
{
	protected:
		SDL_Rect box;
	public:
		iObject() {box.x = box.y = box.w = box.h = 0;}
		virtual void update() { }
		inline const SDL_Rect& getBox(){ return box; }
};
class Object : public iObject
{
	public:
		Uint8 id;
		std::string name;
		ObjectType objectType;
		
		Object() : objectType(NONE){}
		Object(ObjectType type) : objectType(type){}
//		virtual void draw() { }
		
		inline Uint8 ID(){return id;}
		inline void resize(Uint w, Uint h){box.w = w; box.h = h;}
		
	/* Needed for the engine to sort the objects for rendering.	*/
		inline bool operator<(const Object cObject) const { return box.y + box.h < cObject.box.y + cObject.box.h; }
		~Object(){}
};

class SimpleAnimatedObject: public Object
{
	protected:
		sAnimation animation; //single animation.
	public:
		SimpleAnimatedObject(ObjectType type) : Object(type){}
		virtual void animate(){ }
		inline const SDL_Rect &getImage(){ return animation(); }
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
