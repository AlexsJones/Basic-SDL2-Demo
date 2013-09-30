
#include "component/animation.h"
#include "macro.h"
#include "engine.h"

Component::Animation::Animation()
{	
	currentAnimation = 0;
	animations.reserve( 8 );
	sAnimation blankAnimation;
	oldBox.x = 0; oldBox.y = 0;
	oldBox.w = 0; oldBox.h = 0;
	blankAnimation.add( oldBox );
	blankAnimation.ID("");
	animations.push_back( blankAnimation );
}

//Should ACTION by type-safe?????
void Component::Animation::update(Uint8 ACTION)
{
	//if(ACTION || oldBox.x != box.x || oldBox.y != box.y )
	{
		if ( animations.size() >= 2 )
		{
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
//	else { setToDefaultFrame(); }
}


/*	The function parameters needs to be shorter.
 * 	Maybe pass in a Sprite object, which isn't being used yet.
 * 
 * 	TODO:: This function is also too large. It should be split up into a bunch
 * 	of functions.
 */
void Component::Animation::add( std::string id, std::string imagefile, SDL_Rect* image, SDL_Rect frame, int frames, int defaultFrame )
{
/*	Get box for the image. If not supplied already.	*/
	if ( !image ) {
		SDL_Rect imageBox;
		imageBox = Engine::getImageSheetDimensions(imagefile);
		imageBox.x = imageBox.y = 0;
		image = &imageBox;
	}

/*	Calculate the amount of frames that can fit in the space of the image. */
	int framesWide = ( image->w - frame.x ) / frame.w;
	int framesHigh = ( image->h - frame.y ) / frame.h;

	if ( (framesWide * framesHigh) < frames )
		printf("Not enough space inside %s image to create %s animation\n",imagefile.c_str(), id.c_str());

/*	Get the absolute coordinates of the start frame.	*/
/*	This allows the frame to be relative of the image box.	*/	
	frame.x += image->x;
	frame.y += image->y;
	int startX = frame.x;


//	Animation* newAnimation = new Animation;
	sAnimation newAnimation;
	newAnimation.ID(id);

/*	Just use a Point index.x/y ?	*/
	int rowIndex = 0;
	int columnIndex = 0;
	
/*	Assign the frames to the sprite from the image.	*/
	for (int currentFrame = 0; currentFrame < frames; currentFrame++)
	{
/*		If the current frame doesn't fit on the image (x-axis).
 * 		Go to the next line and reset the X cooridinate.	*/
 		if ( (frame.x + (currentFrame * frame.w)) > (image->x + image->w) ){
		/*	Lets not allow one animation to span multiple lines. This method
		 * 	of allocating a sprite will definitely be changed, possibly by
		 * 	using a SpriteStructure.	*/
			break;
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

void Component::Animation::set( Uint nAnimation ){
	if ( nAnimation < animations.size() ){
		currentAnimation = nAnimation;
	}
}

void Component::Animation::set( std::string animationID )
{
	//for ( auto index: animations)
	{	/*	check if animationID matches any animations[i].id()	*/
	//	if ( index.ID() == animationID )
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

void Component::Animation::setToDefaultFrame(){
	if ( !animations.empty() ){
		animations[currentAnimation].setToDefault();
	}
}

void Component::Animation::setDefaultFrame( Uint nAnimation, Uint nFrame ){
	if ( nAnimation < animations.size() )
		animations[nAnimation].setDefault(nFrame);
}

const SDL_Rect& Component::Animation::get(Uint nAnimation)
{
	if ( nAnimation > 0 && nAnimation < animations.size() ){
		return animations[ nAnimation ]();
	}
	if ( nAnimation >= animations.size() ){
		return animations.back()();
	}
	return animations[0]();
}
