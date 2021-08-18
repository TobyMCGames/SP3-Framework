#include "Entity.h"

Entity::Entity()
{

}

Entity::~Entity()
{
	for (int i = 0; i < projectileVector.size(); i++)
	{
		delete projectileVector[i];
		projectileVector[i] = NULL;
	}
	projectileVector.clear();
}

void Entity::Update(double dt)
{
	for (int i = 0; i < projectileVector.size(); i++)
	{
		projectileVector[i]->Update(dt);
	}
}

void Entity::Response(GameObject*)
{

}
