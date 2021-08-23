#include "Arrow.h"
#include "DemonBall.h"

DemonBall::DemonBall()
{
	Default_Speed = 10.f;
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
}

void DemonBall::Render()
{
}

