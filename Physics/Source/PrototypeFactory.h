#include "Zombie.h"
#include "SkeletonArcher.h"

class PrototypeFactory
{
public:
	enum GAMEOBJECTS
	{
		ZOMBIE,
		SKELE_ARCHER,

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
