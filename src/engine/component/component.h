#ifndef _ENGINE_COMPONENT_COMPONENT_H
#define _ENGINE_COMPONENT_COMPONENT_H

/**TODO:Create a ComponentManager
 * 		Put all components into a 'namespace Component{}'
 * 		create a folder for Components
 * 
 *  Note: The way that physics updates is a real mess, and will introduce
 *  a lot of problems later on. 
 * 
 * 	Oh BTW the whole directory and structure of code needs to be re-thought
 * 	and cleaned up. Should these directories also represent the namspace
 * 	they are in?
 * 	poc -> src->
 * 				Game			//or 'Client'	//Game could hold all the scripts and content stuff
 * 					Engine
 * 					Map
 * 					Components
 * 					Player
 * 					Window
 * 				Server
 *  __	 __			Components
 * |  | |
 * |__| |		//The first^ hierarchy one seems more logical
 * 
 * poc -> src->
 * 				Engine
 * 					Map
 * 					Components
 * 					Player
 * 					Window
 * 				Server
 * 				Game
 * 					Blah
**/
namespace Component{
	class iComponent
	{
		public:
			virtual void update() = 0;
	//		virtual void draw() = 0;
	};
}
/*	Component namespace END	*/

enum Movement	//TODO:Replace this
{
	LEFT 	= 	1<<1,
	RIGHT 	=	1<<2,
	UP 		=	1<<3,
	DOWN 	=	1<<4,
	ATTACK 	=	1<<5
/**
	ATTACK2	=	1<<6
	JUMP	=	1<<7
	DEAD	=	1<<8
**/	
};

#endif
