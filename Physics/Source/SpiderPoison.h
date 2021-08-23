#ifndef SPIDERPOISON_H
#define SPIDERPOISON_H

#include "Projectile.h"

// this file contains code for cobwebs shot by spiders. The file is named SpiderPoison as that was our initial idea

class SpiderPoison : public Projectile
{

public:
	virtual void Update(double dt, float m_speed);
	virtual void Response(GameObject* go);
	virtual void Render();
	SpiderPoison();
	~SpiderPoison();
};
#endif