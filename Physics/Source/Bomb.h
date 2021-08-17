#ifndef BOMB_H
#define BOMB_H

#include "Projectile.h"
class Bomb : public Projectile
{
public:
	virtual void Update(double dt);
	virtual void Response(GameObject*);
	Bomb();
	~Bomb();
};
#endif