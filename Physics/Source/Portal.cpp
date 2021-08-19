#include "Portal.h"

Portal::Portal()
{
}

Portal::~Portal()
{
}

void Portal::Update(double dt, float m_speed)
{
	pos += vel * dt;
}

void Portal::Response(GameObject* go)
{
}

