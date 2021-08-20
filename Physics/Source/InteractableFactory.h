#pragma once
#include "SingletonPattern.h"
#include "Interactables.h"

class InteractableFactory : public SingletonPattern<InteractableFactory>
{
public:
	enum INTERACTABLES_TYPES
	{
		PTYPE_BOW_STATION,
		PTYPE_STAFF_STATION,
		PTYPE_PORTAL_STATION,
		NUM_PROJECTILES,
	};
	Interactables* produceInteractable(INTERACTABLES_TYPES InteractableType, Vector3 pos, Vector3 scale, Vector3 normal);
};




