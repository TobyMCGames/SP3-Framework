#include "Arrow.h"

Arrow::Arrow()
{
	speed = 10.f;
}

Arrow::~Arrow()
{
}

void Arrow::Update(double dt)
{
	pos += vel * dt;
}

void Arrow::Response(GameObject* go)
{
}

