#include "Archbishop_ball.h"
#include "CentralMesh.h"
#include "MeshRender.h"
#include "ProjectileFactory.h"
#include "GameLevelManager.h"
#include "Player.h"

ArchBishopBall::ArchBishopBall()
{
	Default_Speed = 40.f;
	damage = 25;
}

ArchBishopBall::~ArchBishopBall()
{

}

void ArchBishopBall::Update(double dt,float m_speed)
{
	this->pos += vel * dt * m_speed;
}

void ArchBishopBall::Response(GameObject* go)
{

}
void ArchBishopBall::Render()
{
	
}