#include "Zombie.h"
#include "GameLevelManager.h"

Zombie::Zombie()
{
	Default_Speed = 15;
}

Zombie::~Zombie()
{
	//return;
}

void Zombie::Update(double dt, float m_speed)
{
	vel.x = 15;
	pos += vel * dt * m_speed;
}

void Zombie::Response(GameObject* go)
{
	std::cout << "zombie response" << std::endl;
	//return;
}