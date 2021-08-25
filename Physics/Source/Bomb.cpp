#include "Bomb.h"

Bomb::Bomb()
	:
	bomb_TimeLeft(bombTimer)
{
	Default_Speed = 10.f;
	damage = 40.f;
}

Bomb::~Bomb()
{
}

void Bomb::Update(double dt, float m_speed)
{
	bomb_TimeLeft -= dt * m_speed;
	if (bomb_TimeLeft <= 0)
	{
		
	}
}

void Bomb::Response(GameObject* go)
{
}

void Bomb::Render()
{
}

void Bomb::explode(std::vector<GameObject*> tilelist, std::vector<GameObject*> entityList)
{
	for (int i = 0; i < tilelist.size(); i++)
	{
		
	}
}

