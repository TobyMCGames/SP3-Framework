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
		PTYPE_PORTAL_ENTRANCE,
		PTYPE_PORTAL_EXIT,
		PTYPE_WARP_GATE,
		PTYPE_TREE_SEEDS,
		PTYPE_TREE,
		PTYPE_COIN,
		PTYPE_HEALTHPOTION,
		PTYPE_VINE_SEEDS,
		PTYPE_BOMB_CRATE,
		NUM_PROJECTILES,
	};
	Interactables* produceInteractable(INTERACTABLES_TYPES InteractableType, Vector3 pos, Vector3 scale, Vector3 normal = Vector3(1,0,0));
};




