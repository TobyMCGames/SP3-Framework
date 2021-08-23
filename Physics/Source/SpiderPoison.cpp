#include "SpiderPoison.h"

// this file contains code for cobwebs shot by spiders. The file is named SpiderPoison as that was our initial idea

SpiderPoison::SpiderPoison()
{
	Default_Speed = 10.f;
	damage = 10;
}

SpiderPoison::~SpiderPoison()
{

}

void SpiderPoison::Update(double dt, float m_speed)
{
	pos += vel * dt * m_speed;
	return;
}

void SpiderPoison::Response(GameObject* go)
{
	if ((go->type == GameObject::GO_PLAYER) ||
		(go->type > GameObject::PASSIVE_TILE_START && go->type < GameObject::PASSIVE_TILE_END))
		this->active = false;
}

void SpiderPoison::Render()
{
}