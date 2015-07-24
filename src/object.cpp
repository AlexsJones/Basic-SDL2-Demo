
#include "object.h"
#include "macro.h"
#include "SDL2/SDL_keycode.h"


Object::Object()
	: ACTION(0), physics()
{
	Actions ={ {"left",0}, {"right",0}, {"up",0}, {"down",0},
			   {"attack",0}, {"attack2",0}, {"jump",0}, {"dead",0} };
	box.x = box.y = 0;
	oldbox = box;
}

void Object::update(const double& dt) {
	oldbox = box;
	for (auto& comp : components) {
		//comp->update(engine, *this);
	}
	physics.update(*this, dt);
	animation.update(*this, dt);
}


void Object::move(SDL_KeyboardEvent& keyevent) {
	// KeyDown: Turn on Action
	if (keyevent.type == SDL_KEYDOWN) {
		switch (keyevent.keysym.sym) {
			case SDLK_LEFT: 	ACTION |= LEFT;			break;
			case SDLK_RIGHT:	ACTION |= RIGHT;		break;
			case SDLK_UP: 		ACTION |= UP;			break;
			case SDLK_DOWN: 	ACTION |= DOWN; 		break;
			default: break;
		}
	}
	// KeyUp: Turn off Action 
	if (keyevent.type == SDL_KEYUP) {
		switch (keyevent.keysym.sym) {
			case SDLK_LEFT: 	ACTION &= ~LEFT;		break;
			case SDLK_RIGHT:	ACTION &= ~RIGHT;		break;
			case SDLK_UP: 		ACTION &= ~UP;			break;
			case SDLK_DOWN: 	ACTION &= ~DOWN; 		break;
			default: break;
		}
	}
}


