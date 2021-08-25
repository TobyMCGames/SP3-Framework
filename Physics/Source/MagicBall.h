#ifndef MAGICBALL_H
#define MAGICBALL_H

#include "Projectile.h"
#include "SpriteAnimation.h"

class MagicBall : public Projectile
{
private:
	SpriteAnimation* FadingAnimation;
	float timer;
public:
	MagicBall();
	~MagicBall();
	virtual void Update(double dt, float m_speed);
	virtual void Response(GameObject* go);
	virtual void Render();
};

#endif