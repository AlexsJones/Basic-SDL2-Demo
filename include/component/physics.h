#ifndef _ENGINE_COMPONENT_PHYSICS_H
#define _ENGINE_COMPONENT_PHYSICS_H

#include "timer.h"
#include "component/component.h"

#include "SDL2/SDL_rect.h"

struct fPoint{ float x; float y; };

namespace Component {

class Physics : public Component {
private:
	fPoint pos;
	float velocity;
	fPoint vel;
	SDL_Point acc;
	float accstep;
	float deaccstep;
	
	Interval<Uint32> timestep;
	
public:
	Physics();
	void update(Object& object, const double& dt) override;
};


}//end namespace Component

#endif

