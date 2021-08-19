#ifndef SKELEARROW_H
#define SKELEARROW_H
#pragma once
#include "Projectile.h"

class SkeleArrow : public Projectile
{

public:
	SkeleArrow();
	~SkeleArrow();
	virtual void Update(double dt);
	virtual void Response(GameObject* go);

};

#endif
