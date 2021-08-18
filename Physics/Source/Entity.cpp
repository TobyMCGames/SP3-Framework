#include "Entity.h"

Entity::Entity()
	: curState(STATE_NORMAL)
	, curLocation(ON_GROUND)
{

}

Entity::~Entity()
{

}

void Entity::Update(double dt)
{

}

void Entity::Response(GameObject*)
{
}
