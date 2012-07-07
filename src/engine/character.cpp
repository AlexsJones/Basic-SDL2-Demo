
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
void Character::TestActions()
{
	for (auto x: Actions)
	{
		if ( (x.second) )	//If the value is true
		{
			printf("'[%s]' is enabled in custom actions\n",x.first.c_str());
		}
	}
}

//Character(const InputComponent& input)
Character::Character( Component::Input* input )
	:Object(CHARACTER), ACTION(0), physics()
{
	Character();
	this->input = input;
}

///#### Keyboard Input ####
//	Character.update( [event/message] ) //Signals/Slots instead??
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
///#### End of Key Input ####


void Character::update()
{
//	##TEST
/**	SEG FAULTS  (I think it is an error with SDL2)
	Uint8* state = SDL_GetKeyboardState(NULL);
			if (state[SDLK_LEFT] == SDL_PRESSED)
				ACTION |= LEFT;
			else ACTION &= LEFT;
			if ( state[SDLK_RIGHT] == SDL_PRESSED)
				ACTION |= RIGHT;
			else ACTION &= RIGHT;
			if ( state[SDLK_UP] == SDL_PRESSED)
				ACTION |= UP;
			else ACTION &= UP;
			if ( state[SDLK_DOWN] == SDL_PRESSED)
				ACTION |= DOWN;
			else ACTION &= DOWN;
	delete[] state;
**/
//	##END TEST
	
	
	oldbox = box;
	//box = physics.update( ACTION, box );
	physics.update( ACTION, box );
	position.update();	//Position should be part of physics, box(position) should be part of movement
	//input->update();

	if(ACTION || oldbox.x != box.x || oldbox.y != box.y ){
		animation.update( ACTION );
//		printf("ACTION = %d\n",ACTION);
	} else
/*	Possibly have animation speed based on an average amount of pixels moved.
 * 	And have setToDefault() called when he stands still for 2 sec for example
 */
	{ animation.setToDefaultFrame(); }
}
