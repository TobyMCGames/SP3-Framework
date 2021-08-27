#include "Turret.h"
#include "GameLevelManager.h"
#include "ProjectileFactory.h"

Turret::Turret()
	:TurretAnimation(NULL)
{
	shootCounter = 0.f;
	bulletCounter = 0;
	waitTimer = 0.f;
	wait = false;
	health = 200;

	TurretAnimation = new SpriteAnimation(CentralMesh::GetInstance()->GetMeshID(CentralMesh::GEO_TURRET));
	TurretAnimation->AddAnimation("Idle", 3, 3);
	TurretAnimation->AddAnimation("Shooting", 0, 2);
}

Turret::~Turret()
{
	delete TurretAnimation;
}

void Turret::Update(double dt, float m_speed)
{
	if (TurretAnimation != NULL)
	{
		TurretAnimation->Update(dt * m_speed);
	}

	if ((Player::GetInstance()->pos.x - pos.x) < 0 && (Player::GetInstance()->pos - pos).Length() <= 40 
		&& (Player::GetInstance()->pos.y - pos.y) < 5 && (Player::GetInstance()->pos.y - pos.y) > -2)
	{
		if (waitTimer >= 3)
		{
			bulletCounter = 0;
			waitTimer = 0;
			wait = false;
		}
		if (bulletCounter >= 3)
		{
			waitTimer += dt * m_speed;
			wait = true;
		}
		else if (shootCounter > MaxFirerate && !wait)
		{
			CSoundController::GetInstance()->PlaySoundByID(14);
			Projectile* bullet =
				ProjectileFactory::GetInstance()->produceProjectile(ProjectileFactory::PTYPE_TURRETBULLET,
					pos - (normal * scale.x), -normal, scale, normal);
			GameLevelManager::GetInstance()->getcurrentLevel()->getProjectileList()->push_back(bullet);
			TurretAnimation->Reset();
			TurretAnimation->PlayAnimation("Shooting", 1, MaxFirerate);
			bulletCounter++;
			shootCounter = 0.f;
		}
		shootCounter += dt * m_speed;
	}
	else
	{
		TurretAnimation->Reset();
		TurretAnimation->PlayAnimation("Idle", 1, 1.5);
		wait = false;
		shootCounter = 0.f;
		bulletCounter = 0;
		waitTimer = 0.f;
	}

}

void Turret::Response(GameObject* go)
{
	if (go->type == GameObject::GO_ARROW ||
		go->type == GameObject::GO_MAGICBALL) // player damage zombie
	{
		takeDamage(go->damage);
		go->active = false;

		if (health <= 0)
		{
			//play death sound
			CSoundController::GetInstance()->PlaySoundByID(16);
			dead();
		}
		else
		{
			//play damaged sounds
			CSoundController::GetInstance()->PlaySoundByID(15);
		}
	}
}

void Turret::Render()
{
	if (TurretAnimation != NULL) {
		MeshRender::GetInstance()->RenderAnimation(
			TurretAnimation->GetSprite(),
			TurretAnimation->GetCurFrame(),
			6,
			false
		);
	}
}

void Turret::dead()
{
	this->active = false;
}

