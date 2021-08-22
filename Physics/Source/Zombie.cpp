#include "Zombie.h"
#include "GameLevelManager.h"

Zombie::Zombie()
	:currState(BEHAVIOUR::IDLE)
{
	Default_Speed = 2;
	StateCounter = 0;
	attackTimer = 0;
	speedBoostTimer = 0;
	speedBoost = 5;
	health = 70;
	damage = 15;
	attackSoundTimer = 0;
	idleSoundTimer = 0;
}

Zombie::~Zombie()
{
	//return;
}

void Zombie::Update(double dt, float m_speed)
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
		else
		{
			
		}
		StateCounter += dt * m_speed;
		break;
	case PATROL:
		if (StateCounter > MaxStateCounter)
		{
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

			if(curDirection == RIGHT)
				vel.x = Default_Speed;
			else
				vel.x = -Default_Speed;
		}
		StateCounter += dt * m_speed;
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
		StateCounter += dt * m_speed;
	default:
		break;
	}
	vel += GamePhysics::GetInstance()->gravity * dt * m_speed;


	//play sounds
	if (currState == ATTACK)
	{
		if (attackSoundTimer >= 5)
		{
			int randAttackSound = rand() % 2;
			if (randAttackSound == 0)
				CSoundController::GetInstance()->PlaySoundByID(9);
			else if (randAttackSound == 1)
				CSoundController::GetInstance()->PlaySoundByID(10);
			attackSoundTimer = 0;
		}
		attackSoundTimer += dt * m_speed;

		idleSoundTimer = 0;
	}
	else if (currState != ATTACK)
	{
		if (idleSoundTimer >= 8)
		{
			CSoundController::GetInstance()->PlaySoundByID(8);
			idleSoundTimer = 0; 
		}
		idleSoundTimer += dt * m_speed;

		attackSoundTimer = 0;
	}

	//cout <<"Zombie attack sound timere:"<< attackSoundTimer << endl;
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
	if (go->type == GameObject::GO_ARROW ||
		go->type == GameObject::GO_PORTAL ||
		go->type == GameObject::GO_MAGICBALL) // player damage zombie
	{
		takeDamage(go->damage);

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

void Zombie::dead()
{
	this->active = false;
}


void Zombie::FlipHorizontalDirection(void)
{
	vel.x *= -1;
}