#ifndef _ENGINE_ANIMATION_H
#define _ENGINE_ANIMATION_H

#include "timer.h"

#include "SDL2/SDL_image.h"
#include <string>
#include <vector>

typedef unsigned int Uint;

/**	Sprite has a source image and a sequence of frames. It stores how many frames
 * 	it has. Animation has one sprite. It stores the position, animation speed, etc
 * 	in order to animate the sprite.
**/
class Image{};//dummy
class Sprite	//Currently un-used
{
private:
	std::string id;	//Not the image id, but an animation id?  walk_right
//	SDL_Rect image;
	Image image;	//Size and position of square inside the actual image represented by its ID
	std::vector<Image> frames;
public:
};

//  sAnimation was changed because there was a naming conflict within
//  Component::Animation. Once there is a gamespace or something, it
//	will be reverted or changed to something better.
class sAnimation
{
protected:
	std::string id;

	bool locked;
	std::vector<SDL_Rect> frames;	//sequence of frames
	Interval<Uint32> speed;
	
	Uint currentFrame;
	Uint defaultFrame;
	
	bool reverseAnimate;
//		bool loop;						//Does the animation loop, or just play and start from begining
	
public:
	sAnimation();
	sAnimation(std::string imagefile, int w, int h);
	inline void ID(std::string id){ this->id = id; }
	inline std::string ID(){ return id; }
//		void create( std::string id, std::string imagefile, SDL_Rect* image, SDL_Rect frame, int frames, int defaultFrame );
	void add(SDL_Rect frame);
	
	void animate();

	void setSpeed(int speed);
	void setDefault(Uint nFrame);
	void setToDefault();
	
	inline const SDL_Rect& get(){ return get(currentFrame); }
	const SDL_Rect& get(Uint nFrame);
	const SDL_Rect& operator()(Uint nFrame);
	inline const SDL_Rect& operator()(){ return get(currentFrame); }
};

#endif