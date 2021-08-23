#ifndef BOMB_H
#define BOMB_H

#include "Projectile.h"
class Bomb : public Projectile
{
public:
	virtual void Update(double dt, float m_speed);
	virtual void Response(GameObject* go);
	virtual void Render();
	Bomb();
	~Bomb();
};
#endif