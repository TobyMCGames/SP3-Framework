#ifndef MAGICBALL_H
#define MAGICBALL_H
#pragma once
#include "Projectile.h"

class MagicBall : public Projectile
{
private:

public:
	MagicBall();
	~MagicBall();
	virtual void Update(double dt);
	virtual void Response(GameObject* go);

};

#endif