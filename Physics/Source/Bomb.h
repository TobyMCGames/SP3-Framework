#ifndef BOMB_H
#define BOMB_H

#include "Projectile.h"
#include <vector>
#include "SpriteAnimation.h"

class Bomb : public Projectile
{
public:
	const float explosionTime = 5.0f;
	virtual void Update(double dt, float m_speed);
	virtual void Response(GameObject* go);
	virtual void Render();
	Bomb();
	~Bomb();
private:
	bool primed;
	float TimeLeft;
	SpriteAnimation* bombAnimation;
};
#endif