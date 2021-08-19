#ifndef DEMONBALL_H
#define DEMONBALL_H
#pragma once
#include "Projectile.h"

class DemonBall : public Projectile
{
public:
	DemonBall();
	~DemonBall();
	virtual void Update(double dt, float m_speed);
	virtual void Response(GameObject* go);
};

#endif
