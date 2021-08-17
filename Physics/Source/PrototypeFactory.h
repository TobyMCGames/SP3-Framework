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
		ZOMBIE,
		SKELE_ARCHER,
		SPIDER,
		BOOMER,
		TURRET,
		DISGUISED_ENEMY,
		DEMON_LORD,

		// leave this last
		NUM_GAMEOBJECTS
	};
	static GameObject* getObject(int choice);
	PrototypeFactory();
	~PrototypeFactory();
private:
	static GameObject* Prototypes[NUM_GAMEOBJECTS];
};

GameObject* PrototypeFactory::Prototypes[] = {
	new Zombie, new SkeletonArcher
};

GameObject* PrototypeFactory::getObject(int choice) {
	return Prototypes[choice]->clone();
}

PrototypeFactory::PrototypeFactory()
{

}

PrototypeFactory::~PrototypeFactory()
{
	// delete array here
	delete Prototypes;
}
