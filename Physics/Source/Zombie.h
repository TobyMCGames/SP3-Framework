#pragma once
#include "Entity.h"
#include "SpriteAnimation.h"

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

	enum COLLIDEPOS
	{
		NOTHING,
		COL_UP,
		COL_DOWN,
		COL_LEFT,
		COL_RIGHT
	};
	float speedBoostTimer;
	float attackTimer;
	float StateCounter;
	const float JumpForce = 15;
	const float MaxStateCounter = 1;
	bool jump = false;
	float attackSoundTimer;
	float idleSoundTimer;
	BEHAVIOUR currState;
	float speedBoost;
	void FlipHorizontalDirection(void);

	SpriteAnimation* ZombieAnimation;
public:
	Zombie();
	~Zombie();
	virtual void Update(double dt, float m_speed);
	virtual void Response(GameObject* go);
	virtual void Render();
	virtual void dead();
};