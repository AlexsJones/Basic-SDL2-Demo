
#include "engine.h"
#include "macro.h"

/**	Note: If player needs to be updated multiple times, there is a very
 * 	good chance he could glitch through things(especially if there is low
 * 	fps) The engine needs to be able to handle it. With the current system this
 * 	isn't really possible. There needs to be a good collision detection system.
 * 	Possibly AABBox system.
 * 
 * 	Need separate box for collisions. 
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
{
	Player();
	name = filename;
	animation.create( name, width, height );
	box.w = width;
	box.h = height;
}

void Player::setType( const PlayerType& type ){ this->type = type; }

//Getters

const PlayerType& Player::getType(){ return type; }

//const SDL_Rect& Player::getBox(){ return box; }
//const SDL_Rect& Player::getImageBox(){ return imagebox; }

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

