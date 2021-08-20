#include "TurretBullet.h"

TurretBullet::TurretBullet()
{
	speed = 10.f;
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

}

