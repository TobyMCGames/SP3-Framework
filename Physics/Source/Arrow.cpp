#include "Arrow.h"

Arrow::Arrow()
{
	speed = 30.f;
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

}

