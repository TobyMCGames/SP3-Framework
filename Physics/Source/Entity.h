#ifndef ENTITY_H
#define ENTITY_H
#include "GameObject.h"
#include <vector>
#include "Projectile.h"

class Entity : public GameObject, public Prototype<Entity>
{
protected:
	enum STATES
	{
		STATE_NORMAL,
		STATE_INVINCIBLE,
		STATE_FROZEN,
		NUM_STATES,
	};

	enum LOCATION
	{
		ON_GROUND,
		IN_AIR
	};

	STATES curState;
	LOCATION curLocation;


public:
	Entity();
	~Entity();

	std::vector<Projectile*> projectileVector;
	virtual void Update(double dt);
	virtual void Response(GameObject* go);
};
#endif

