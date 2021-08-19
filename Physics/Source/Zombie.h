#pragma once
#include "Entity.h"

class Zombie : public Entity
{
protected:
	enum BEHAVIOUR
	{
		// insert more states here
		IDLE,
		PATROL,
		ATTACK,
		NUM_STATES,
	};
	int StateCounter;
	const int MaxStateCounter = 60;
	BEHAVIOUR currState;
public:
	Zombie();
	~Zombie();
	virtual void Update(double dt, float m_speed);
	virtual void Response(GameObject* go);
};