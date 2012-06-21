/**     ______________________________________
       /  _______    _______    ________     /\
      /	 / ___  /\  / ___  /\  / ______/\   / /\
     / 	/ /__/ / / / /  / / / / /\_____\/  / / /
    /  / _____/ / / /  / / / / / /        / / /
   /  / /\____\/ / /__/ / / / /_/___     / / /
  /  /_/ /      /______/ / /_______/\   / / /
 /   \_\/       \______\/  \_______\/  / / /
/_____________________________________/ / /
\_____________________________________\/ /
 \_____________________________________\/

**/

#ifndef _ENGINE_CAMERA_H
#define _ENGINE_CAMERA_H


/** Currently, the camera is set up to center itself over the player until
 * 	it hits the map edge. If the map is smaller than the camera on a given
 * 	axis, the camera will be centered over the map on that axis.
 * 
 *	Possible TODOs:
 * 		camera movement has inertia
 * 		ability to follow multiple players
 * 		zooming in-and-out.
 *		ability to follow a path
 * 		if ACTIVE_PLAYER is 0, move the camera as a spectator?
 */

class Camera : public iObject
{
//		SDL_Point offset;
		SDL_Rect map;
		Player* player;
		bool active;
	public:
		Camera() :active(false)
		{
			box.w = box.h = 0;
			box.x = -(box.w/2);
			box.y = -(box.h/2);
			map.x = map.y = map.w = map.h = 0;
			//offset.x = offset.y = 0;
		}
		
		void setMap(SDL_Rect map){
			this->map = map;
		}
		void follow(Player* player){
			//if single player
			this->player = player;
			active = true;
		}
		void resize(SDL_Rect window){
			//SDL_GetWindowSize( window, &box.w, &box.h);
			box.w = window.w;
			box.h = window.h;
		}
		void update()
		{
			if (active && player)
			{
				//Center camera over player.
				box.x = (player->getBox().x + (player->getBox().w / 2)) - (box.w / 2);
				box.y = (player->getBox().y + (player->getBox().h / 2)) - (box.h / 2);

				//if camera is close to map edge
				Map::keepInBounds(box, map);
				
				//If the map is smaller than camera. Center the camera over the map.
				if (map.w < box.w){ box.x = map.x + (map.w / 2) - (box.w / 2); }
				if (map.h < box.h){ box.y = map.y + (map.h / 2) - (box.h / 2); }	
			}
		}
		
		void detach(){
			player = NULL;
			active = false;
		}
				
		const bool& isActive(){ return active; }

};
#endif
