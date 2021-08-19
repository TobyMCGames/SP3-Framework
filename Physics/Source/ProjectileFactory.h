#pragma once
#include "SingletonPattern.h"
#include "Projectile.h"

class ProjectileFactory : public SingletonPattern<ProjectileFactory>
{
public:
	enum PROJECTILE_TYPES
	{
		PTYPE_ARROW,
		PTYPE_BOMB,
		PTYPE_DEMONBALL,
		PTYPE_MAGICBALL,
		PTYPE_PORTAL,
		PTYPE_SKELEARROW,
		PTYPE_SPIDERPOISON,
		PTYPE_TURRETBULLET,
		NUM_PROJECTILES,
	};
	Projectile* produceProjectile(PROJECTILE_TYPES projectileType, Vector3 pos, Vector3 vel, Vector3 scale, Vector3 normal);	
};




