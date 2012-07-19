#ifndef _ENGINE_COMPONENT_PHYSICS_H
#define _ENGINE_COMPONENT_PHYSICS_H

#include "timer.h"
#include "component/component.h"

#include "SDL2/SDL_rect.h"

struct fPoint{
	float x; float y;
};

//base PhysicsComponent on PoisitionComponent??
namespace Component
{
class Physics : public Component::iComponent
{
	private:
		fPoint pos;
		float velocity;
		fPoint vel;
		SDL_Point acc;
		float accstep;
		float deaccstep;
		
		Interval timestep;
		
	public:
		Physics();
		inline float Velocity(){ return velocity; }
		void update();
		void update(Uint8& ACTION, SDL_Rect& box);
};
}
/*	Component namespace END	*/
#endif
