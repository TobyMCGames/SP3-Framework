#include "Spider.h"
#include "GameLevelManager.h"

Spider::Spider()
	:currState(BEHAVIOUR::IDLE)
{
	Default_Speed = 5;
	StateCounter = 0;
	attackTimer = 0;
	speedBoostTimer = 0;
	speedBoost = 5;
	health = 100;
	return;
}

Spider::~Spider()
{
	return;
}

void Spider::Update(double dt, float m_speed)
{
	if (currState != IDLE)
		pos.x += vel.x * dt * m_speed;
	pos.y += vel.y * dt * m_speed;
	switch (currState)
	{
	case IDLE:
		if (StateCounter > MaxStateCounter)
		{
			currState = PATROL;
			StateCounter = 0;
			cout << "switching to Patrol state" << endl;
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
			else if (curDirection == LEFT)
				vel.x = -Default_Speed;
			else
				cout << "Could not figure out which patrol direction to move for spider" << endl;
		}
		StateCounter += dt * m_speed;
		break;
	case ATTACK:
		//vel.y += Default_Speed;
		if ((pos - Player::GetInstance()->pos).Length() <= 30)
		{
			// Go right
			if ((Player::GetInstance()->pos.x - pos.x) > 0)
			{
				vel.x = Default_Speed;
				if (((Player::GetInstance()->pos.y - pos.y) < 0) && curLocation == Entity::IN_AIR)
				{
					vel.y -= 0;
				}
			}
			// Go left
			else if ((Player::GetInstance()->pos.x - pos.x) < 0)
			{
  				vel.x = -Default_Speed;
				if (((Player::GetInstance()->pos.y - pos.y) < 0) && curLocation == Entity::IN_AIR)
				{
					vel.y -= 0;
				}
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
		break;
	case CLIMBING:
	{
		vel.y = Default_Speed;
		curLocation = IN_AIR;
		if ((pos - Player::GetInstance()->pos).Length() <= 30)
		{
			// Go right
			if ((Player::GetInstance()->pos.x - pos.x) > 0)
			{
				currState = ATTACK;
			}
			// Go left
			else if ((Player::GetInstance()->pos.x - pos.x) < 0)
			{
				currState = ATTACK;
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
		break;
	}
	default:
		break;
	}
	vel += GamePhysics::GetInstance()->gravity * dt * m_speed;
	return;
}

void Spider::Response(GameObject* go)
{
	if (go->type > GameObject::PASSIVE_TILE_START && go->type < GameObject::PASSIVE_TILE_END)
	{
		if (vel.y == 0)
		{
			curLocation = ON_GROUND;
		}

		if (vel.x == 0 && currState == ATTACK)
		{
			currState = CLIMBING;
		}

		if (vel.x != 0 && currState == CLIMBING)
		{
			currState = ATTACK;
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
	if (go->type == GameObject::GO_ARROW ||
		go->type == GameObject::GO_PORTAL ||
		go->type == GameObject::GO_MAGICBALL)// player damage spider
	{
		takeDamage(go->damage);

		if (health <= 0)
		{
			dead();
		}
	}
	return;
}

void Spider::Render()
{
}

void Spider::dead()
{
	this->active = false;
}


// enable this when flipped horizontally sprite for spider is made
//void Spider::FlipHorizontalDirection(void)
//{
//	vel.x *= -1;
//}