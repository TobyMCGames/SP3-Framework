#pragma once
#include "Entity.h"
#include "SpriteAnimation.h"

class Spider : public Entity
{
protected:
	enum BEHAVIOUR
	{
		// insert more states here, if applicable
		IDLE,
		PATROL,
		ATTACK,
		CLIMBING,
		NUM_STATES,
	};
	int speedBoostTimer;
	int attackTimer;
	int StateCounter;
	float shootCounter;
	const float JumpForce = 15;
	const int MaxStateCounter = 60;
	const int MaxFirerate = 3;
	Vector3 old_spider_position;
	BEHAVIOUR currState;

	float speedBoost;
	SpriteAnimation* SpiderAnimation;
	//void FlipHorizontalDirection(void);
public:
	Spider();
	~Spider();
	virtual void Update(double dt, float m_speed);
	virtual void Response(GameObject* go);
	virtual void Render();
	virtual void dead();
};