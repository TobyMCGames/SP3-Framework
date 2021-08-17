#ifndef ARROW_H
#define ARROW_H
#pragma once
#include "Projectile.h"

class Arrow : public Projectile
{
public:
	Arrow();
	~Arrow();
	virtual void Update(double dt);
	virtual void Response(GameObject* go);
};

#endif