#include "Arrow.h"
#include "MagicBall.h"

MagicBall::MagicBall()
{
	speed = 50.f;
}

MagicBall::~MagicBall()
{

}

void MagicBall::Update(double dt, float GAMESPEED)
{
	pos += vel * dt * GAMESPEED;
}

void MagicBall::Response(GameObject* go)
{

}


