
#include "component/input.h"
Component::Input::Input()
{
/*	This code allows the InputComponent to be a manager of itself. It maintains
 * 	a list of all InputComponents and adds itself when it is created.
	if (!inputComponents) inputComponents = new std::vector<Input>;
	inputComponents->push_back(*this);
*/
}

void Component::Input::update()
{
	
}
	
void Component::Input::checkFor(SDL_Keycode keycode)
{
	for(std::vector<KeyBinding>::iterator itr = keyBindings.begin(); itr != keyBindings.end(); itr++)
	{
		if(itr->key == keycode){}//movement->move(itr.action)
	}
}
