#include "Spider.h"
#include "GameLevelManager.h"
#include "ProjectileFactory.h"

Spider::Spider()
	:currState(BEHAVIOUR::IDLE),
	SpiderAnimation(NULL)
{
	Default_Speed = 5;
	StateCounter = 0;
	attackTimer = 0;
	speedBoostTimer = 0;
	speedBoost = 5;
	health = 100;
	shootCounter = 0;
	damage = 12;

	SpiderAnimation = new SpriteAnimation(CentralMesh::GetInstance()->GetMeshID(CentralMesh::GEO_SPIDER));
	SpiderAnimation->AddAnimation("Idle", 0, 4);
	SpiderAnimation->AddAnimation("Walking", 6, 11);
	SpiderAnimation->AddAnimation("Shooting", 12, 15);
}

Spider::~Spider()
{
	delete SpiderAnimation;
}

void Spider::Update(double dt, float m_speed)
{
	if (currState != IDLE)
	{
		SpiderAnimation->Reset();
		SpiderAnimation->PlayAnimation("Walking", -1, 1.5);
		pos.x += vel.x * dt * m_speed;
	}
	pos.y += vel.y * dt * m_speed;

	if (SpiderAnimation != NULL)
	{
		SpiderAnimation->Update(dt * m_speed);
	}
	switch (currState)
	{
	case IDLE:
		if (StateCounter > MaxStateCounter)
		{
			currState = PATROL;
			StateCounter = 0;
			cout << "switching to Patrol state" << endl;
			SpiderAnimation->Reset();
			SpiderAnimation->PlayAnimation("Idle", 1, 1.5);
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
		else if ((pos - Player::GetInstance()->pos).Length() <= 30) // changing this value affects spider detection radius
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
		if ((pos - Player::GetInstance()->pos).Length() <= 30) // changing this value affects spider detection radius
		{
			if ((pos - Player::GetInstance()->pos).Length() >= 15) // changing this value affects spider shooting poison radius
			{
				normal = ((Player::GetInstance()->pos - pos).Normalize());
				if (shootCounter > MaxFirerate)
				{
					// shooting process
					CSoundController::GetInstance()->PlaySoundByID(1);
					Projectile* spiderpoison =
						ProjectileFactory::GetInstance()->produceProjectile(ProjectileFactory::PTYPE_SPIDERPOISON,
							pos + (normal * scale.x), normal, scale, normal);
					GameLevelManager::GetInstance()->getcurrentLevel()->getProjectileList()->push_back(spiderpoison);
					SpiderAnimation->Reset();
					SpiderAnimation->PlayAnimation("Shooting", -1, 1.5);
					shootCounter = 0;
				}
				shootCounter += dt * m_speed;
			}
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
		if ((pos - Player::GetInstance()->pos).Length() <= 30) // changing this value affects spider detection radius
		{
			currState = ATTACK;
		}
		else
		{
			if (StateCounter > MaxStateCounter)
			{
				currState = IDLE;
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
			curLocation = ON_GROUND;
		if (vel.x == 0 && currState == ATTACK)
			currState = CLIMBING;
		if (vel.x != 0 && currState == CLIMBING)
			currState = ATTACK;
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
	if (go->type == GameObject::GO_BOMB)
	{
		takeDamage(go->damage);
		go->active = false;
		if (health <= 0)
		{
			//CSoundController::GetInstance()->PlaySoundByID(13);
			dead();
		}
	}
		
	if (go->type == GameObject::GO_ARROW ||
		go->type == GameObject::GO_MAGICBALL)// player damage spider
	{
		takeDamage(go->damage);
		go->active = false;

		if (health <= 0)
		{
			CSoundController::GetInstance()->PlaySoundByID(25);
			dead();
		}
		else
		{
			CSoundController::GetInstance()->PlaySoundByID(24);
		}
	}
	return;
}

void Spider::Render()
{
	if (SpiderAnimation != NULL) {
		MeshRender::GetInstance()->RenderAnimation(
			SpiderAnimation->GetSprite(),
			SpiderAnimation->GetCurFrame(),
			6,
			false
		);
	}
}

void Spider::dead()
{
	this->active = false;
}


// enable this when flipped horizontally sprite for spider is made
void Spider::FlipHorizontalDirection(void)
{
	vel.x *= -1;
}