#include "Turret.h"
#include "GameLevelManager.h"
#include "ProjectileFactory.h"

Turret::Turret()
{
	shootCounter = 0;
	
}

Turret::~Turret()
{
}

void Turret::Update(double dt, float m_speed)
{
	if ((Player::GetInstance()->pos.x - pos.x) < 0 && (Player::GetInstance()->pos - pos).Length() <= 40 
		&& (Player::GetInstance()->pos.y - pos.y) < 1)
	{
		if (shootCounter > MaxFirerate)
		{
			Projectile* bullet =
				ProjectileFactory::GetInstance()->produceProjectile(ProjectileFactory::PTYPE_TURRETBULLET,
					pos - (normal * scale.x), -normal, scale, normal);
			GameLevelManager::GetInstance()->getcurrentLevel()->getProjectileList()->push_back(bullet);
			shootCounter = 0;
		}
		shootCounter++;
	}
}

void Turret::Response(GameObject* go)
{

}

