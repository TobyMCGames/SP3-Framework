#include "Projectile.h"

Projectile::Projectile()
{
}

Projectile::~Projectile()
{

}

void Projectile::Update(double dt)
{
	pos += vel *dt;
}

void Projectile::Response(GameObject* go)
{
}
