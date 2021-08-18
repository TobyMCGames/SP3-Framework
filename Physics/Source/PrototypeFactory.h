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

	static Entity* getObject(int choice);
	PrototypeFactory();
	~PrototypeFactory();
private:
	static Entity* Prototypes[NUM_GAMEOBJECTS];
};

Entity* PrototypeFactory::Prototypes[] = {
	new Zombie, new SkeletonArcher,new Spider, new Boomer,new Turret,new DisguisedEnemy,new DemonLord
};

Entity* PrototypeFactory::getObject(int choice) {
	return Prototypes[choice]->clone();
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





