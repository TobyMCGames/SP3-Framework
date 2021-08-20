#include "Entity.h"

Entity::Entity()
	: curState(STATE_NORMAL)
	, curLocation(ON_GROUND)
{

}

Entity::~Entity()
{
	// clean up later please 
}