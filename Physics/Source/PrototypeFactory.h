#pragma once
#include "Zombie.h"
#include "SkeletonArcher.h"
#include "Spider.h"
#include "Boomer.h"
#include "Turret.h"
#include "DisguisedEnemy.h"
#include "DemonLord.h"



class PrototypeFactory
{
public:
	enum GAMEOBJECTS
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

	static Entity* getObject(int choice,Vector3 pos, Vector3 vel, Vector3 scale);
	PrototypeFactory();
	~PrototypeFactory();
private:
	static Entity* Prototypes[NUM_GAMEOBJECTS];
};

Entity* PrototypeFactory::Prototypes[] = {
	new Zombie, new SkeletonArcher,new Spider, new Boomer,new Turret,new DisguisedEnemy,new DemonLord
};

Entity* PrototypeFactory::getObject(int choice,Vector3 pos,Vector3 vel,Vector3 scale) {
	Entity* newEntity = Prototypes[choice]->clone();
	newEntity->pos = pos;
	newEntity->scale = scale;
	newEntity->vel = vel;
	newEntity->active = true;
	switch (choice)
	{
		case ZOMBIE:
			newEntity->type = GameObject::GO_ZOMBIE;
			break;
		case SKELE_ARCHER:	
			newEntity->type = GameObject::GO_SKELEARCHER;
			break;
		case SPIDER:
			newEntity->type = GameObject::GO_SPIDER;
			break;
		case BOOMER:
			newEntity->type = GameObject::GO_BOOMER;
			break;
		case TURRET:
			newEntity->type = GameObject::GO_TURRET;
			break;
		case NYMPH:
			newEntity->type = GameObject::GO_NYMPH;
			break;
		case DEMON_LORD:
			newEntity->type = GameObject::GO_DEMONLORD;
			break;
	}
	return newEntity;

}

PrototypeFactory::PrototypeFactory()
{

}

PrototypeFactory::~PrototypeFactory()
{
	// delete array here	
	int arrsize = sizeof(Prototypes) / sizeof(Prototypes[0]);
	for (int i = 0; i < arrsize; i++)
	{
		delete Prototypes[i];
		Prototypes[i] = nullptr;
	}
}





