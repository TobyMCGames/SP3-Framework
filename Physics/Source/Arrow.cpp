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
	//std::cout << pos << std::endl;
}

void Arrow::Response(GameObject* go)
{
}
