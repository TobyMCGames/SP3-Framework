#ifndef PORTAL_H
#define PORTAL_H

#include "Projectile.h"
class Portal : public GameObject
{
public:
	virtual void Update(double dt);
	virtual void Response(GameObject*);
	Portal();
	~Portal();
};
#endif