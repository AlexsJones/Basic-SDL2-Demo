
#include "component/animation.h"
#include "macro.h"
#include "engine.h"

namespace Component {

Animation::Animation() { animations.push_back(AnimatedSprite()); }


void Animation::update(Object& object, const double& dt) {
	Uint8& ACTION = object.ACTION;
	SDL_Rect box = object.box;
	SDL_Rect oldbox = object.oldbox;
	
	// If has moved, update frame, otherwise set to default/still
	//if ( (oldbox.x == box.x && oldbox.y == box.y) ) {
	if ( !ACTION ) {
		setToDefaultFrame();
		return;
	}
	if (hasFlag(ACTION, LEFT))			{ set( "left" ); 	}
	if (hasFlag(ACTION, RIGHT))			{ set( "right" ); 	}
	if (hasFlag(ACTION, UP))			{ set( "up" ); 		}
	if (hasFlag(ACTION, DOWN))			{ set( "down" );	}
	//	Diagonals
	if (hasFlag(ACTION, (UP + LEFT)))	{ set( "up-left" ); 	}
	if (hasFlag(ACTION, (UP + RIGHT)))	{ set( "up-right" ); 	}
	if (hasFlag(ACTION, (DOWN + LEFT))) { set( "down-left" ); 	}
	if (hasFlag(ACTION, (DOWN + RIGHT))){ set( "down-right" ); 	}
	
	if (current < animations.size()) { animations[current].update(dt); }
}


void Animation::add( std::string animName, AnimatedSprite sprite ) {
	if (!current) { current = 1; }
	animIdByName[animName] = animations.size();
	animations.push_back( sprite );
}

void Animation::set( std::string animName ) {
	Uint id = animIdByName[animName];
	if (id) { current = id; }
}

void Animation::setToDefaultFrame(){
	if (current < animations.size()) { animations[current].setToDefault(); }
}

void Animation::setDefaultFrame( std::string animName, Uint nFrame ) {
	Uint id = animIdByName[animName];
	if (id) { animations[id].setDefault(nFrame); }
}

const SDL_Rect& Animation::get() {
	thread_local SDL_Rect null = {0,0,0,0};
	if (current < animations.size()) { animations[current].getFrame(); }
	else { return null; }
}

const SDL_Rect& Animation::get(std::string animName) {
	return animations[ animIdByName[animName] ].getFrame();
}

}//end namespace Component


