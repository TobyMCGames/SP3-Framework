#include "Bomb.h"
#include "MeshRender.h"

Bomb::Bomb()
{
	Default_Speed = 20.f;
	damage = 50.f;
	projectileState = IN_MOTION;
}

Bomb::~Bomb()
{
}

void Bomb::Update(double dt, float m_speed)
{
	if (projectileState != ProjectileState::IDLE_PROJECTILE)
	{
		pos += vel * m_speed * dt;
		vel += GamePhysics::GetInstance()->gravity * m_speed * dt;
	}
}

void Bomb::Response(GameObject* go)
{
	if (go->type > GameObject::PASSIVE_TILE_START && go->type < GameObject::PASSIVE_TILE_END)
	{
		projectileState = ProjectileState::IDLE_PROJECTILE;
		vel = 0;
		this->active = false;
	}
}

void Bomb::Render()
{
	
}



