#pragma once
#include "Entity.h"

class SkeletonArcher : public Entity
{
protected:
	enum BEHAVIOUR
	{
		// insert more states here
		IDLE,
		CHASE,
		ATTACK,
		NUM_STATES,
	};
	BEHAVIOUR currState;
	float shootCounter;
	float attackTimer;
	float StateCounter;
	const float JumpForce = 15;
	const float MaxStateCounter = 1;
	const int MaxFirerate = 5;
public:
	SkeletonArcher();
	~SkeletonArcher();
	virtual void Update(double dt, float m_speed);
	virtual void Response(GameObject* go);
	virtual void dead();
};