#include "Portal.h"

Portal::Portal()
{
	Default_Speed = 100.f;
	scale.Set(5, 5, 1);
}

Portal::~Portal()
{
}

void Portal::Update(double dt, float m_speed)
{
	pos += vel * dt * m_speed;
}

void Portal::Response(GameObject* go)
{
	
}

