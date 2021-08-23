#pragma once
#include "Entity.h"
#include "SpriteAnimation.h"

class DemonLord : public Entity
{
protected:
	enum BEHAVIOUR
	{
		// insert more states here
		NUM_STATES,
	};

	SpriteAnimation* animation1;
public:
	DemonLord();
	~DemonLord();
	virtual void Update(double dt, float m_speed);
	virtual void Response(GameObject*  go);
	virtual void Render();
	virtual void dead();
};