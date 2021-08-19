#include "Portal.h"

Portal::Portal()
{
	speed = 100.f;
}

Portal::~Portal()
{
}

void Portal::Update(double dt, float GAMESPEED)
{
	pos += vel * dt;
}

void Portal::Response(GameObject* go)
{

}

