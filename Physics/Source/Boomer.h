#pragma once
#include "Entity.h"

class Boomer : public Entity
{
protected:
	enum BEHAVIOUR
	{
		// insert more states here
		NUM_STATES,
	};
public:
	Boomer();
	~Boomer();
	virtual void Update(double dt);
	virtual void Response(GameObject* go);
};