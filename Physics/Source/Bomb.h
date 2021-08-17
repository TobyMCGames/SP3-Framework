#ifndef BOMB_H
#define BOMB_H

#include "Projectile.h"
class Bomb : public GameObject
{
public:
	virtual void Update(double dt);
	virtual void Response(GameObject*);
	Bomb();
	~Bomb();
};
#endif