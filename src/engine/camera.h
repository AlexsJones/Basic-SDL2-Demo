#ifndef _ENGINE_CAMERA_H
#define _ENGINE_CAMERA_H

#include "object.h"

#include "SDL2/SDL_rect.h"

/** Currently, the camera is set up to center itself over the player until
 *  it hits the map edge. If the map is smaller than the camera on a given
 *  axis, the camera will be centered over the map on that axis.
 *  
 *  Possible TODOs:
 *    camera movement has inertia
 *    ability to follow multiple players
 *    zooming in-and-out.
 *    ability to follow a path
 *    give the Engine a default camera, which receives input
 *        if nothing else is added.
 */

class Camera : public iObject
{
		SDL_Rect bounds;			//make a weak pointer
		Object* followedObject;		//make a weak pointer
		bool active;
	public:
		Camera() :active(false)
		{
			box.w = box.h = 0;
			box.x = -(box.w/2);
			box.y = -(box.h/2);
			bounds.x = bounds.y = bounds.w = bounds.h = 0;
		}
		
		inline void setBounds( SDL_Rect newBounds ){
			this->bounds = newBounds;
		}
		inline void follow( Object* newObject ){
			this->followedObject = newObject;
			active = true;
		}
		inline Object* getFocus()
		{
			return followedObject;
		}
		void resize( SDL_Rect window ){
			box.w = window.w;
			box.h = window.h;
		}
		inline void update()
		{
			if ( active && followedObject )
			{
			/*	Since the camera's position is based on an object, update()
			 * 	the object first.
			 */	
				followedObject->update();
				SDL_Rect objectBox;
				objectBox = followedObject->getBox();
			/*	Center camera over player.	*/
				box.x = (objectBox.x + (objectBox.w / 2)) - (box.w / 2);
				box.y = (objectBox.y + (objectBox.h / 2)) - (box.h / 2);

			/*	if camera is close to map edge.	*/
				Map::keepInBounds(box, bounds);
				
			/*	If the map is smaller than camera. Center the camera over the map.	*/       
				if (bounds.w < box.w){ box.x = bounds.x + (bounds.w / 2) - (box.w / 2); }
				if (bounds.h < box.h){ box.y = bounds.y + (bounds.h / 2) - (box.h / 2); }	
			}
		}
		
		inline void detach(){
			followedObject = NULL;
			active = false;
		}
				
		inline const bool& isActive(){ return active; }

};
#endif
