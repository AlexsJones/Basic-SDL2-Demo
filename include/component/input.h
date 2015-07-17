#ifndef _ENGINE_COMPONENT_INPUT_H
#define _ENGINE_COMPONENT_INPUT_H

#include "component/component.h"

#include <string>
#include <vector>
#include "SDL2/SDL_keycode.h"

struct KeyBinding
{
	SDL_Keycode key;
	std::string action;
	//SDL_Modstate	//modifier?
	//function?
};

/*	std::map< std::string, std::list<SDL_Keycode> > GameEventPrimitives;
	or
	GameEventPrimitives.push_back("left", SDLK_LEFT)
	animation("left"), move("left")
	struct GameEventPrimitive{std::string id; std::list<SDL_Keycode>}
*/

namespace Component{
class Input : public Component::iComponent
{
	private:
	/*	Refer to Notes:Game:Input, sorry my notes are currently private^ ;)	*/
//		static std::vector<Input>* inputComponents;	//No...wait..what?
		std::vector<KeyBinding> keyBindings;		//No...
	public:
		Input();
		void update();
		void update(int ACTION);		//	For Character input
		void checkFor(SDL_Keycode key);
};
}
/*	Component namespace END	*/
#endif
