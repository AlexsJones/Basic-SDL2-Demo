
#include "animation.h"
#include "macro.h"

class Engine{ public:static SDL_Rect getImageSheetDimensions(std::string); static SDL_Rect setClip( SDL_Texture*, int, int, int, int );
};

/**	Each Animation should have frame zero return a box{0,0,0,0} so characters
 * 	or players that are not setup, don't cause the program to crash when
 * 	they are instantiated. This will make animation/frame 1 to be 1 and frame 
 * 	zero to be zeroes(blank).
**/

sAnimation::sAnimation()
	: id(),locked(false), currentFrame(1)
{
//	frames.reserve(2);
	defaultFrame = 0;
	add( {0,0,0,0} );
	speed.set(65);
	reverseAnimate = false;
}

void sAnimation::add( SDL_Rect frame ){
	frames.push_back( frame );
	if ( defaultFrame == 0 /*&& frames.size() > 1*/ )
	{
		setDefault(1);
	}
}

void sAnimation::animate()
{
	if( speed() )
	{
		if ( frames.size() == 2 ){
			return;
		}
		else if ( !reverseAnimate )
		{
			if ( currentFrame < frames.size() - 1 ){
				currentFrame++;
				if ( frames.size() == 3 ){ currentFrame = 1; }
			} else {
				reverseAnimate = true; currentFrame--;
			}
		}
		else if( reverseAnimate )
		{
			if( currentFrame <= 1 )
				reverseAnimate = false;
			else currentFrame--;
		}
	}
}

void sAnimation::setSpeed( int speed ){
	this->speed = speed;
}

void sAnimation::setDefault( Uint nFrame )
{
/*	If nFrame is more than total frames, let setToDefault() deal
 * 	with it, this is so you	can set the defaultFrame before the frames
 *  are populated.
 */	
	if ( defaultFrame == nFrame || nFrame == 0 ){
		return;
	}else{
		defaultFrame = nFrame;
	}
}

void sAnimation::setToDefault()
{
	if ( !defaultFrame ){ return; }
	if ( defaultFrame < frames.size() ){
	currentFrame = defaultFrame;
	reverseAnimate = false;
	}
}

const SDL_Rect& sAnimation::get( Uint nFrame )
{
	if (nFrame <= 0){
		printf("Warning, requesting blank frame...\n");
		return frames[0];
	}
	if( nFrame < frames.size() )
	{
		currentFrame = nFrame;
		return frames[ currentFrame ];
	}
	
/*	If frame index is too high return the last frame	*/
	if ( nFrame >= frames.size() )
		printf("Warning, requesting a frame index higher than total frames...\n");
		return frames.back();
}
