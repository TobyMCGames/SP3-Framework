#pragma once
#include "Entity.h"
#include "SpriteAnimation.h"

class HeavySkeletonArcher : public Entity
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

	enum COLLIDEPOS
	{
		NOTHING,
		COL_UP,
		COL_DOWN,
		COL_LEFT,
		COL_RIGHT
	};
	BEHAVIOUR currState;
	float shootCounter;
	float attackTimer;
	float StateCounter;
	const float JumpForce = 15;
	const float MaxStateCounter = 1;
	const int MaxFirerate = 2;

	SpriteAnimation* HeavySkeletonAnimation;
	//void CheckDistance(GameObject* go1, double dt, float m_speed);
	//void CheckDistanceResponse(double dt, float m_speed);
public:
	HeavySkeletonArcher();
	~HeavySkeletonArcher();
	virtual void Update(double dt, float m_speed);
	virtual void Response(GameObject* go);
	virtual void Render();
	virtual void dead();
};