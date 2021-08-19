#pragma once
#include "Arrow.h"
#include "Bomb.h"
#include "DemonBall.h"
#include "MagicBall.h"
#include "Portal.h"
#include "SkeleArrow.h"
#include "SpiderPoison.h"
#include "TurretBullet.h"

class ProjectileFactory
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

	static Projectile* getObject(int choice,Vector3 pos, Vector3 vel, Vector3 scale,Vector3 normal);
	ProjectileFactory();
	~ProjectileFactory();
private:
	static Projectile* Prototypes[NUM_PROJECTILES];
};

Projectile* ProjectileFactory::Prototypes[] = {
	new Arrow(),new Bomb(), new DemonBall(), new MagicBall(), new Portal(), new SkeleArrow(), new SpiderPoison(),
	new TurretBullet()
};

Projectile* ProjectileFactory::getObject(int choice,Vector3 pos,Vector3 vel,Vector3 scale,Vector3 normal) {
	Projectile* newProjectile = Prototypes[choice]->clone();
	newProjectile->pos = pos;
	newProjectile->scale = scale;
	newProjectile->vel = vel;
	newProjectile->active = true;
	newProjectile->normal = normal;
	switch (choice)
	{
	case PTYPE_ARROW:
		newProjectile->type = GameObject::GAMEOBJECT_TYPE::GO_ARROW;
		break;
	case PTYPE_BOMB:
		newProjectile->type = GameObject::GAMEOBJECT_TYPE::GO_BOMB;
		break;
	case PTYPE_DEMONBALL:
		newProjectile->type = GameObject::GAMEOBJECT_TYPE::GO_DEMONBALL;
		break;
	case PTYPE_MAGICBALL:
		newProjectile->type = GameObject::GAMEOBJECT_TYPE::GO_MAGICBALL;
		break;
	case PTYPE_PORTAL:
		newProjectile->type = GameObject::GAMEOBJECT_TYPE::GO_PORTAL;
		break;
	case PTYPE_SKELEARROW:
		newProjectile->type = GameObject::GAMEOBJECT_TYPE::GO_SKELEARROW;
		break;
	case PTYPE_SPIDERPOISON:
		newProjectile->type = GameObject::GAMEOBJECT_TYPE::GO_SPIDERPOISON;
		break;
	case PTYPE_TURRETBULLET:
		newProjectile->type = GameObject::GAMEOBJECT_TYPE::GO_TURRETBULLET;
		break;
	}
	return newProjectile;

}

ProjectileFactory::ProjectileFactory()
{

}

ProjectileFactory::~ProjectileFactory()
{
	// delete array here	
	int arrsize = sizeof(Prototypes) / sizeof(Prototypes[0]);
	for (int i = 0; i < arrsize; i++)
	{
		delete Prototypes[i];
		Prototypes[i] = nullptr;
	}
}





