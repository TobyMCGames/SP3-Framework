#ifndef BOMB_H
#define BOMB_H

#include "Projectile.h"
#include <vector>
#include "SpriteAnimation.h"

class Bomb : public Projectile
{
public:
	virtual void Update(double dt, float m_speed);
	virtual void Response(GameObject* go);
	virtual void Render();
	// initted when the bomb collided and reached vel 0
	void init();
	Bomb();
	~Bomb();

private:
	float bomb_TimeLeft;
	const int explosionRange = 2;
	const float bombTimer = 5;
	Vector3 max_explosion;
	Vector3 min_explosion;
	bool startexTimer;
	SpriteAnimation* bombanimation;
};
#endif