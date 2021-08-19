#ifndef DEMONBALL_H
#define DEMONBALL_H
#pragma once
#include "Projectile.h"

class DemonBall : public Projectile
{
private:

public:
	DemonBall();
	~DemonBall();
	virtual void Update(double dt);
	virtual void Response(GameObject* go);

};

#endif
