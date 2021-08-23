#include "Boomer.h"

Boomer::Boomer()
{
	return;
}

Boomer::~Boomer()
{
	return;
}

void Boomer::Update(double dt, float m_speed)
{
	return;
}

void Boomer::Response(GameObject* go)
{
	std::cout << "Boomer response" << std::endl;
	return;
}

void Boomer::Render()
{
}

void Boomer::dead()
{
	this->active = false;
}
