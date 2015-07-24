#ifndef _ENGINE_ANIMATION_H
#define _ENGINE_ANIMATION_H

#include "timer.h"

#include "SDL2/SDL_image.h"
#include <string>
#include <vector>

typedef unsigned int Uint;


class Image{};

// SpriteSheet contains a collection of Frames
class SpriteSheet {
private:
	std::string name;
	//SDL_Rect image;
	Image image;
	std::vector<SDL_Rect> frames;
public:
};

namespace Component { class Animation; } 
class AnimatedSprite {
protected:
friend class Component::Animation;
	std::vector<SDL_Rect> frames;
	// Change to fps;
	Interval<Uint32> speed;
	Uint fps = 45;
	Uint image = 0;
	Uint defaultFrame = 0;
	Uint currentFrame = 0;
	Uint lastUpdate = 0;
	
	bool reverseAnimate = false;
	//bool loop;
	
public:
	AnimatedSprite() { speed = Interval<Uint32>(65); }
	AnimatedSprite(Uint image, SDL_Rect frame, int frames=1, int defaultFrame=0);
	
	void update(const double& dt);
	
	void addFrame(SDL_Rect frame) { frames.push_back( frame ); }
	
	void setImage(Uint image) { if (image) { this->image = image; } }
	
	void setSpeed(int speed) { this->speed = speed; }
	
	void setDefault(Uint nFrame) {
		if ( nFrame >= frames.size() ) { return; } else { defaultFrame = nFrame; }
	}
	
	void setToDefault() {
		if ( !defaultFrame ) { return; }
		if ( defaultFrame < frames.size() ) {
			currentFrame = defaultFrame;
			reverseAnimate = false;
		}
	}
	
	void clearFrames() { frames.clear(); }
	
	const SDL_Rect& getFrame() { return getFrame(currentFrame); }
	
	const SDL_Rect& getFrame(Uint nFrame) {
		thread_local SDL_Rect null = {0,0,0,0};
		if( nFrame < frames.size() ) {
			currentFrame = nFrame;
			return frames[currentFrame];
		}
		return null;
	}
	
	/*
	bool operator==(const AnimatedSprite& rhs) {
		return (image == rhs.image) && (frames == rhs.frames);
	}
	*/
	
	operator bool() { return image && !frames.empty(); }
};


#endif

