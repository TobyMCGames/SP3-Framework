#include "Bomb.h"
#include "MeshRender.h"

Bomb::Bomb()
	:primed(false),
	TimeLeft(0.f)
{
	Default_Speed = 20.f;
	damage = 50.f;
	projectileState = IN_MOTION;
	bombAnimation = new SpriteAnimation(CentralMesh::GetInstance()->GetMeshID(CentralMesh::GEO_BOMB));
	bombAnimation->AddAnimation("Bomb_Explosion", 0, 8);
}

Bomb::~Bomb()
{
	delete bombAnimation;
}

void Bomb::Update(double dt, float m_speed)
{
	if (projectileState != ProjectileState::IDLE_PROJECTILE)
	{
		pos += vel * m_speed * dt;
		vel += GamePhysics::GetInstance()->gravity * m_speed * dt;
	}
	else if (primed == true)
	{
		TimeLeft -= dt * m_speed;
		bombAnimation->Update(dt*m_speed);
	}
}

void Bomb::Response(GameObject* go)
{
	if (go->type > GameObject::PASSIVE_TILE_START && go->type < GameObject::PASSIVE_TILE_END)
	{
		projectileState = ProjectileState::IDLE_PROJECTILE;
		vel = 0;
		if (primed == false)
		{
			bombAnimation->PlayAnimation("Bomb_Explosion", 1,explosionTime+2);
			TimeLeft = explosionTime;
		}

		if (TimeLeft <= 0)
		{
			this->active = false;
			go->active = false;
		}
		else 
		{
			primed = true;
		}
	}
}

void Bomb::Render()
{
	if (bombAnimation!= NULL) {
		MeshRender::GetInstance()->RenderAnimation(
			bombAnimation->GetSprite(),
			bombAnimation->GetCurFrame(),
			9,
			false
		);
	}
}



