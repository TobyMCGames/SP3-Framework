#include "Arrow.h"
#include "MagicBall.h"
#include "CentralMesh.h"
#include "MeshRender.h"

MagicBall::MagicBall()
	: FadingAnimation(NULL)
	, timer(3.f)
{
	damage = 35;
	Default_Speed = 20.f;
	FadingAnimation = new SpriteAnimation(CentralMesh::GetInstance()->GetMeshID(CentralMesh::GEO_MAGICBALL));
	FadingAnimation->AddAnimation("Fading", 0, 5);
	FadingAnimation->PlayAnimation("Fading", 1, timer);
}

MagicBall::~MagicBall()
{
	delete FadingAnimation;
}

void MagicBall::Update(double dt, float m_speed)
{
	pos += vel * dt * m_speed;

	timer -= dt * m_speed;
	if (timer < 0)
		active = false;

	FadingAnimation->Update(dt * m_speed);
}

void MagicBall::Response(GameObject* go)
{
	if ((go->type > GameObject::PASSIVE_TILE_START &&
		go->type < GameObject::PASSIVE_TILE_END) || (go->type == GameObject::GO_TURRET) || (go->type == GameObject::GO_ZOMBIE))
		this->active = false;
}

void MagicBall::Render()
{
	if (FadingAnimation != NULL) {
		MeshRender::GetInstance()->RenderAnimation(
			FadingAnimation->GetSprite(),
			FadingAnimation->GetCurFrame(),
			6,
			false
		);
	}
}


