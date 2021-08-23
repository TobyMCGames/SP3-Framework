#ifndef ARROW_H
#define ARROW_H

#include "Projectile.h"

class Arrow : public Projectile
{
public:
	Arrow();
	~Arrow();
	virtual void Update(double dt, float m_speed);
	virtual void Response(GameObject* go);
	virtual void Render();
};

#endif