#ifndef SPIDERPOISON_H
#define SPIDERPOISON_H

#include "Projectile.h"
class SpiderPoison : public Projectile
{
public:
	virtual void Update(double dt, float m_speed);
	virtual void Response(GameObject*);
	SpiderPoison();
	~SpiderPoison();
};
#endif