#ifndef ENTITY_H
#define ENTITY_H
#include "AdvanceGO.h"
#include <vector>
#include "Projectile.h"

class Entity :public AdvanceGO
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
		IN_AIR,
	};

	enum DIRECTION
	{
		LEFT,
		RIGHT,
	};

	STATES curState;
	LOCATION curLocation;
	DIRECTION curDirection;

public:
	Entity();
	~Entity();
	virtual void Update(double dt, float m_speed)=0;
	virtual void Response(GameObject* go)=0;
	bool CheckDirection(DIRECTION direction);

};
#endif

