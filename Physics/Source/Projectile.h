#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "GameObject.h"
#include "Prototype.h"

class Projectile : public GameObject, public Prototype<Projectile>
{
protected:
	float speed;
public:
	Projectile();
	~Projectile();
	virtual void Update(double dt);
	virtual void Response(GameObject* go);
	float getProjectileSpeed();
};

#endif