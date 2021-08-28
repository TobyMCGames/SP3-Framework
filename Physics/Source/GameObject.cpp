
#include "GameObject.h"

GameObject::GameObject(GAMEOBJECT_TYPE typeValue)
	: type(typeValue),
	scale(1, 1, 1),
	active(false),
	mass(1.f),
	hp(1),
	//detectionRange(1),
	target(NULL),
	dir(1, 0, 0),
	momentOfInertia(1),
	angularVelocity(0),
	normal(1.f, 0.f, 0.f)
{
}

GameObject::~GameObject()
{
}

void GameObject::setTransform(Vector3 pos, Vector3 vel, Vector3 scale)
{
	this->pos = pos;
	this->vel = vel;
	this->scale = scale;
}



