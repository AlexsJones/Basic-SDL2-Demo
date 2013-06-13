#ifndef _ENGINE_COMPONENT_COMPONENT_H
#define _ENGINE_COMPONENT_COMPONENT_H


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
