#pragma once
#include "Zombie.h"
#include "SkeletonArcher.h"
#include "Spider.h"
#include "Boomer.h"
#include "Turret.h"
#include "DisguisedEnemy.h"
#include "DemonLord.h"
#include "SingletonPattern.h"

class EntityFactory : public SingletonPattern<EntityFactory>
{
public:
	enum EntityTypes
	{
		// entities
		ZOMBIE,
		SKELE_ARCHER,
		SPIDER,
		BOOMER,
		TURRET,
		NYMPH,
		DEMON_LORD,

		// leave this last
		NUM_GAMEOBJECTS
	};

	// remember to set the normal default (1,0,0)
	Entity* produceEntity(EntityTypes entityType, Vector3 pos, Vector3 vel, Vector3 scale);
};

		






