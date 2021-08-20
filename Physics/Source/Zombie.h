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
	int speedBoostTimer;
	int attackTimer;
	int StateCounter;
	const float JumpForce = 15;
	const int MaxStateCounter = 60;
	BEHAVIOUR currState;

	float speedBoost;
	void FlipHorizontalDirection(void);
public:
	Zombie();
	~Zombie();
	virtual void Update(double dt, float m_speed);
	virtual void Response(GameObject* go);
};