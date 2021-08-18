#ifndef ENTITY_H
#define ENTITY_H
#include "GameObject.h"
#include "Prototype.h"

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


	Vector3 projectile;
public:
	Entity();
	~Entity();
	
	virtual void Update(double dt);
	virtual void Response(GameObject* go);
};
#endif

