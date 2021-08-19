#ifndef MAGICBALL_H
#define MAGICBALL_H
#pragma once
#include "Projectile.h"

class MagicBall : public Projectile
{
public:
	MagicBall();
	~MagicBall();
	virtual void Update(double dt, float m_speed);
	virtual void Response(GameObject* go);
};

#endif