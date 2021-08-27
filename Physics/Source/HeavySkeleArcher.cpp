#include "HeavySkeleArcher.h"
#include "GameLevelManager.h"
#include "ProjectileFactory.h"
#include "SkeleArrow.h"

HeavySkeletonArcher::HeavySkeletonArcher()
	:currState(BEHAVIOUR::IDLE),
	HeavySkeletonAnimation(NULL)
{
	health = 70;
	damage = 15;
	Default_Speed = 7;
	StateCounter = 0;
	attackTimer = 0;
	shootCounter = 0;

	HeavySkeletonAnimation = new SpriteAnimation(CentralMesh::GetInstance()->GetMeshID(CentralMesh::GEO_HEAVYSKELEARCHER));
	HeavySkeletonAnimation->AddAnimation("Idle", 3, 3);
	HeavySkeletonAnimation->AddAnimation("Walking", 0, 2);
	//SkeletonAnimation->PlayAnimation("Walking", -1, 1);
}

HeavySkeletonArcher::~HeavySkeletonArcher()
{
	delete HeavySkeletonAnimation;
}

void HeavySkeletonArcher::Update(double dt, float m_speed)
{
	if (currState != IDLE && currState != ATTACK)
	{
		pos.x += vel.x * dt * m_speed;
		HeavySkeletonAnimation->Reset();
		HeavySkeletonAnimation->PlayAnimation("Walking", -1, 1);
	}
	else
	{
		HeavySkeletonAnimation->Reset();
		HeavySkeletonAnimation->PlayAnimation("Idle", 1, 1);
	}

	if (HeavySkeletonAnimation != NULL)
	{
		HeavySkeletonAnimation->Update(dt * m_speed);
	}

	pos.y += vel.y * dt * m_speed;
	switch (currState)
	{	case IDLE:

		if ((pos - Player::GetInstance()->pos).Length() <= 60)
		{
			currState = ATTACK;
			vel.x = 0;
		}
		break;
	case CHASE:
		if ((pos - Player::GetInstance()->pos).Length() <= 80)
		{
			if ((Player::GetInstance()->pos.x - pos.x) > 0)
			{
				vel.x = Default_Speed;
				normal.Set(1.f, -1.f, 0.f);
			}
			else if ((Player::GetInstance()->pos.x - pos.x) < 0)
			{
				vel.x = -Default_Speed;
				normal.Set(-1.f, -1.f, 0.f);
			}
			if ((pos - Player::GetInstance()->pos).Length() <= 60)
			{
				currState = ATTACK;
			}
		}
		if((pos - Player::GetInstance()->pos).Length() >= 100)
		{
			currState = IDLE;
		}
		//StateCounter += dt * m_speed;
		break;
	case ATTACK:
		if ((pos - Player::GetInstance()->pos).Length() <= 60)
		{
			vel.x = 0;
			normal = ((Player::GetInstance()->pos - pos).Normalize());
			if (shootCounter > MaxFirerate)
			{
				CSoundController::GetInstance()->PlaySoundByID(1);
				Projectile* skelearrow =
					ProjectileFactory::GetInstance()->produceProjectile(ProjectileFactory::PTYPE_SKELEARROW,
						pos + (normal * scale.x), normal, Vector3(3.42f, 1.26f, 1.f), normal);
				GameLevelManager::GetInstance()->getcurrentLevel()->getProjectileList()->push_back(skelearrow);

				shootCounter = 0;
			}
			shootCounter += dt * m_speed;
		}
		else
		{
			currState = CHASE;
		}
		break;
	default:
		break;
	}
	vel += GamePhysics::GetInstance()->gravity * dt * m_speed;

}

void HeavySkeletonArcher::Response(GameObject* go)
{
	if (go->type > GameObject::PASSIVE_TILE_START && go->type < GameObject::PASSIVE_TILE_END)
	{
		if (vel.y == 0)
		{
			curLocation = ON_GROUND;
		}

		if (currState == CHASE)
		{
			//check direction
			if (CheckDirection(LEFT) == true)
			{
				curDirection = LEFT;
			}
			else if (CheckDirection(RIGHT) == true)
			{
				curDirection = RIGHT;
			}
			else
			{
				if (curDirection == LEFT)
				{
					curDirection = RIGHT;
				}
				else
					curDirection = LEFT;

			}

			if ((GamePhysics::GetInstance()->GetCollidePos() == COL_LEFT || GamePhysics::GetInstance()->GetCollidePos() == COL_RIGHT) && curLocation == ON_GROUND)
			{
				vel.y += JumpForce;
				curLocation = IN_AIR;
			}
		}
	}
	if (go->type == GameObject::GO_ARROW ||
		go->type == GameObject::GO_MAGICBALL) // player damage zombie
	{
		takeDamage(go->damage);
		go->active = false;

		if (health <= 0)
		{
			CSoundController::GetInstance()->PlaySoundByID(13);
			dead();
		}
		else
		{
			int randHurtSound = rand() % 2;

			if (randHurtSound == 0)
				CSoundController::GetInstance()->PlaySoundByID(11);
			else if (randHurtSound == 1)
				CSoundController::GetInstance()->PlaySoundByID(12);
		}
	}
}

void HeavySkeletonArcher::Render()
{
	if (HeavySkeletonAnimation != NULL) {
		MeshRender::GetInstance()->RenderAnimation(
			HeavySkeletonAnimation->GetSprite(),
			HeavySkeletonAnimation->GetCurFrame(),
			6,
			false
		);
	}
}

void HeavySkeletonArcher::dead()
{
	this->active = false;
}

