
#include "component/physics.h"
#include "macro.h"

Component::Physics::Physics()
	:velocity(250.f)
{
	vel.x = vel.y = 0;
	acc.x = acc.y = 0;
	pos.x = pos.y = 0;
	
	timestep.set( 33 );
	
	accstep = 50;
	deaccstep = accstep / 2.0f;
}

void Component::Physics::update()
{}

#include <iostream>

void Component::Physics::update(Uint8& ACTION, SDL_Rect& box)
{
//	update the acceleration and keep within bounds
//	update the velocity using the new acc. and deltaTime
//	add the velocity to the position, and return its value(float).
	if (box.x != (int )pos.x)
		pos.x = box.x;
	if (box.y != (int )pos.y)
		pos.y = box.y;
		
	while ( timestep() ){
		float DT = timestep.get() / 1000.0f;
		if ( vel.x >= 0 ) {
			vel.x -= deaccstep;
			if ( vel.x < 0 ) { vel.x = 0; }
		} else {
			vel.x += deaccstep;
			if ( vel.x > 0 ) { vel.x = 0; }
		}
		if ( vel.y >= 0 ) {
			vel.y -= deaccstep;
			if ( vel.y < 0 ) { vel.y = 0; }
		} else {
			vel.y += deaccstep;
			if ( vel.y > 0 ) { vel.y = 0; }
		}
		
		if (hasFlag(ACTION, LEFT))	{ vel.x -= accstep; }
		if (hasFlag(ACTION, RIGHT))	{ vel.x += accstep; }
		if (hasFlag(ACTION, UP))	{ vel.y -= accstep; }
		if (hasFlag(ACTION, DOWN))	{ vel.y += accstep; }
		
		if (vel.x > velocity) 	vel.x = velocity;
		if (vel.x < -velocity) 	vel.x = -velocity;
		if (vel.y > velocity) 	vel.y = velocity;
		if (vel.y < -velocity) 	vel.y = -velocity;
		pos.x += vel.x * DT;
		pos.y += vel.y * DT;
		box.x = pos.x;
		box.y = pos.y;
	}
	if (!ACTION){ timestep.resetTime(); }
}
