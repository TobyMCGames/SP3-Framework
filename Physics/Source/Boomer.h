#pragma once
#include "Entity.h"
#include "SpriteAnimation.h"

class Boomer : public Entity
{
protected:
	enum BEHAVIOUR
	{
		// insert more states here
		IDLE,
		PATROL,
		ATTACK,
		EXPLODE,
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
	float attackTimer;
	float StateCounter;
	const float MaxStateCounter = 3;
	const float JumpForce = 15;
	float explodeTimer;
	const float maxExplodeTime = 2.5;
	SpriteAnimation* BoomerAnimation;

public:
public:
	Boomer();
	~Boomer();
	virtual void Update(double dt, float m_speed);
	virtual void Response(GameObject* go);
	virtual void Render();
	virtual void dead();
};