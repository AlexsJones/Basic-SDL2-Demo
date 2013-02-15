#ifndef _ENGINE_COMPONENT_ANIMATION_H
#define _ENGINE_COMPONENT_ANIMATION_H

#include "component/component.h"
#include "../animation.h"
#include "SDL2/SDL_rect.h"
#include <vector>

namespace Component{

class Animation : public Component::iComponent
{
	private:
		std::vector<sAnimation> animations;	//Should this be a map<Animation, std::string>
		int currentAnimation;
		SDL_Rect oldBox;
	//TODO:
		int defaultAnimationLeft;
		int defaultAnimationRight;
		int defaultAnimationUp;
		int defaultAnimationDown;
		
		
	public:
		Animation();
		void update(){};
		void update(Uint8 ACTION);
		//void animate(int);
		
		void add( std::string id, std::string imagefile, SDL_Rect* image, SDL_Rect frame, int frames, int defaultFrame=0 );
		
		void set(Uint animation); 			//	and Engine action-primitve?
		void set(std::string animation);
		void setToDefaultFrame();
		
		void setDefaultFrame( Uint nAnimation, Uint nFrame );
				
		const SDL_Rect& get(Uint nAnimation);
		inline const SDL_Rect& operator()(){ return get(currentAnimation); }
};

}
/*	Component namespace END	*/
#endif
