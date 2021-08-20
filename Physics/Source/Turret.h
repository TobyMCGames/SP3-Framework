#pragma once
#include "Entity.h"

class Turret : public Entity
{
protected:
	enum BEHAVIOUR
	{
		// insert more states here
		SCANNING,
		SHOOT,
		NUM_STATES,
	};
	int shootCounter;
	const int MaxFirerate = 20;
public:
	Turret();
	~Turret();
	virtual void Update(double dt, float m_speed);
	virtual void Response(GameObject* go);
};