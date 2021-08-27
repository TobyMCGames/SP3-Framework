#pragma once
#include "Entity.h"
#include "SpriteAnimation.h"

class DemonLord : public Entity
{
protected:
	enum BEHAVIOUR
	{
		// insert more states here
		ARRIVAL,
		IDLE,
		ATTACK_DEMONBALL,
		RETREAT,
		NUM_STATES,
	};

	SpriteAnimation* Floating;
	SpriteAnimation* Charging;
	BEHAVIOUR curFSM;

	float portalSpinTime;
	Vector3 portalScale;

	float FSMcounter;
public:
	DemonLord();
	~DemonLord();
	virtual void Update(double dt, float m_speed);
	virtual void Response(GameObject*  go);
	virtual void Render();
	virtual void dead();
};