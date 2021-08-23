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
	if ((go->type > GameObject::PASSIVE_TILE_START &&
		go->type < GameObject::PASSIVE_TILE_END) || (go->type == GameObject::GO_TURRET) || (go->type == GameObject::GO_ZOMBIE))
	{
		this->active = false;
		std::cout << GamePhysics::GetInstance()->GetCollidePos()<<std::endl;
	}
}

void Portal::Render()
{
}

