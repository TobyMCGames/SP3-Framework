#include "Zombie.h"
#include "GameLevelManager.h"

Zombie::Zombie()
	:currState(BEHAVIOUR::IDLE)
{
	Default_Speed = 5;
	StateCounter = 0;
}

Zombie::~Zombie()
{
	//return;
}

void Zombie::Update(double dt, float m_speed)
{
	pos += vel * dt * m_speed;
	std::cout << this->normal << std::endl;
	switch (currState)
	{
	case IDLE:
		if (StateCounter > MaxStateCounter)
		{
			currState = PATROL;
			StateCounter = 0;
			cout << "switching to Patrol state" << endl;
		}
		else
		{
			vel = 0;
		}
		StateCounter++;
		break;
	case PATROL:
		if (StateCounter > MaxStateCounter)
		{
			currState = IDLE;
			StateCounter = 0;
			cout << "switching to Idle state" << endl;
		}
		//vel.x = 15;
		else if ((pos - Player::GetInstance()->pos).Length() <= 30)
		{
			currState = ATTACK;
			StateCounter = 0;
			cout << "switching to Attack state" << endl;
		}
		else
		{
			vel.x = Default_Speed;
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
}

void Zombie::Response(GameObject* go)
{
	if (go->type > GameObject::PASSIVE_TILE_START && go->type < GameObject::PASSIVE_TILE_END)
	{
		if (vel.y == 0)
		{
			curLocation = ON_GROUND;
		}

		if (currState == PATROL)
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
}

//void Zombie::FlipHorizontalDirection(void)
//{
//	vel.x *= -1;
//}