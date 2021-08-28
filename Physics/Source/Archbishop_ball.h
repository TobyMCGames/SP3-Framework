#pragma once
#include "Entity.h"
#include "SpriteAnimation.h"
#include "Projectile.h"
class ArchBishopBall : public Projectile
{
public:
	ArchBishopBall();
	~ArchBishopBall();
	virtual void Update(double dt, float m_speed);
	virtual void Response(GameObject*  go);
	virtual void Render();

};