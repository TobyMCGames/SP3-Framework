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
	float waitTimer;
	const float MaxFirerate = 0.5f;
	bool wait;
	int bulletCounter;
public:
	Turret();
	~Turret();
	virtual void Update(double dt, float m_speed);
	virtual void Response(GameObject* go);
	virtual void dead();
};