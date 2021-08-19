#ifndef MAGICBALL_H
#define MAGICBALL_H

#include "Projectile.h"

class MagicBall : public Projectile
{
private:

public:
	MagicBall();
	~MagicBall();
	virtual void Update(double dt, float m_speed);
	virtual void Response(GameObject* go);

};

#endif