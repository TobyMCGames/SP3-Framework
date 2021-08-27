#include "Boomer.h"
#include "GameLevelManager.h"

Boomer::Boomer()
	:currState(BEHAVIOUR::IDLE),
	BoomerAnimation(NULL)
{
	health = 45;
	damage = 0;
	Default_Speed = 10;
	StateCounter = 0;
	explodeTimer = 0;

	BoomerAnimation = new SpriteAnimation(CentralMesh::GetInstance()->GetMeshID(CentralMesh::GEO_BOOMER));
	BoomerAnimation->AddAnimation("Idle", 12, 12);
	BoomerAnimation->AddAnimation("Walking", 0, 5);
	BoomerAnimation->AddAnimation("Chasing", 6, 11);
	BoomerAnimation->AddAnimation("Priming", 18, 19);
	BoomerAnimation->AddAnimation("Explode", 24, 24);
}

Boomer::~Boomer()
{
	delete BoomerAnimation;
}

void Boomer::Update(double dt, float m_speed)
{
	if (currState != IDLE)
	{
		pos.x += vel.x * dt * m_speed;
	}
	if (currState == IDLE)
	{
		BoomerAnimation->Reset();
		BoomerAnimation->PlayAnimation("Idle", 1, 1);
	}
	else if (currState == PATROL)
	{
		BoomerAnimation->Reset();
		BoomerAnimation->PlayAnimation("Walking", -1, 1);
	}
	else if (currState == ATTACK)
	{
		BoomerAnimation->Reset();
		BoomerAnimation->PlayAnimation("Chasing", -1, 1);
	}
	else if (currState == EXPLODE)
	{
		BoomerAnimation->Reset();
		BoomerAnimation->PlayAnimation("Priming", -1, 0.5);
	}

	pos.y += vel.y * dt * m_speed;
	vel += GamePhysics::GetInstance()->gravity * dt * m_speed;
	switch (currState)
	{
	case IDLE:
		if (StateCounter > MaxStateCounter)
		{
			currState = PATROL;
			StateCounter = 0;
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

			if (curDirection == RIGHT)
				vel.x = Default_Speed;
			else
				vel.x = -Default_Speed;
		}
		StateCounter += dt * m_speed;
		break;
	case ATTACK:
		if ((pos - Player::GetInstance()->pos).Length() <= 10)
		{
			currState = EXPLODE;
		}
		if ((pos - Player::GetInstance()->pos).Length() <= 60)
		{
			if ((Player::GetInstance()->pos.x - pos.x) > 0)
			{
				vel.x = Default_Speed;
			}
			else if ((Player::GetInstance()->pos.x - pos.x) < 0)
			{
				vel.x = -Default_Speed;
			}
	/*		if (((Player::GetInstance()->pos.y - pos.y) > 0) && curLocation == Entity::ON_GROUND)
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
			}
		}
		StateCounter += dt * m_speed;
		break;
	case EXPLODE:
		vel.x = 0;
		if (explodeTimer >= maxExplodeTime)
		{
			BoomerAnimation->Reset();
			BoomerAnimation->PlayAnimation("Explode", -1, 1);
			if ((pos - Player::GetInstance()->pos).Length() <= 20)
			{
				Player::GetInstance()->takeDamage(30);
			}
			dead();
		}
		explodeTimer += dt * m_speed;
		break;
	default:
		break;
	}
	if (BoomerAnimation != NULL)
	{
		BoomerAnimation->Update(dt * m_speed);
	}
}

void Boomer::Response(GameObject* go)
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
		go->type == GameObject::GO_MAGICBALL)
	{
		takeDamage(go->damage);
		go->active = false;

		if (health <= 0)
		{
			dead();
		}
		else
		{
			//play hurt sounds
		}
	}
	if (go->type == GO_PLAYER)
	{
		currState = EXPLODE;
	}
}

void Boomer::Render()
{
	if (BoomerAnimation != NULL) {
		MeshRender::GetInstance()->RenderAnimation(
			BoomerAnimation->GetSprite(),
			BoomerAnimation->GetCurFrame(),
			6,
			false
		);
	}
}

void Boomer::dead()
{
	this->active = false;
}
