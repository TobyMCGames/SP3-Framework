#include "InteractableFactory.h"

Interactables* InteractableFactory::produceInteractable(INTERACTABLES_TYPES InteractableType, Vector3 pos, Vector3 scale, Vector3 normal)
{
	Interactables* newInteractable = nullptr;
	switch (InteractableType)
	{
	case PTYPE_BOW_STATION:
		newInteractable = new WeaponStation(GameObject::WEAPON_STATION_BOW);
		break;
	case PTYPE_STAFF_STATION:
		newInteractable = new WeaponStation(GameObject::WEAPON_STATION_STAFF);
		break;
	case PTYPE_PORTAL_STATION:
		newInteractable = new WeaponStation(GameObject::WEAPON_STATION_PORTAL);
		break;	
	//portal gates
	case PTYPE_PORTAL_ENTRANCE:
		newInteractable = new PortalGate(GameObject::PORTAL_GATE_ENTRANCE);
		break;
	case PTYPE_PORTAL_EXIT:
		newInteractable = new PortalGate(GameObject::PORTAL_GATE_EXIT);
		break;
	case PTYPE_BOMB_CRATE:
		newInteractable = new BombCrate(GameObject::BOMB_CRATE);
		break;
	case PTYPE_TREE_SEEDS:
		newInteractable = new TreeSeeds(GameObject::TREE_SEEDS);
		break;
	case PTYPE_TREE:
		newInteractable = new Tree(GameObject::TREE_SAPLING_TILE);
		break;
	case PTYPE_VINE_SEEDS:
		newInteractable = new VineSeeds(GameObject::VINE_SEEDS);
		break;
	case PTYPE_COIN:
		newInteractable = new Coin(GameObject::COIN);
		break;
	case PTYPE_HEALTHPOTION:
		newInteractable = new HealthPotion(GameObject::HEALTHPOTION);
		break;
	case PTYPE_WARP_GATE:
		newInteractable = new PortalGate(GameObject::WARP_GATE);
		break;
	case PTYPE_KEY:
		newInteractable = new key(GameObject::GO_KEY);
		break;
	}
	if (newInteractable != nullptr)
	{
		newInteractable->pos = pos;
		newInteractable->scale = scale;
		newInteractable->normal = normal;
		newInteractable->active = true;
	}
	return newInteractable;
}
