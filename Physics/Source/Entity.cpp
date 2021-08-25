#include "Entity.h"

Entity::Entity()
	: curState(STATE_NORMAL)
	, curLocation(ON_GROUND)
	, curDirection(LEFT)
	, InvincibilityTimer(0)
{

}

Entity::~Entity()
{
	// clean up later please 
}


bool Entity::CheckDirection(DIRECTION direction)
{
	if (direction == LEFT)
	{
		if (vel.x < 0)
			return true;
		else if (vel.x > 0)
			return false;
	}
	else if (direction == RIGHT)
	{
		if (vel.x > 0)
			return true;
		else if (vel.x < 0)
			return false;
	}
	else
	{
		std::cout << "Direction unknown bruhhh" << std::endl;
	}
		
	return false;
}

bool Entity::CheckCurDirection()
{
	return curDirection;
}

void Entity::takeDamage(int damage)
{
	this->health -= damage;
}



