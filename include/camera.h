#ifndef _ENGINE_CAMERA_H
#define _ENGINE_CAMERA_H

#include "object.h"
#include "SDL2/SDL_rect.h"

// Camera centers itself over an Object until it hits the map's edge.
// Note, Camera updates the object it is following before it repositions itself
// over it. This prevents the object from 'wiggling' around on the screen.
// If Camera was updated after, then some Objects which are barely on the screen,
// won't be rendered at all until the next frame. Maybe the solution is to expand
// the camera's box to allow for that.
class Camera : public Object
{
	SDL_Rect bounds;
	// Convert to an Object Id
	Object* followedObject;
	bool active;

public:
	Camera() :active(false)
	{
		box.w = box.h = 0;
		box.x = -(box.w/2);
		box.y = -(box.h/2);
		bounds.x = bounds.y = bounds.w = bounds.h = 0;
	}
	
	void setBounds( SDL_Rect newBounds ) { bounds = newBounds; }
	
	void follow( Object* newObject ) {
		this->followedObject = newObject;
		active = true;
	}
	
	Object* getFocus() { return followedObject; }
	
	void resize( SDL_Rect window ) {
		box.w = window.w;
		box.h = window.h;
	}
	
	void update(const double& dt) override {
		if ( active && followedObject ) {
			followedObject->update(dt);
			SDL_Rect objectBox;
			objectBox = followedObject->getBox();
			// Center camera over object.
			box.x = (objectBox.x + (objectBox.w / 2)) - (box.w / 2);
			box.y = (objectBox.y + (objectBox.h / 2)) - (box.h / 2);

			// Constrain Camera to the Map
			Map::keepInBounds(box, bounds);
			
			// If the map is smaller than camera. Center the camera over the map.     
			if (bounds.w < box.w) { box.x = bounds.x + (bounds.w / 2) - (box.w / 2); }
			if (bounds.h < box.h) { box.y = bounds.y + (bounds.h / 2) - (box.h / 2); }	
		}
	}
	
	void detach() {
		followedObject = NULL;
		active = false;
	}
			
	const bool& isActive(){ return active; }
};

#endif

