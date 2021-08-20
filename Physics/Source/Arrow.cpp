#include "Arrow.h"

Arrow::Arrow()
{
	speed = 30.f;
	scale.Set(5.f,2, 1);
}

Arrow::~Arrow()
{

}

void Arrow::Update(double dt, float GAMESPEED)
{
	pos += vel * dt * GAMESPEED;
	vel += (GamePhysics::GetInstance()->gravity) * dt * GAMESPEED;
	normal = vel.Normalized();
}

void Arrow::Response(GameObject* go)
{
	this->active = false;
}

