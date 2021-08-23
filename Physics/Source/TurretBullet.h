#ifndef TURRETBULLET_H
#define TURRETBULLET_H

#include "Projectile.h"
class TurretBullet : public Projectile
{

public:
	virtual void Update(double dt, float m_speed);
	virtual void Response(GameObject* go);
	virtual void Render();
	TurretBullet();
	~TurretBullet();
};
#endif