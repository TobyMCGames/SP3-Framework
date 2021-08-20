#include "Entity.h"

Entity::Entity()
	: curState(STATE_NORMAL)
	, curLocation(ON_GROUND)
	, curDirection(LEFT)
{

}

Entity::~Entity()
{
	// clean up later please 
}




