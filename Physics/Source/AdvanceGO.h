#pragma once
#include "GameObject.h"

class AdvanceGO : public GameObject
{
public:
	AdvanceGO() {};
	~AdvanceGO() {};
	virtual void Update(double dt, float m_speed) = 0;
	virtual void Response(GameObject* go) = 0;
};