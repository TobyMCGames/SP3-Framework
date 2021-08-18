#include "Arrow.h"

Arrow::Arrow()
{
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
