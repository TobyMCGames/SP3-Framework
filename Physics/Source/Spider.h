#pragma once
#include "Entity.h"

class Spider : public Entity
{
protected:
	enum BEHAVIOUR
	{
		// insert more states here, if applicable
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
	//void FlipHorizontalDirection(void);
public:
	Spider();
	~Spider();
	virtual void Update(double dt, float m_speed);
	virtual void Response(GameObject* go);
	virtual void Render();
	virtual void dead();
};