#include "Arrow.h"
#include "SkeleArrow.h"

SkeleArrow::SkeleArrow()
{
	Default_Speed = 30;
}

SkeleArrow::~SkeleArrow()
{
}

void SkeleArrow::Update(double dt, float m_speed)
{
	pos += vel * dt * m_speed;
	/*vel += (GamePhysics::GetInstance()->gravity) * dt * m_speed;
	normal = vel.Normalized();*/
}

void SkeleArrow::Response(GameObject* go)
{
}

