#ifndef ENTITY_H
#define ENTITY_H
#include "GameObject.h"
//#include "Projectile.h"

class Entity : public GameObject
{
protected:
	enum STATES
	{
		STATE_NORMAL,
		STATE_INVINCIBLE,
		STATE_FROZEN,
		NUM_STATES,
	};

	Vector3 projectile;
public:
	Entity();
	~Entity();
	
	virtual void Update(double dt) = 0;
	virtual void Response(GameObject*) = 0;
};
#endif

