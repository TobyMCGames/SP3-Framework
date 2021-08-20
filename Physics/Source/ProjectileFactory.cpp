#include "ProjectileFactory.h"
#include "Arrow.h"
#include "Bomb.h"
#include "DemonBall.h"
#include "MagicBall.h"
#include "Portal.h"
#include "SkeleArrow.h"
#include "SpiderPoison.h"
#include "TurretBullet.h"

Projectile* ProjectileFactory::produceProjectile(PROJECTILE_TYPES projectileType, Vector3 pos, Vector3 vel, Vector3 normal)
{
	Projectile* newProjectile = nullptr;
	switch (projectileType)
	{
	case PTYPE_ARROW:
		newProjectile = new Arrow();
		newProjectile->type = GameObject::GO_ARROW;
		break;
	case PTYPE_BOMB:
		newProjectile = new Bomb();
		newProjectile->type = GameObject::GO_BOMB;
		break;
	case PTYPE_DEMONBALL:
		newProjectile = new DemonBall();
		newProjectile->type = GameObject::GO_DEMONBALL;
		break;
	case PTYPE_MAGICBALL:
		newProjectile = new MagicBall();
		newProjectile->type = GameObject::GO_MAGICBALL;
		break;
	case PTYPE_PORTAL:
		newProjectile = new Portal();
		newProjectile->type = GameObject::GO_PORTAL;
		break;
	case PTYPE_SKELEARROW:
		newProjectile = new SkeleArrow();
		newProjectile->type = GameObject::GO_SKELEARROW;
		break;
	case PTYPE_SPIDERPOISON:
		newProjectile = new SpiderPoison();
		newProjectile->type = GameObject::GO_SPIDERPOISON;
		break;
	case PTYPE_TURRETBULLET:
		newProjectile = new TurretBullet();
		newProjectile->type = GameObject::GO_TURRETBULLET;
		break;		
	}
	newProjectile->pos = pos;
	newProjectile->vel = vel * newProjectile->getProjectileSpeed();
	newProjectile->normal = normal;
	newProjectile->active = true;
	return newProjectile;
}
