#pragma once
#include "Entity.h"

class DemonLord : public Entity
{
protected:
	enum BEHAVIOUR
	{
		// insert more states here
		NUM_STATES,
	};
public:
	DemonLord();
	~DemonLord();
	virtual void Update(double dt, float m_speed);
	virtual void Response(GameObject*  go);
	virtual void dead();
};