
#include "character.h"
#include "macro.h"

#include "SDL2/SDL_keycode.h"
Character::Character()
	 :Object(CHARACTER), ACTION(0), physics()
{
	Actions ={ {"left",0}, {"right",0}, {"up",0}, {"down",0},
			   {"attack",0}, {"attack2",0}, {"jump",0}, {"dead",0} };
	box.x = 0;
	box.y = 0;
	oldbox = box;
}
bool Character::TestActions(std::string action)
{
/*	for (auto x: Actions)
	{
		if ( (x.second) )	//If the value is true
		{
			printf("'[%s]' is enabled in custom actions\n",x.first.c_str());
		}
	}*/
	return Actions[action];
}

//Character(const InputComponent& input)
Character::Character( Component::Input* input )
	:Object(CHARACTER), ACTION(0), physics()
{
	Character();
	this->input = input;
}

//	Character.update( [event/message] )
void Character::move(SDL_KeyboardEvent& keyevent)
{
	if (keyevent.type == SDL_KEYDOWN)	//Turn on Action
	{
		switch (keyevent.keysym.sym)
		{
			case SDLK_LEFT: 	ACTION |= LEFT;			break;
			case SDLK_RIGHT:	ACTION |= RIGHT;		break;
			case SDLK_UP: 		ACTION |= UP;			break;
			case SDLK_DOWN: 	ACTION |= DOWN; 		break;
			default: break;
		}
	}
	if (keyevent.type == SDL_KEYUP)		//Turn off Action
	{
		switch (keyevent.keysym.sym)
		{
			case SDLK_LEFT: 	ACTION &= ~LEFT;		break;
			case SDLK_RIGHT:	ACTION &= ~RIGHT;		break;
			case SDLK_UP: 		ACTION &= ~UP;			break;
			case SDLK_DOWN: 	ACTION &= ~DOWN; 		break;
			default: break;
		}
	}

}


void Character::update()
{
	oldbox = box;
	//box = physics.update( ACTION, box );
	physics.update( ACTION, box );
	position.update();
	//input->update();

	if( ACTION && (oldbox.x != box.x || oldbox.y != box.y) ){
	//if (true) {
		animation.update( ACTION /*& RIGHT*/ );
//		printf("ACTION = %d\n",ACTION);
	} else {
		animation.setToDefaultFrame();
	}
}


