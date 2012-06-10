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

#ifndef _ENGINE_ANIMATION_H
#define _ENGINE_ANIMATION_H
#include <string>
#include <vector>

#include "component.h"
/**	TODO: Include an 'std::initializer_list' for the animation structure.
  * 	
  * 	Need to know where to start reading the file for animation if there
  * 	are multiple animations in one image. This will be held be the animation
  * 	class and implemented by overloading the constructor. Default would
  * 	just be start=0;.
  * 	or	
  * 	The AnimationComponent could calculate a value of it's start cooridinates.
  * 	This would be good if different animations have different sizes.
  */

/**	Sprites has a source image and a sequence of frames. It stores how many frames
 * 	it has. Animation has one sprite. It stores the position, animation speed, etc
 * 	in order to animate the sprite.
 * 
**/
class Animation
{
	private:
		SDL_Rect image;					//size of image
		
		bool locked;
		std::vector<SDL_Rect> sprites;  //sequence of frames
		Uint frames;					//columns
		Uint animations;				//rows
		Uint speed;
		
		Uint currentFrame;
		Uint currentAnimation;
		Uint defaultFrame;
		
		bool reverseAnimate;
		Uint timeref;
		
	public:
		Animation();
		Animation(std::string imagefile, int w, int h);
		void create(std::string imagefile, int w, int h);
		
		void animate();
		void animate(int ACTIONS);
		
		void set(Uint nAnimation);
		void setSpeed(Uint speed);
		void setDefault(Uint nFrame);
		void setToDefault();
		
		const SDL_Rect& get(Uint nAnimation, Uint nFrame);
		const SDL_Rect& operator()(Uint nAnimation, Uint nFrame);
		const SDL_Rect& operator()(Uint nIndex);
		const SDL_Rect& operator()();
};

class AnimationComponent : public Component
{
	private:
		std::vector<Animation> animations; //Should this be a map<Animation, std::string>
	public:
		void update(){};
		void update(int){};
		void set(int animation); //Engine action-primitve
		void set(std::string animation);
		void setToDefault();
		Animation get();
};
#endif
