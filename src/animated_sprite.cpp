
#include "engine.h"

AnimatedSprite::AnimatedSprite(Uint image, SDL_Rect frame, int frames, int defaultFrame)
{
	speed = Interval<Uint32>(65);
	
	if ( !image ) { return; }
	this->image = image;
	
	SDL_Rect clip = {0,0,0,0};
	clip = Engine::getImageSheetDimensions(image);
	
	// Calculate the amount of frames that can fit in the space of the image.
	int framesWide = ( clip.w - frame.x ) / frame.w;
	int framesHigh = ( clip.h - frame.y ) / frame.h;
	
	//if ( (framesWide * framesHigh) < frames )
	//	printf("Not enough space inside %s image to create %s animation\n",imagefile.c_str(), id.c_str());
	
	// Get the absolute coordinates of the start frame.
	// This allows the frame to be relative of the image box.	
	frame.x += clip.x;
	frame.y += clip.y;
	int startX = frame.x;
	
	int curRow = 0;
	int curCol = 0;
	
	// Assign the frames to the sprite from the image.
	for (int currentFrame = 0; currentFrame < frames; ++currentFrame) {
		// If the current frame doesn't fit on the image (x-axis).
		// Go to the next line and reset the X cooridinate.
 		// Currently disabled
 		if ( (frame.x + (currentFrame * frame.w)) > (clip.x + clip.w) ) {
			break;
			//frame.y += frame.h;
			//frame.x = startX;
			//curCol = 0; curRow++;
			//if ( (frame.y + frame.h) > (clip.y + clip.h) ) {
				//printf("Warning %s sprite does not fit inside image correctly.\n", id.c_str());
			//}
		}
		addFrame( Engine::setClip(image,
							frame.x + curCol*frame.w, frame.y + curRow*frame.h, 
							frame.w, frame.h)	);
		curCol++;
	}
	setDefault(defaultFrame);
}


void AnimatedSprite::update(const double& dt) {
	lastUpdate += dt;
	if (lastUpdate >= (1000/(double)fps)) { lastUpdate = 0; }
	else { return; }
	//if (lastUpdate > (1000.f/speed.get())) { return; }
	//if( !speed() || (frames.size() <= 1) ) { return; }
	if ( !reverseAnimate ) {
		if ( currentFrame+1 < frames.size() ) { currentFrame++; }
		else { reverseAnimate = true; }
	} else if( reverseAnimate ) {
		if( currentFrame > 0 ) { --currentFrame; }
		else { reverseAnimate = false; }
	}
}



