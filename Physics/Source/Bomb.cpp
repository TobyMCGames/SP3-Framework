#include "Bomb.h"
#include "MeshRender.h"

Bomb::Bomb()
	:
	bomb_TimeLeft(bombTimer)
{
	Default_Speed = 20.f;
	damage = 40.f;
	startexTimer = false;
	bombanimation = new SpriteAnimation(CentralMesh::GetInstance()->GetMeshID(CentralMesh::GEO_BOMB));
	bombanimation->AddAnimation("bomb_idle", 0,0);
	bombanimation->AddAnimation("timeticking",1,9);
	bombanimation->PlayAnimation("bomb_idle", -1, 1.f);
	projectileState = IN_MOTION;
}

Bomb::~Bomb()
{
	delete bombanimation;
}

void Bomb::Update(double dt, float m_speed)
{
	if (projectileState != ProjectileState::IDLE_PROJECTILE)
	{
		pos += vel * m_speed * dt;
		vel += GamePhysics::GetInstance()->gravity * m_speed * dt;
	}

	bomb_TimeLeft -= dt * m_speed;
}

void Bomb::Response(GameObject* go)
{
	if (go->type > GameObject::PASSIVE_TILE_START && go->type < GameObject::PASSIVE_TILE_END)
	{
		projectileState = ProjectileState::IDLE_PROJECTILE;
		vel = 0;
	}
}

void Bomb::Render()
{
	if (bombanimation != NULL) {
		MeshRender::GetInstance()->RenderAnimation(
			bombanimation->GetSprite(),
			bombanimation->GetCurFrame(),
			6,
			false
		);
	}
}


void Bomb::init()
{
	min_explosion = pos;
	max_explosion = pos;
	min_explosion.x -= explosionRange;
	min_explosion.y -= explosionRange;
	max_explosion.x += explosionRange;
	max_explosion.y += explosionRange;
	startexTimer = true;
}

