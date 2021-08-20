#include "Arrow.h"

Arrow::Arrow()
{
	Default_Speed = 30.f;
	damage = 10;
}

Arrow::~Arrow()
{

}

void Arrow::Update(double dt, float m_speed)
{
	pos += vel * dt * m_speed;
	vel += (GamePhysics::GetInstance()->gravity) * dt * m_speed;
	normal = vel.Normalized();
}

void Arrow::Response(GameObject* go)
{
	this->active = false;
}

