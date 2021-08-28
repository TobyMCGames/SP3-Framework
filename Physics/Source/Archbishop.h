#ifndef Archbishop_H
#define Archbishop_H
#include "Entity.h"
#include "SpriteAnimation.h"

class Archbishop : public Entity
{
private:
	SpriteAnimation* firstform;
	enum bishop_states
	{
		IDLE,
		SPIN_ATTACK,
		SPINING_KAMIKAZE,
		TRACK_PLAYER,
		DISARM_PLAYER,
		FLEE,
	};
	bishop_states current_state;
	float rotation;
	bool inAir;
	Vector3 targetposition;
	int stateCounter;

public:
	Archbishop();
	~Archbishop();
	virtual void Update(double dt, float m_speed);
	virtual void Response(GameObject* go);
	virtual void Render();
	virtual void dead();
};

#endif
