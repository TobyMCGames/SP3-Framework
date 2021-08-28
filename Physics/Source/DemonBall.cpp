#include "Arrow.h"
#include "DemonBall.h"

DemonBall::DemonBall()
{
	Default_Speed = 20.f;
	damage = 25;
}

DemonBall::~DemonBall()
{
}

void DemonBall::Update(double dt, float m_speed)
{
	pos += vel * dt * m_speed;
}

void DemonBall::Response(GameObject* go)
{
	if (go->type > PASSIVE_TILE_START && go->type < PASSIVE_TILE_END)
	{
		this->active = false;
	}
}

void DemonBall::Render()
{
}

