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
	float speedBoostTimer;
	float attackTimer;
	float StateCounter;
	const float JumpForce = 15;
	const float MaxStateCounter = 1;
	BEHAVIOUR currState;

	float speedBoost;
	void FlipHorizontalDirection(void);
public:
	Zombie();
	~Zombie();
	virtual void Update(double dt, float m_speed);
	virtual void Response(GameObject* go);
};