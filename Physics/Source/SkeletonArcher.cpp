#include "SkeletonArcher.h"
#include "GameLevelManager.h"
#include "ProjectileFactory.h"
#include "SkeleArrow.h"

SkeletonArcher::SkeletonArcher()
	:currState(BEHAVIOUR::IDLE)
{
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
	cout << (pos - Player::GetInstance()->pos).Length() << endl;
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
				normal.Set(1.f, 0.f, 0.f);
			}
			else if ((Player::GetInstance()->pos.x - pos.x) < 0)
			{
				vel.x = -Default_Speed;
				normal.Set(-1.f, 0.f, 0.f);
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
				Projectile* skelearrow =
					ProjectileFactory::GetInstance()->produceProjectile(ProjectileFactory::PTYPE_SKELEARROW,
						pos + (normal * scale.x), normal, scale, normal);
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
	if (go->type == GameObject::GO_ARROW)
	{
		go->active = false;
	}
}

void SkeletonArcher::dead()
{
	this->active = false;
}

