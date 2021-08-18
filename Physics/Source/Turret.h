#pragma once
#include "Entity.h"

class Turret : public Entity
{
protected:
	enum BEHAVIOUR
	{
		// insert more states here
		NUM_STATES,
	};
public:
	Turret();
	~Turret();
	virtual void Update(double dt);
	virtual void Response(GameObject* go);
};