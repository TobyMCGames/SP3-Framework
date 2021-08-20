#pragma once
#include "Entity.h"

class SkeletonArcher : public Entity
{
protected:
	enum BEHAVIOUR
	{
		// insert more states here
		NUM_STATES,
	};
public:
	SkeletonArcher();
	~SkeletonArcher();
	virtual void Update(double dt, float m_speed);
	virtual void Response(GameObject* go);
	virtual void dead();
};