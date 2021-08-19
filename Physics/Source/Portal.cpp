#include "Portal.h"

Portal::Portal()
{
	speed = 10.f;
}

Portal::~Portal()
{
}

void Portal::Update(double dt)
{
	pos += vel * dt;
}

void Portal::Response(GameObject* go)
{
}

