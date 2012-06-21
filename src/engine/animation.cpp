
#include "engine.h"

/**	Each Animation should have frame zero return a box{0,0,0,0} so characters
 * 	or players that are not setup, don't cause the program to crash when
 * 	they are instantiated. This will make animation/frame 1 to be 1 and frame 
 * 	zero to be zeroes(blank).
**/
///////////////////////////
/// 	Animation 		///
///////////////////////////
void Animation::ID(std::string id)
{
	this->id = id;
}
Animation::Animation()
	: id(),locked(false), currentFrame(1), timeref(0)
{
//	frames.reserve(2);
	add( {0,0,0,0} );
	speed = 50;
	defaultFrame = 1;
	reverseAnimate = false;
}

Animation::Animation(std::string imagefile, int w, int h)
{
	Animation();
//	create(imagefile, w, h);
}

void Animation::animate()
{
	if( Timer::updateInterval(speed, timeref) )
	{
		if ( !reverseAnimate )
		{
			currentFrame++;
			if ( currentFrame >= frames.size()-1 ){
				if ( frames.size() == 2 || frames.size() == 3 ) currentFrame = 1;
				else { reverseAnimate = true; currentFrame--; }
			}
		}
		else if( reverseAnimate )
		{
			currentFrame--;
			if( currentFrame<=1 )
				reverseAnimate = false;
		}
	}
}

/*void Animation::animate(int ACTION)
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
*/
void Animation::setSpeed(int speed){
	this->speed = speed;
}

/*void Animation::set(Uint nAnimation){
//	if (nAnimation > animations)	//if animation is higher than whats available
//		return;						//don't change animation
	if (nAnimation <= 0)			//AnimationZero doesn't exist anymore
		return;
//	else currentAnimation = --nAnimation;
}
*/
void Animation::setDefault(int nFrame){
	if ( (nFrame >= frames.size()) || (nFrame == 0) ){
		return;
	} else{
		defaultFrame = nFrame;
	}
}

void Animation::setToDefault(){
	currentFrame = defaultFrame;
	if (currentFrame >= frames.size())
		currentFrame = 1;
	reverseAnimate = false;
}

const SDL_Rect& Animation::get( int nFrame )
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
	
	if ( nFrame >= frames.size() ) 				//	If frame index is too high
		printf("Warning, requesting a frame index higher than total frames...\n");
		return frames[ frames.size()-1  ];	//	Return the last frame
}

const SDL_Rect& Animation::operator()(){
	return get( currentFrame );
}


void Animation::add(SDL_Rect frame)
{
	frames.push_back( frame );
}


///////////////////////////
///	Animation Component	///
///////////////////////////

AnimationComponent::AnimationComponent()
{	
	box = {0,0,0,0};
	currentAnimation = 1;
	animations.reserve( 8 );
	Animation blankAnimation;
	blankAnimation.add( box );
	blankAnimation.ID("");
	animations.push_back( blankAnimation );
//	printf("AnimationComponent now has %d Animation\n", animations.size());
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


//	The function parameters needs to be shorter.
void AnimationComponent::add( std::string id, std::string imagefile, SDL_Rect* image, SDL_Rect frame, int frames, int defaultFrame )
{
//	printf("Adding Animation\n");
//	Get box for the image.If not supplied already.
	if ( !image ){
	SDL_Rect* imageBox = new SDL_Rect;
	*imageBox = Engine::getImageSheetDimensions(imagefile);
	imageBox->x = imageBox->y = 0;
	image = imageBox;
	//printf("Image::%d.%d %d x %d\n",image->x, image->y, image->w, image->h );
	}

//	Caluculate the amount of frames that can fit in the space of the image.
	int framesWide = ( image->w - frame.x ) / frame.w;
	int framesHigh = ( image->h - frame.y ) / frame.h;

	if ( (framesWide * framesHigh) < frames )
		printf("Not enough space inside %s image to create %s animation\n",imagefile.c_str(), id.c_str());

//	Get the absolute coordinates of the start frame.
//	This allows the frame to be relative of the image box.
	int startX = frame.x;
	
	frame.x += image->x;
	frame.y += image->y;
	
//	Animation* newAnimation = new Animation;
	Animation newAnimation;
	newAnimation.ID(id);
	newAnimation.setDefault(defaultFrame);
	
	//Just use a Point index.x/y ?
	int rowIndex = 0;
	int columnIndex = 0;
//	Assign the frames to the sprite from the image.
	for (int currentFrame = 0; currentFrame </*=/*if first frame is 1 NOT 0*/ frames; currentFrame++)
	{
//		If the current frame doesn't fit on the image (x-axis).
		if ( (frame.x + (currentFrame * frame.w)) > (image->x + image->w) ){
//			Go to the next line and reset the X cooridinate.
			frame.y += frame.h;	rowIndex++;
			frame.x = startX;	columnIndex = 0;
//			Unless there isn't room for the next line....dun..dun..dunnnnn
			if ( (frame.y + frame.h) > (image->y + image->h) ){
				printf("Warning %s sprite does not fit inside image correctly.\n", id.c_str());
			}
		}
		/*	Add the frames to the Animation's Sprite	*/
		newAnimation.add( Engine::setClip( NULL,
							frame.x + columnIndex*frame.w, frame.y + rowIndex*frame.h, 
							frame.w, frame.h )	);
		columnIndex++;
	}
	animations.push_back( newAnimation );
//	printf("Animation now has %d frames\n", animations[ animations.size() -1].sprites.size());
//	printf("AnimationComponent now has %d Animation\n", animations.size());
/*	for (rowIndex = 0; rowIndex <= framesHigh; rowIndex++){
		for (columnIndex = 0; columnIndex <= frames; columnIndex++){
			newAnimation.add( Engine::setClip( NULL, frame.x + columnIndex*frame.w, rowIndex*frame.h + frame.y, frame.w, frame.h )	);
//			sprites.push_back( Engine::setClip( NULL, columnIndex*w, rowIndex*h, w, h ) );
//			newAnimation.addSpriteFrame()
		}
	}	*/
//	printf("image: %d.%d %d x %d\n",image->x,image->y,image->w,image->h);
}

void AnimationComponent::set( Uint nAnimation ){
	if ( 0 < nAnimation && nAnimation < animations.size() ){
		currentAnimation = nAnimation;
	}
//	else printf("Could not set animation: %d\n",nAnimation);
}

void AnimationComponent::set( std::string animationID )
{
		//for ()		//iterate through animations
						//check if animationID matches any animations[i].id()
}

void AnimationComponent::setToDefault(){
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
//	printf("Total Animations: %d \nRequesting Animation: %d\n",animations.size(),nAnimation);
	if ( animations.empty() ){
//		printf("Empty Animation, Tried to Get Animation %d \n\n",nAnimation);
		return box;
	}
//	if (nAnimation == 0){
//		printf("Getting Animation %d \n\n",nAnimation);
//		return animations[ 0 ]();
//	}
	if (nAnimation < animations.size()){
//		printf("Getting Animation: %d which has %d frames\n\n",nAnimation, animations[ animations.size() -1].frames.size());
		return animations[ nAnimation ]();
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
///	The Code CRASHES Here	///X
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	}
}

const SDL_Rect& AnimationComponent::operator()(){
	const SDL_Rect &temp = get(currentAnimation);
//	printf("Current Animation: %d, Frame: %d,%d %d x %d\n",currentAnimation,&temp.x,&temp.y,&temp.w,&temp.h);
	return get(currentAnimation);
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
///	currentAnimation needs to be set-up correctly	///X
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
