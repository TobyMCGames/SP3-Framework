#include "Arrow.h"

Arrow::Arrow()
{
	speed = 30.f;
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

