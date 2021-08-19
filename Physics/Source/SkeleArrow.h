#ifndef SKELEARROW_H
#define SKELEARROW_H

#include "Projectile.h"

class SkeleArrow : public Projectile
{

public:
	SkeleArrow();
	~SkeleArrow();
	virtual void Update(double dt, float m_speed);
	virtual void Response(GameObject* go);

};

#endif
