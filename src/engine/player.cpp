
#include "engine.h"
#include "macro.h"

/**	Note: If player needs to be updated multiple times, there is a very
 * 	good chance he could glitch through things(especially if there is low
 * 	fps) The engine needs to be able to handle it. With the current system this
 * 	isn't really possible. There needs to be a good collision detection system.

 * 	This can be done if player has it's own CollisionComponent. The 
 * 	interface for this component should be able to interact with other
 * 	collision components, maybe through a CollisonComponentManager.
 * 
 * 	Have a previously stored, good position that changes everytime the
 * 	player moves. If he moves into a wall it will restore his x position 
 * 	to the previously known good position, for example. It would need to
 * 	tell physics to hinder the player's x-axis velocity.
 * 
 * 	Need separate box for collisions. 
 *  Possibly AABBox collision detection.
 * 
 * 
 *  A_LEFT
 * 	A_ATTACK
 * 
 * 	S_STEP
 * 	S_ATTACK
**/

Player::Player()
	:Character()
{
}

Player::Player( std::string filename, int width, int height ) //this width + height  determines size of frames.
	:Character()
{
	Player();
	name = filename;
//	animations.add( name, width, height );
	SDL_Rect frame = {0,0,width,height};
	animation.add( "left", filename, NULL, frame, 6, 2	);
	frame.y += height;
	animation.add( "right", filename, NULL, frame, 6, 2 );
	//	Set default frames to 2 for pirate
	animation.setDefaultFrame(1,2);
	animation.setDefaultFrame(2,2);
	box.w = width;
	box.h = height;
}

void Player::setType( const PlayerType& type ){ this->type = type; }

const PlayerType& Player::getType(){ return type; }


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

