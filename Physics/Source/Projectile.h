#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "GameObject.h"
#include "Prototype.h"
#include "GamePhysics.h"

class Projectile : public GameObject, public Prototype<Projectile>
{
protected:

public:
	Projectile();
	~Projectile();
	virtual void Update(double dt, float m_speed);
	virtual void Response(GameObject* go);
};

#endif