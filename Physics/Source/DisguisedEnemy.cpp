#include "DisguisedEnemy.h"

DisguisedEnemy::DisguisedEnemy()
{
	return;
}

DisguisedEnemy::~DisguisedEnemy()
{
	return;
}

void DisguisedEnemy::Update(double dt, float m_speed)
{
	return;
}

void DisguisedEnemy::Response(GameObject* go)
{
	std::cout << "DEnemy response" << std::endl;
	return;
}

void DisguisedEnemy::Render()
{
}

void DisguisedEnemy::dead()
{
	this->active = false;
}

