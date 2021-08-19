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
	static Vector3 maxpoint = Vector3(GameLevelManager::GetInstance()->getcurrentLevel()->getworldWidth(),
		GameLevelManager::GetInstance()->getcurrentLevel()->getworldHeight(),
		pos.z);
	if (pos.x + Default_Speed * dt < maxpoint.x - (scale.x / 2))
		vel.x = Default_Speed;
	cout << pos << endl;
}

void Zombie::Response(GameObject* go)
{
	std::cout << "zombie response" << std::endl;
	//return;
}