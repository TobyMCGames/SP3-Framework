#ifndef PORTAL_H
#define PORTAL_H

#include "Projectile.h"
class Portal : public Projectile
{
private:

public:
	virtual void Update(double dt, float m_speed);
	virtual void Response(GameObject* go);
	virtual void Render();
	Portal();
	~Portal();
};
#endif