#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "AdvanceGO.h"
#include "GamePhysics.h"

class Projectile : public AdvanceGO
{
	
public:
	enum ProjectileState
	{
		IN_MOTION,
		IDLE_PROJECTILE
	};

	Projectile();
	~Projectile();
	virtual void Update(double dt, float m_speed) = 0;
	virtual void Response(GameObject* go) = 0;
	virtual void Render() = 0;
	virtual ProjectileState getProjectilestate();

protected:
	ProjectileState projectileState;

};

#endif