#include "Zombie.h"

Zombie::Zombie()
{
	return;
}

Zombie::~Zombie()
{
	return;
}

void Zombie::Update(double dt, float m_speed)
{
	std::cout << "i am zombie" << std::endl;
	return;
}

void Zombie::Response(GameObject* go)
{
	std::cout << "zombie response" << std::endl;
	return;
}