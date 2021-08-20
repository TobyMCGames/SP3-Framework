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
