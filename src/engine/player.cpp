
#include "player.h"

Player::Player()
	//:Character()
{
}

Player::Player( std::string filename, int width, int height ) //this width + height  determines size of frames.
	//:Character()
{
	Player();
	name = filename;
//	animation.add( "left", {{0,0,47,51}}, 1 );
//	animation.add( name, width, height );
	SDL_Rect frame = {0,0,width,height};
	animation.add( "left", filename, NULL, frame, 6, 3	);
	frame.y += frame.h;
	animation.add( "right", filename, NULL, frame, 6, 3 );
/*	Set default frames to 2 for pirate	*/
//	animation.setDefaultFrame(1,3);
//	animation.setDefaultFrame(2,3);
	box.w = width;
	box.h = height;
}
