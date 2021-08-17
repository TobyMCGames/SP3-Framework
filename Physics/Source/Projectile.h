#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "GameObject.h"

class Projectile : public GameObject
{
protected:

public:
	Projectile();
	~Projectile();
	virtual void Update(double dt) = 0;
	virtual void Response(GameObject* go) = 0;
};

#endif