#include "Arrow.h"
#include "MagicBall.h"

MagicBall::MagicBall()
{
	speed = 50.f;
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

}


