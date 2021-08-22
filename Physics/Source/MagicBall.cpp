#include "Arrow.h"
#include "MagicBall.h"

MagicBall::MagicBall()
{
	Default_Speed = 50.f;
}

MagicBall::~MagicBall()
{

}

void MagicBall::Update(double dt, float m_speed)
{
	pos += vel * dt * m_speed;
}

void MagicBall::Response(GameObject* go)
{
	if ((go->type > GameObject::PASSIVE_TILE_START &&
		go->type < GameObject::PASSIVE_TILE_END) || (go->type == GameObject::GO_TURRET) || (go->type == GameObject::GO_ZOMBIE))
		this->active = false;
}


