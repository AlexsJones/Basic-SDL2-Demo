
#include "engine.h"

/**	TODO: Add an operator[] or function to setup which player actions belong
 *	to which animation.sprite[box]. This would give us the ability to:
 * 	1. Allow certain animations to have long/shorter frames.
 * 	2. Allow the spritesheet to be completely customized for custom
 * 		actions(as long as the player can be configured that way).
 * 
 *	NOTE: Internally animation/frame 1 is actually 0.
 * 		ex. Animation.set(1) ---> actually sets animation to 0.
 *		Because of this change there may be some bugs hiding in here. 
 *	
**/
/////////////////////////////////////////////////////
/// Animation ///
/////////////////////////////////////////////////////
Animation::Animation()
	:locked(false), frames(0), animations(0), currentFrame(0),
		currentAnimation(0), timeref(0)
{
	image.x = image.y = 0;
	image.w = image.h = 0;
	speed = 50;
	defaultFrame = 2;						//should be 2 for pirate
	reverseAnimate = false;
}

Animation::Animation(std::string imagefile, int w, int h){
	Animation();
	create(imagefile, w, h);
}

void Animation::create(std::string imagefile, int w, int h)
{
	if (locked){return;}
	image = Engine::getImageSheetDimensions(imagefile);

	if (image.w % w || image.h % h){	//if there are remainding pixels
		printf("Warning:: Invalid Size: %s [%d x %d] \n", imagefile.c_str(), w, h);
		printf("	  Does not fit cleanly inside sprite-sheet.\n\n");
	}
	
	frames = image.w  / w;
	animations = image.h / h;
	if ( !frames ){ frames = 1; }
	if ( !animations ){ animations = 1; }
//	printf("%d,%d",frames,animations);
	for (Uint rowIndex = 0; rowIndex < animations; rowIndex++){
		for (Uint columnIndex = 0; columnIndex < frames; columnIndex++){
			sprites.push_back( Engine::setClip( NULL, columnIndex*w, rowIndex*h, w, h ) );
		}
	}
	locked = true;
}

void Animation::animate()
{
	if( Timer::updateInterval(speed, timeref) )
	{
		if (!reverseAnimate && currentFrame < frames)
		{
			currentFrame++;
			if (currentFrame >= frames){
				if (frames == 1 || frames == 2) currentFrame = 0;
				else { reverseAnimate = true; currentFrame--; }
			}
		}
		if( reverseAnimate ) { currentFrame--; }
		if( reverseAnimate && currentFrame<=0 ) { reverseAnimate = false; }
	}
}

void Animation::animate(int ACTION)
{
	if (hasFlag(ACTION, LEFT))	{ set( 1 ); }
	if (hasFlag(ACTION, RIGHT))	{ set( 2 ); }
	if (hasFlag(ACTION, UP))	{ set( 3 ); }
	if (hasFlag(ACTION, DOWN))	{ set( 4 ); }
//	Diagonals
	if (hasFlag(ACTION, (UP + LEFT)))	{ set( 5 ); }
	if (hasFlag(ACTION, (UP + RIGHT)))	{ set( 6 ); }
	if (hasFlag(ACTION, (DOWN + LEFT))) { set( 7 ); }
	if (hasFlag(ACTION, (DOWN + RIGHT))){ set( 8 ); }
	animate();
};

void Animation::setSpeed(Uint speed){
	this->speed = speed;
}

void Animation::set(Uint nAnimation){
	if (nAnimation > animations)	//if animation is higher than whats available
		return;						//don't change animation
	if (nAnimation <= 0)			//AnimationZero doesn't exist anymore
		return;
	else currentAnimation = --nAnimation;
}

void Animation::setDefault(Uint nFrame){
	if (nFrame > frames || frames <= 1)
		return;
	else defaultFrame = --nFrame;
}

void Animation::setToDefault(){
	currentFrame = defaultFrame;
	if (currentFrame >= frames)
		currentFrame = 0;
	reverseAnimate = false;
}


/** The following are used to get state of the animation.
 * 	The Player class calls this every time the engine requests the 'image'
 * 	from the player through the getImage().
 * 	Example:
 * 	class Frog{
 *		private: Animation animstate;
 * 		pucblic:const SDL_Rect& update(){animstate();}
 * 	}
 * 	"Frog.update();" will return a clip from the spritesheet to render.
**/ 
const SDL_Rect& Animation::get(Uint nAnimation, Uint nFrame)
{
	if( nAnimation < animations && nFrame < frames )
	{
		currentAnimation = nAnimation;
		currentFrame = nFrame;
		return sprites[( nAnimation * (frames) + nFrame )];
	}
	
	if ( nAnimation > animations && nFrame < frames )
		return sprites[( (animations - 1) * (frames) + nFrame )];
	if ( nAnimation < animations && nFrame > frames )
		return sprites[( nAnimation * (frames) + nFrame-1)];
	return sprites[0];
}

const SDL_Rect& Animation::operator()(){
	return get(currentAnimation, currentFrame );
}
