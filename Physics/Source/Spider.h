#pragma once
#include "Entity.h"

class Spider : public Entity
{
protected:
	enum BEHAVIOUR
	{
		// insert more states here
		NUM_STATES,
	};
public:
	Spider();
	~Spider();
	virtual void Update(double dt, float m_speed);
	virtual void Response(GameObject* go);
};