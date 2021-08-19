#include "Arrow.h"
#include "MagicBall.h"

MagicBall::MagicBall()
{
	speed = 5.f;
}

MagicBall::~MagicBall()
{

}

void MagicBall::Update(double dt)
{
	pos += vel * dt;

}

void MagicBall::Response(GameObject* go)
{

}


