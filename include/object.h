#ifndef _ENGINE_OBJECT_H
#define _ENGINE_OBJECT_H

#include "component/component.h"
#include "component/animation.h"
#include "component/physics.h"

#include <unordered_map>


class Object {
public:
	//std::unordered_map<std::string, Component> components;
	std::vector<Component::Component> components;
	std::unordered_map<std::string, bool> Actions;
	//std::set<std::string> state;
	
	Uint id = 0;
	Uint imageId = 0;
	std::string name;
	
	Uint8 ACTION = 0;
	SDL_Rect box = {0,0,0,0};
	SDL_Rect oldbox = {0,0,0,0};
	Component::Physics physics;		
	Component::Animation animation;
	
	
	Object();
	~Object(){}
	
	virtual void init() { box = {0,0,0,0}; }
	virtual void update( const double& dt );
	virtual void draw() {}
	
	void move(SDL_KeyboardEvent& keyevent);
	void resize(Uint w, Uint h){box.w = w; box.h = h;}
	const SDL_Rect& getImage(){ return animation.get(); }
	const SDL_Rect& getBox(){ return box; }
	
	Uint ID() { return id; }
	Uint ID(Uint ID) { id = ID; return id; }
};


#endif

