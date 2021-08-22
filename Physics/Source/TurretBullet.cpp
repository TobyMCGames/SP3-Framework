#include "TurretBullet.h"

TurretBullet::TurretBullet()
{
	Default_Speed = 10.f;
	damage = 5;
}

TurretBullet::~TurretBullet()
{

}

void TurretBullet::Update(double dt, float m_speed)
{
	pos += vel * dt * m_speed;
}

void TurretBullet::Response(GameObject* go)
{
	if ((go->type == GameObject::GO_PLAYER) ||
		(go->type > GameObject::PASSIVE_TILE_START && go->type < GameObject::PASSIVE_TILE_END))
		this->active = false;
}

