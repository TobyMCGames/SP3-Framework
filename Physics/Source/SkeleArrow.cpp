#include "Arrow.h"
#include "SkeleArrow.h"

SkeleArrow::SkeleArrow()
{
	Default_Speed = 30;
	damage = 10;
}

SkeleArrow::~SkeleArrow()
{
}

void SkeleArrow::Update(double dt, float m_speed)
{
	pos += vel * dt * m_speed;
	/*vel += (GamePhysics::GetInstance()->gravity) * dt * m_speed;
	normal = vel.Normalized();*/
}

void SkeleArrow::Response(GameObject* go)
{
	if ((go->type == GameObject::GO_PLAYER) ||
		(go->type > GameObject::PASSIVE_TILE_START && go->type < GameObject::PASSIVE_TILE_END))
			this->active = false;
}

void SkeleArrow::Render()
{
}

