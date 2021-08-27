#include "Zombie.h"
#include "GameLevelManager.h"

Zombie::Zombie()
	:currState(BEHAVIOUR::IDLE),
	ZombieAnimation(NULL)
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
	jump = false;

	ZombieAnimation = new SpriteAnimation(CentralMesh::GetInstance()->GetMeshID(CentralMesh::GEO_ZOMBIE));
	ZombieAnimation->AddAnimation("Idle", 4, 4);
	ZombieAnimation->AddAnimation("Walking", 0, 3);
}

Zombie::~Zombie()
{
	//return;
	delete ZombieAnimation;
}

void Zombie::Update(double dt, float m_speed)
{
	if (currState != IDLE)
	{
		pos.x += vel.x * dt * m_speed;
		ZombieAnimation->Reset();
		ZombieAnimation->PlayAnimation("Walking", -1, 3);
	}
	pos.y += vel.y * dt * m_speed;
	vel += GamePhysics::GetInstance()->gravity * dt * m_speed;
	switch (currState)
	{
	case IDLE:
		if (StateCounter > MaxStateCounter)
		{
			currState = PATROL;
			ZombieAnimation->Reset();
			ZombieAnimation->PlayAnimation("Idle", 1, 1.5);
			StateCounter = 0;
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
		}
		else if ((pos - Player::GetInstance()->pos).Length() <= 30)
		{
			currState = ATTACK;
			StateCounter = 0;
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
			}
		}
		StateCounter += dt * m_speed;
	default:
		break;
	}

	if (ZombieAnimation != NULL)
	{
		ZombieAnimation->Update(dt * m_speed);
	}

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
	//cout << "Collide Pos: "<< GamePhysics::GetInstance()->GetCollidePos() << endl;

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
		if (currState == ATTACK)
		{
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
	//attack player
	if (go->type == GameObject::GO_PLAYER)
	{
		//if (pos.x <= (go->pos.x + go->scale.x / 2))
		//{
			cout << "touched player" << endl;
		//}
	}
}

void Zombie::Render()
{
	if (ZombieAnimation != NULL) {
		MeshRender::GetInstance()->RenderAnimation(
			ZombieAnimation->GetSprite(),
			ZombieAnimation->GetCurFrame(),
			6,
			2,
			4,
			false
		);
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
