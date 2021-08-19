#include "Zombie.h"

Zombie::Zombie()
{
	return;
}

Zombie::~Zombie()
{
	return;
}

void Zombie::Update(double dt)
{
	std::cout << "i am zombie" << std::endl;
	return;
}

void Zombie::Response(GameObject*)
{
	std::cout << "zombie response" << std::endl;
	return;
}