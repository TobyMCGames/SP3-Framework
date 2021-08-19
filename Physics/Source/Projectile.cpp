#include "Projectile.h"

Projectile::Projectile()
{
}

Projectile::~Projectile()
{

}

void Projectile::Update(double dt, float m_speed)
{
	pos += vel * dt * m_speed;
}

void Projectile::Response(GameObject* go)
{
}
