#ifndef TURRETBULLET_H
#define TURRETBULLET_H

#include "Projectile.h"
class TurretBullet : public GameObject
{
public:
	virtual void Update(double dt);
	virtual void Response(GameObject*);
	TurretBullet();
	~TurretBullet();
};
#endif