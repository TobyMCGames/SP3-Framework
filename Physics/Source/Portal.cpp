#include "Portal.h"

Portal::Portal()
{
	speed = 100.f;
	scale.Set(5, 5, 1);
}

Portal::~Portal()
{
}

void Portal::Update(double dt, float GAMESPEED)
{
	pos += vel * dt;
}

void Portal::Response(GameObject* go)
{
	this->active = false;
}

