#include "SkeletonArcher.h"
#include "GameLevelManager.h"

SkeletonArcher::SkeletonArcher()
	:currState(BEHAVIOUR::IDLE)
{
	Default_Speed = 5;
	StateCounter = 0;
	attackTimer = 0;
	speedBoostTimer = 0;
	speedBoost = 5;
	return;
}

SkeletonArcher::~SkeletonArcher()
{
	return;
}

void SkeletonArcher::Update(double dt, float m_speed)
{
	switch (currState)
	{
	case IDLE:
		if (StateCounter > MaxStateCounter)
		{
			currState = PATROL;
			StateCounter = 0;
			cout << "SkeletonArcher: switching to Patrol state" << endl;
		}
		else
		{
			pos.y += vel.y * dt * m_speed;
		}
		StateCounter++;
		break;
	case PATROL:
		if (StateCounter > MaxStateCounter)
		{
			/*if (CheckDirection(LEFT))
			{
				curDirection = RIGHT;
			}
			else
				curDirection = LEFT;*/
			currState = IDLE;
			StateCounter = 0;
			cout << "switching to Idle state" << endl;
		}
		else if ((pos - Player::GetInstance()->pos).Length() <= 30)
		{
			currState = ATTACK;
			StateCounter = 0;
			cout << "switching to Attack state" << endl;
		}
		else
		{
			if (curDirection == RIGHT)
				vel.x = Default_Speed;
			else
				vel.x = -Default_Speed;

			pos += vel * dt * m_speed;
		}
		StateCounter++;
		break;
	case ATTACK:
		if ((pos - Player::GetInstance()->pos).Length() <= 30)
		{
			if ((Player::GetInstance()->pos.x - pos.x) > 0)
			{
				vel.x = Default_Speed;
			}
			else if ((Player::GetInstance()->pos.x - pos.x) < 0)
			{
				vel.x = -Default_Speed;
			}
			if (((Player::GetInstance()->pos.y - pos.y) > 0) && curLocation == Entity::ON_GROUND)
			{
				vel.y += JumpForce;
				curLocation = IN_AIR;
			}
			pos += vel * dt * m_speed;
		}
		else
		{
			if (StateCounter > MaxStateCounter)
			{
				currState = PATROL;
				StateCounter = 0;
				cout << "ATTACK: Reset Counter " << StateCounter << endl;
			}
		}
		StateCounter++;
	default:
		break;
	}
	vel += GamePhysics::GetInstance()->gravity * dt * m_speed;
	return;
}

void SkeletonArcher::Response(GameObject* go)
{
	if (go->type > GameObject::PASSIVE_TILE_START && go->type < GameObject::PASSIVE_TILE_END)
	{
		if (vel.y == 0)
		{
			curLocation = ON_GROUND;
		}
	}
	std::cout << "Skarcher response" << std::endl;
	return;
}

