#ifndef _ENGINE_COMPONENT_COMPONENT_H
#define _ENGINE_COMPONENT_COMPONENT_H


class Object;

namespace Component {

class Component {
public:
	virtual void update(Object& object, const double& dt) {}
	//virtual void draw(Canvas) = 0;
};

} //end namespace Component

#endif //_ENGINE_COMPONENT_COMPONENT_H

