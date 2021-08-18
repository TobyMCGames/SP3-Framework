#include "Portal.h"

Portal::Portal()
{
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

