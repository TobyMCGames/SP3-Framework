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
	this->active = false;
}


