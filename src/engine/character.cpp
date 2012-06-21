
#include "engine.h"
#include "macro.h"
#include "character.h"

/**	Note: If player needs to be updated multiple times, there is a very
 * 	good chance he could glitch through things(especially if there is low
 * 	fps) The engine needs to be able to handle it. With the current system this
 * 	isn't really possible. There needs to be a good collision detection system.
 * 	Possibly AABBox system.
 * 
 * 	Need separate box for collisions. The box could be different based on animation. There
 * 	could also be another box that takes its position and calculates a larger box that represents
 * 	the tiles the player intersects.
 * 
 * 
 *  A_LEFT
 * 	A_ATTACK
 * 
 * 	S_STEP
 * 	S_ATTACK
**/

Character::Character()
	 :AnimatedObject(CHARACTER), physics(box), ACTION(0),
		Actions
		{	 //This is just a test
			{"LEFT",1}, {"RIGHT",0},
			{"UP",0}, {"DOWN",0},
			{"ATTACK",0}
		}
//		velocity(140.f), timeref(SDL_GetTicks())
{
/*	vel.x = vel.y = 0.f;
	acc.x = acc.y = 0;
	timestep=(1000.f/velocity);
	accstep = velocity*((timestep * 4.f)/1000.f);//LOL ~4	//4 is meant to be an amount of pixels or something
	deaccstep = accstep * 4.f;
	animation.setSpeed(2000/(velocity/5));
	
	pos.x = -(box.w / 2.0);
	pos.y = -(box.h / 2.0);*/
//	box.x = pos.x;
//	box.y = pos.y;
	box.x = 0;
	box.y = 0;
	oldbox = box;
}
void Character::TestActions()
{
	for (auto x: Actions)
	{
		if ( (x.second) )	//If the value is true
		{
			printf("'[%s]' is enabled in custom actions\n",x.first.c_str());
		}
	}
}

Character::Character( InputComponent* input ) //Character(const InputComponent& input)
	:AnimatedObject(CHARACTER), physics(box)
{
	Character();
	this->input = input;
//	Animation animation = { "Left", {{0,0,47,51}}, 1 };
//						  {"id", SDL_Rect coord/size, frames?}
}


void Character::animate()
{	//This function may be changed or removed
	
//	Check for actual movement
	//if( oldbox.x != box.x || oldbox.y != box.y ){ animation.animate(); }
//	if ( (ACTION & ATTACKING) == ATTACKING )
//		Engine::Physics::particles();
	//else { animation.setToDefault(); }	//default frame
/*	if( oldbox.x != box.x || oldbox.y != box.y ){
		animation.animate( ACTION );
	} else
	{ animation.setToDefault(); }
*/}

///#### Keyboard Input ####
//	Character.update( [event/message] )	---> component-manager hands it to correct component
//										`*--> if it is null, just update everything.
void Character::move(SDL_KeyboardEvent& keyevent)
{
//	std::map< std::string, std::list<SDL_Keycode> > GameEventPrimitives;
//	GameEventPrimitives.push_back("LEFT", SDLK_LEFT)
//	animation("LEFT"), move("LEFT")
//	struct GameEventPrimitive{std::string id; std::list<SDL_Keycode>}

	if (keyevent.type == SDL_KEYDOWN)	//Turn on Action
	{
		switch (keyevent.keysym.sym)
		{
			case SDLK_LEFT: 	ACTION |= LEFT;			break;
			case SDLK_RIGHT:	ACTION |= RIGHT;		break;
			case SDLK_UP: 		ACTION |= UP;			break;
			case SDLK_DOWN: 	ACTION |= DOWN; 		break;
			default: break;
		}
	}
	if (keyevent.type == SDL_KEYUP)		//Turn off Action
	{
		switch (keyevent.keysym.sym)
		{
			case SDLK_LEFT: 	ACTION &= ~LEFT;		break;
			case SDLK_RIGHT:	ACTION &= ~RIGHT;		break;
			case SDLK_UP: 		ACTION &= ~UP;			break;
			case SDLK_DOWN: 	ACTION &= ~DOWN; 		break;
			default: break;
		}
	}
}
///#### End of Key Input ####


void Character::update()
{
	oldbox = box;
	//box = physics.update( ACTION, box );
	physics.update( ACTION, box );
	position.update();	//Position should be part of physics, box(position) should be part of movement

	if( oldbox.x != box.x || oldbox.y != box.y ){
		animation.update( ACTION );
//		printf("ACTION = %d\n",ACTION);
	} else
/*	Possibly have animation speed based on an average amount of pixels moved.
 * 	And have setToDefault() called when he stands still for 2 sec for example
 */
	{ animation.setToDefault(); }
}


/**	OLD update() function
void Character::update()
{
//fixed timestep that is fixed to move at least 1 px per step(if max vel), this is experimental.
//It keeps updating to catchup if it is too far behind.(very low fps may be problematic for collisions)
//This method has a constant delta time, therefore it is difficult
//to implement variable acceleration
//I may implement RK4 instead. -->It's more accurate, supports variable accel better, but may slower.
//NEED TO FIX HARD CODED values to be based on velocity/acc.
		oldbox = box;
		while (Timer::updateInterval(timestep, timeref)){
			if (!ACTION){
				//animation.setSpeed(75); //USELESS -- This seems extremely useless?
				//if (abs(acc.x) < .05f && abs(acc.y) < .05f) oldbox = box;		//oldbox = box was just called...reason for this?
			}
			
			else animation.setSpeed(2000/(velocity/5));
			
			if ( (!hasFlag(ACTION, LEFT) && !hasFlag(ACTION, RIGHT)) || hasFlag(ACTION, (LEFT + RIGHT)) ){
				if (acc.x > 0){
					acc.x -= 12;
					if (acc.x < 0) acc.x = 0;
				}
				if (acc.x < 0){
					acc.x += 12;
					if (acc.x > 0) acc.x = 0;
				}
			}
			if ( (!hasFlag(ACTION, UP) && !hasFlag(ACTION, DOWN)) || hasFlag(ACTION, (UP + DOWN)) ){
				if (acc.y > 0){
					acc.y -= 12;
					if (acc.y < 0) acc.y = 0;
				}
				if (acc.y < 0){
					acc.y += 12;
					if (acc.y > 0) acc.y = 0;
				}
			}
		
//	TODO: Instead of hasFlag()'ing everything, have a container of Actions
//	 with a function to execute. It would look something like this. 
//	 std::map< string, bool >
			
			//	TODO::Move animation.set to AnimationComponent.update()
			
			if (hasFlag(ACTION, LEFT))	{ acc.x -= 4; animation.set( 1 ); }	//animation.set(LEFT_ANIMATION);
			if (hasFlag(ACTION, RIGHT))	{ acc.x += 4; animation.set( 2 ); } //animation.set(animation.action["right"])
			if (hasFlag(ACTION, UP))	{ acc.y -= 4; animation.set( 3 ); }	//animation["up"]; --this would return animation.action["up"]
			if (hasFlag(ACTION, DOWN))	{ acc.y += 4; animation.set( 4 ); }
	//	Diagonals
			if (hasFlag(ACTION, (UP + LEFT)))	{ animation.set( 5 ); }
			if (hasFlag(ACTION, (UP + RIGHT)))	{ animation.set( 6 ); }
			if (hasFlag(ACTION, (DOWN + LEFT))) { animation.set( 7 ); }
			if (hasFlag(ACTION, (DOWN + RIGHT))){ animation.set( 8 ); }

			if (acc.x > velocity) 	acc.x = velocity;
			if (acc.y > velocity) 	acc.y = velocity;
			if (acc.x < -velocity) 	acc.x = -velocity;
			if (acc.y < -velocity) 	acc.y = -velocity;
			
			vel.x = ((timestep/1000.f) * acc.x);
			vel.y = ((timestep/1000.f) * acc.y);
			
			pos.x += vel.x;
			pos.y += vel.y;
			
			box.x = pos.x;
			box.y = pos.y;
			
			if (Engine::DEBUG == 3){
				printf("player is at %d, %d \n",box.x,box.y);
				printf("player is at %.1f, %.1f \n",pos.x,pos.y);
				printf("with velocity of %f,%f \n\n",vel.x,vel.y);
			}
			
		}
		if (!ACTION){ timeref = SDL_GetTicks(); }
}
**/
//void Character::moveTo( Coordinate ){}
float Character::getMaxVelocity(){ return physics.Velocity(); }
//void Character::setType( const CharacterType& type ){ }

//	This allows engine to draw image on canvas.
//const SDL_Rect& Character::getImage(){ return animation(); }

//const SDL_Rect& Character::getBox(){ return animations.getBox(); }


void Character::switchInput(InputComponent* input)
{	
	this->input = input;
}
