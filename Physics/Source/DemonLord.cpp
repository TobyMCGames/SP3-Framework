#include "DemonLord.h"

DemonLord::DemonLord()
	: animation1(NULL)
{
	return;
}

DemonLord::~DemonLord()
{
	return;
}

void DemonLord::Update(double dt,float m_speed)
{
	return;
}

void DemonLord::Response(GameObject* go) 
{
	std::cout << "Dlord response" << std::endl;
	return;
}

void DemonLord::Render()
{
}

void DemonLord::dead()
{
	this->active = false;
}

