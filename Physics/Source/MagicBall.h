#ifndef MAGICBALL_H
#define MAGICBALL_H

#include "Projectile.h"

class MagicBall : public Projectile
{
private:

public:
	MagicBall();
	~MagicBall();
	virtual void Update(double dt, float GAMESPEED);
	virtual void Response(GameObject* go);
};

#endif