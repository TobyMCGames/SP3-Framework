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
			else
				vel.x = -Default_Speed;
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
			// jump if player is higher than spider
			/*if (((Player::GetInstance()->pos.y - pos.y) > 0) && curLocation == Entity::ON_GROUND)
			{
				vel.y += JumpForce;
				curLocation = IN_AIR;
			}*/
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

void Spider::Response(GameObject* go)
{
	if (go->type > GameObject::PASSIVE_TILE_START && go->type < GameObject::PASSIVE_TILE_END)
	{
		// uncomment this to make spides jump (also need to uncomment a section above)
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
	if (go->type == GameObject::GO_ARROW ||
		go->type == GameObject::GO_PORTAL ||
		go->type == GameObject::GO_MAGICBALL)// player damage zombie
	{
		takeDamage(go->damage);

		if (health <= 0)
		{
			dead();
		}
	}
	return;
}

void Spider::dead()
{

}

