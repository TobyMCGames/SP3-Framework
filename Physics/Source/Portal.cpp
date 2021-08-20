#include "Portal.h"

Portal::Portal()
{
	Default_Speed = 100.f;
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
	if ((go->type > GameObject::PASSIVE_TILE_START &&
		go->type < GameObject::PASSIVE_TILE_END))
		this->active = false;
}

