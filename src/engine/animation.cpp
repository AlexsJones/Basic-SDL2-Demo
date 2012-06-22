
#include "engine.h"

/**	Each Animation should have frame zero return a box{0,0,0,0} so characters
 * 	or players that are not setup, don't cause the program to crash when
 * 	they are instantiated. This will make animation/frame 1 to be 1 and frame 
 * 	zero to be zeroes(blank).
**/
///////////////////////////
/// 	Animation 		///
///////////////////////////
void Animation::ID( std::string id ){
	this->id = id;
}
std::string Animation::ID( ){
	return id;
}

Animation::Animation()
	: id(),locked(false), currentFrame(1), timeref(0)
{
//	frames.reserve(2);
	add( {0,0,0,0} );
	speed = 65;
	defaultFrame = 1;
	reverseAnimate = false;
}

void Animation::add( SDL_Rect frame ){
	frames.push_back( frame );
}

void Animation::animate()
{
	if( Timer::updateInterval(speed, timeref) )
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

void Animation::setSpeed( int speed ){
	this->speed = speed;
}

void Animation::setDefault( Uint nFrame )
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

void Animation::setToDefault()
{
	if ( defaultFrame < frames.size() ){
	currentFrame = defaultFrame;
	reverseAnimate = false;
	}
}

const SDL_Rect& Animation::get( Uint nFrame )
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
		return frames[ frames.size()-1  ];
}

const SDL_Rect& Animation::operator()(){
	return get( currentFrame );
}

///////////////////////////
///	Animation Component	///
///////////////////////////

AnimationComponent::AnimationComponent()
{	
	box = {0,0,0,0};
	currentAnimation = 0;
	animations.reserve( 8 );
	Animation blankAnimation;
	blankAnimation.add( box );
	blankAnimation.ID("");
	animations.push_back( blankAnimation );
}

//Should ACTION by type-safe?????
void AnimationComponent::update(Uint8& ACTION)
{
	if ( !animations.empty() ){
		if (hasFlag(ACTION, LEFT))			{ set( "left" ); 	set( 1 );}
		if (hasFlag(ACTION, RIGHT))			{ set( "right" ); 	set( 2 ); }
		if (hasFlag(ACTION, UP))			{ set( "up" ); 		set( 3 ); }
		if (hasFlag(ACTION, DOWN))			{ set( "down" ); 	set( 4 ); }
	//	Diagonals
		if (hasFlag(ACTION, (UP + LEFT)))	{ set( "left" ); 	set( 5 );}
		if (hasFlag(ACTION, (UP + RIGHT)))	{ set( "right" ); 	set( 6 ); }
		if (hasFlag(ACTION, (DOWN + LEFT))) { set( "left" ); 	set( 7 );}
		if (hasFlag(ACTION, (DOWN + RIGHT))){ set( "right" ); 	set( 8 );}
		animations[currentAnimation].animate();
	}
}


/*	The function parameters needs to be shorter.
 * 	Maybe pass in a Sprite object, which isn't being used yet.
 * 
 * 	TODO:: This function is also too large. It should be split up into a bunch
 * 	of functions.
 */
void AnimationComponent::add( std::string id, std::string imagefile, SDL_Rect* image, SDL_Rect frame, int frames, int defaultFrame )
{
/*	Get box for the image.If not supplied already.	*/
	if ( !image ){
	SDL_Rect* imageBox = new SDL_Rect;
	*imageBox = Engine::getImageSheetDimensions(imagefile);
	imageBox->x = imageBox->y = 0;
	image = imageBox;
	}

/*	Caluculate the amount of frames that can fit in the space of the image. */
	int framesWide = ( image->w - frame.x ) / frame.w;
	int framesHigh = ( image->h - frame.y ) / frame.h;

	if ( (framesWide * framesHigh) < frames )
		printf("Not enough space inside %s image to create %s animation\n",imagefile.c_str(), id.c_str());

/*	Get the absolute coordinates of the start frame.	*/
/*	This allows the frame to be relative of the image box.	*/
	int startX = frame.x;
	
	frame.x += image->x;
	frame.y += image->y;
	
//	Animation* newAnimation = new Animation;
	Animation newAnimation;
	newAnimation.ID(id);

/*	Just use a Point index.x/y ?	*/
	int rowIndex = 0;
	int columnIndex = 0;
	
/*	Assign the frames to the sprite from the image.	*/
	for (int currentFrame = 0; currentFrame </*=/*if first frame is 1 NOT 0*/ frames; currentFrame++)
	{
/*		If the current frame doesn't fit on the image (x-axis).
 * 		Go to the next line and reset the X cooridinate.	*/
 		if ( (frame.x + (currentFrame * frame.w)) > (image->x + image->w) ){
			frame.y += frame.h;	rowIndex++;
			frame.x = startX;	columnIndex = 0;
			if ( (frame.y + frame.h) > (image->y + image->h) ){
				printf("Warning %s sprite does not fit inside image correctly.\n", id.c_str());
			}
		}
		newAnimation.add( Engine::setClip( NULL,
							frame.x + columnIndex*frame.w, frame.y + rowIndex*frame.h, 
							frame.w, frame.h )	);
		columnIndex++;
	}
	if (defaultFrame > 0 && frames >= defaultFrame){
		newAnimation.setDefault(defaultFrame);
	}
	animations.push_back( newAnimation );
	if ( !currentAnimation ){
		currentAnimation = 1;
	}
}

void AnimationComponent::set( Uint nAnimation ){
	if ( nAnimation < animations.size() ){
		currentAnimation = nAnimation;
	}
}

void AnimationComponent::set( std::string animationID )
{
	for ( auto index: animations)
	{	/*	check if animationID matches any animations[i].id()	*/
		if ( index.ID().c_str() == animationID.c_str() )
		{
			/*	How do I convert the Animation match to number.
			 * 
			 * 	store an int inside the animation as an ID and change
			 * 		std::string id; to std::string action;
			 * 
			 * 	or change:
			 * 	vector<Animation> animations;
			 * 	to:
			 * 	map<Animation, std::string> animations;
			 * 
			 * 	This should be done for the Engine too with its list of Players.
			 * 	The Player has an ID which the Engine assigns on creation.
			 * 
			 * 	If I don't use the 'auto' keyword I might be able to have a 
			 * 	counter to get the right animation number.
			 * 	
			 */
			//currentAnimation = index...;
		}
	}
}

void AnimationComponent::setToDefaultFrame(){
	if ( !animations.empty() ){
		animations[currentAnimation].setToDefault();
	}
}

void AnimationComponent::setDefaultFrame( Uint nAnimation, Uint nFrame ){
	if ( nAnimation < animations.size() )
		animations[nAnimation].setDefault(nFrame);
}

const SDL_Rect& AnimationComponent::get(Uint nAnimation)
{
	if ( animations.empty() || nAnimation >= animations.size() ){
		return box;
	}
//	if (nAnimation == 0){ return animations[ 0 ](); }
	if (nAnimation < animations.size()){
		return animations[ nAnimation ]();
	}
}

const SDL_Rect& AnimationComponent::operator()(){
	return get(currentAnimation);
}
