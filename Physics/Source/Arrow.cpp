#include "Arrow.h"

Arrow::Arrow()
{
}

Arrow::~Arrow()
{
}

void Arrow::Update(double dt, float m_speed)
{
	vel += (GamePhysics::GetInstance()->gravity) * dt * m_speed;
}

void Arrow::Response(GameObject* go)
{
}
