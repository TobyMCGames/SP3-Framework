#pragma once
#include "Entity.h"
#include "SpriteAnimation.h"

class DisguisedEnemy : public Entity
{
protected:
	enum BEHAVIOUR
	{
		// insert more states here
		IDLE,
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
	float attackTimer;
	float StateCounter;
	const float JumpForce = 15;
	const float MaxStateCounter = 1;
	bool jump = false;
	float disguiseAnimTimer;
	const float maxanimtime = 1;
	bool hasdisguised;
	float attackSoundTimer;
	float idleSoundTimer;
	BEHAVIOUR currState;

	SpriteAnimation* NymphAnimation;

public:
	DisguisedEnemy();
	~DisguisedEnemy();
	virtual void Update(double dt, float m_speed);
	virtual void Response(GameObject* go);
	virtual void Render();
	virtual void dead();
};