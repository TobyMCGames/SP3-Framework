#include "EntityFactory.h"

Entity* EntityFactory::produceEntity(EntityTypes entityType, Vector3 pos, Vector3 vel, Vector3 scale)
{
	Entity* newEntity = nullptr;
	switch (entityType)
	{
	case ZOMBIE:
		newEntity = new Zombie();
		newEntity->type = GameObject::GO_ZOMBIE;
		break;
	case SLOWZOMBIE:
		newEntity = new SLowZombie();
		newEntity->type = GameObject::GO_SLOWZOMBIE;
		break;
	case SKELE_ARCHER:
		newEntity = new SkeletonArcher();
		newEntity->type = GameObject::GO_SKELEARCHER;
		break;
	case HEAVY_SKELE_ARCHER:
		newEntity = new HeavySkeletonArcher();
		newEntity->type = GameObject::GO_HEAVYSKELEARCHER;
		break;
	case SPIDER:
		newEntity = new Spider();
		newEntity->type = GameObject::GO_SPIDER;
		break;
	case BOOMER:
		newEntity = new Boomer();
		newEntity->type = GameObject::GO_BOOMER;
		break;
	case TURRET:
		newEntity = new Turret();
		newEntity->type = GameObject::GO_TURRET;
		break;
	case NYMPH:
		newEntity = new DisguisedEnemy();
		newEntity->type = GameObject::GO_NYMPH;
		break;
	case DEMON_LORD:
		newEntity = new DemonLord();
		newEntity->type = GameObject::GO_DEMONLORD;
		break;
	}
	newEntity->pos = pos;
	newEntity->vel = vel;
	newEntity->scale = scale;
	newEntity->active = true;
	newEntity->normal = Vector3(1, 0, 0);
	return newEntity;
}
