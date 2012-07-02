
#include "player.h"

Player::Player()
	:Character()
{
}

Player::Player( std::string filename, int width, int height ) //this width + height  determines size of frames.
	:Character()
{
	Player();
	name = filename;
//	animation.add( "left", {{0,0,47,51}}, 1 );
//	animation.add( name, width, height );
	SDL_Rect frame = {0,0,width,height};
	animation.add( "left", filename, NULL, frame, 6, 3	);
	frame.y += height;
	animation.add( "right", filename, NULL, frame, 6, 3 );
/*	Set default frames to 2 for pirate	*/
//	animation.setDefaultFrame(1,3);
//	animation.setDefaultFrame(2,3);
	box.w = width;
	box.h = height;
}


///////////////////////////
///		Random Tests	///
///////////////////////////
class Foo
{
	private:
		int nBar;
		std::vector<int> vBar;
	public:
		Foo(const std::initializer_list<int>& nAssign) //:ntest(pie)
		{
			auto x = nAssign.begin();
			nBar = *x;
		}	
};
Foo foo( {5,7,3,8,3,2,7} );

class Player2
{
	public:
		std::string name;
		std::string image;
		SDL_Point size;
		int speed;
	public:
		//Player2(const std::initializer_list<int>& nAssign) //:ntest(pie)
		Player2(std::string name_, ...);
		
};

//Player2 teeest { "pirate", "pirate", {40,60}, 140 };
//Player2 teeest2{ "pirate", teeest2.image = "pirate", {40,60}, 140 } ;
//Foo fool( {nBar=5} );

