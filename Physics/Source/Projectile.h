#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "AdvanceGO.h"
#include "GamePhysics.h"

class Projectile : public AdvanceGO
{
protected:
	float speed;
public:
	Projectile();
	~Projectile();
	virtual void Update(double dt, float m_speed) = 0;
	virtual void Response(GameObject* go) = 0;
	float getProjectileSpeed();
};

#endif