#include "Arrow.h"
#include "MagicBall.h"

MagicBall::MagicBall()
{
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
