#ifndef _ENGINE_COMPONENT_ANIMATION_H
#define _ENGINE_COMPONENT_ANIMATION_H

#include "component/component.h"
#include "../animated_sprite.h"

#include "SDL2/SDL_rect.h"
#include <vector>
#include <unordered_map>

class Object;

namespace Component {

class Animation : public Component {
private:
	std::vector<AnimatedSprite> animations;
	std::unordered_map<std::string, Uint> animIdByName;
	Uint current = 0;
	
public:
	Animation();
	void update(Object& object, const double& dt) override;
	void add(std::string animName, AnimatedSprite sprite);
	void set(std::string animName);
	void setToDefaultFrame();
	void setDefaultFrame(std::string animName, Uint nFrame);
	const SDL_Rect& get();
	const SDL_Rect& get(std::string animName);
};

}//end namespace Component

#endif

