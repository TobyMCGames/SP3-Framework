#include "SkeletonArcher.h"
#include "GameLevelManager.h"
#include "ProjectileFactory.h"
#include "SkeleArrow.h"

SkeletonArcher::SkeletonArcher()
	:currState(BEHAVIOUR::IDLE)
{
	health = 45;
	damage = 5;
	Default_Speed = 5;
	StateCounter = 0;
	attackTimer = 0;
	shootCounter = 0;
}

SkeletonArcher::~SkeletonArcher()
{
}

void SkeletonArcher::Update(double dt, float m_speed)
{
	//cout << (pos - Player::GetInstance()->pos).Length() << endl;
	if (currState != IDLE)
		pos.x += vel.x * dt * m_speed;
	pos.y += vel.y * dt * m_speed;
	switch (currState)
	{
	case IDLE:
		if ((pos - Player::GetInstance()->pos).Length() <= 40)
		{
			currState = ATTACK;
			cout << "switching to Attack state" << endl;
			vel.x = 0;
		}
		break;
	case CHASE:
		if ((pos - Player::GetInstance()->pos).Length() <= 60)
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
			if (((Player::GetInstance()->pos.y - pos.y) > 0) && curLocation == Entity::ON_GROUND)
			{
				vel.y += JumpForce;
				curLocation = IN_AIR;
			}
		}
		if((pos - Player::GetInstance()->pos).Length() <= 40)
		{
			currState = IDLE;
		}
		//StateCounter += dt * m_speed;
		break;
	case ATTACK:
		if ((pos - Player::GetInstance()->pos).Length() <= 40)
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
			cout << "switching to Chase state" << endl;
		}
		break;
	default:
		break;
	}
	vel += GamePhysics::GetInstance()->gravity * dt * m_speed;

}

void SkeletonArcher::Response(GameObject* go)
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

void SkeletonArcher::Render()
{
}

void SkeletonArcher::dead()
{
	this->active = false;
}

