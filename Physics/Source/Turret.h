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
	float shootCounter;
	const float MaxFirerate = 1.f;
public:
	Turret();
	~Turret();
	virtual void Update(double dt, float m_speed);
	virtual void Response(GameObject* go);
};