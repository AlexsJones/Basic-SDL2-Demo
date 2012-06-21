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
class Sprite
{
	private:
//		std::string id;
		SDL_Rect image;
		std::vector<SDL_Rect> sprites;  //sequence of frames, contains number of frames: sprites.size()
//		int frames;
	public:
};
class Animation
{
	friend class AnimationComponent;
	protected:
		std::string id;
	
		bool locked;
		std::vector<SDL_Rect> frames;  //sequence of frames
		int speed;
		
		int currentFrame;
		int defaultFrame;
		
		bool reverseAnimate;
		Uint timeref;
		
	public:
		void ID(std::string id);
		Animation();
		Animation(std::string imagefile, int w, int h);
//		void create( std::string id, std::string imagefile, SDL_Rect* image, SDL_Rect frame, int frames, int defaultFrame );
		void add(SDL_Rect frame);
		
		void animate();

		void setSpeed(int speed);
		void setDefault(int nFrame);
		void setToDefault();
		
		const SDL_Rect& get(int nFrame);
		const SDL_Rect& operator()(int nFrame);
		const SDL_Rect& operator()();
};

class AnimationComponent : public Component
{
	private:
		std::vector<Animation> animations;	//Should this be a map<Animation, std::string>
		int currentAnimation;
		SDL_Rect box;
		
	public:
		AnimationComponent();
		void update(){};
		void update(Uint8& ACTION);
		void animate(int);
		
		void add( std::string id, std::string imagefile, SDL_Rect* image, SDL_Rect frame, int frames, int defaultFrame=0 );
		
		void set(Uint animation); 			//	and Engine action-primitve?
		void set(std::string animation);
		void setToDefault();
		
		void setDefaultFrame( Uint nAnimation, Uint nFrame );
				
		const SDL_Rect& get(Uint nAnimation);
		const SDL_Rect& operator()();

};
#endif
