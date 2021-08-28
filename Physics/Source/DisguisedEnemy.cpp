#include "DisguisedEnemy.h"
#include "GameLevelManager.h"

DisguisedEnemy::DisguisedEnemy()
	:currState(BEHAVIOUR::IDLE),
	NymphAnimation(NULL)
{
	Default_Speed = 10;
	StateCounter = 0;
	attackTimer = 0;
	health = 40;
	damage = 6;
	disguiseAnimTimer = 0;
	hasdisguised = false;

	NymphAnimation = new SpriteAnimation(CentralMesh::GetInstance()->GetMeshID(CentralMesh::GEO_NYMPH));
	NymphAnimation->AddAnimation("Walking", 16, 18);
	NymphAnimation->AddAnimation("Disguise", 0, 7);
	NymphAnimation->AddAnimation("CaveTile", 8, 8);
	NymphAnimation->AddAnimation("StoneBrickTile", 9, 9);
	NymphAnimation->AddAnimation("SoilGrassTile", 10, 10);
	NymphAnimation->AddAnimation("ForestGrass", 11, 11);
	NymphAnimation->AddAnimation("BrickTile", 12, 12);
}

DisguisedEnemy::~DisguisedEnemy()
{
	delete NymphAnimation;
}

void DisguisedEnemy::Update(double dt, float m_speed)
{
	if (currState != IDLE)
	{
		pos.x += vel.x * dt * m_speed;
		NymphAnimation->Reset();
		NymphAnimation->PlayAnimation("Walking", -1, 1.8);
	}
	pos.y += vel.y * dt * m_speed;
	vel += GamePhysics::GetInstance()->gravity * dt * m_speed;
	switch (currState)
	{
	case IDLE:
		vel.x = 0;
		if ((pos - Player::GetInstance()->pos).Length() <= 20)
		{
			currState = ATTACK;
		}
		break;
	case ATTACK:
		hasdisguised = true;
		if (disguiseAnimTimer >= maxanimtime)
		{
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
			}
			else
			{
				if (StateCounter > MaxStateCounter)
				{
					currState = IDLE;
					StateCounter = 0;
				}
				disguiseAnimTimer = 0;
			}
			StateCounter += dt * m_speed;
		}
		else
		{
			NymphAnimation->Reset();
			NymphAnimation->PlayAnimation("Disguise", -1, maxanimtime);
			disguiseAnimTimer += dt * m_speed;
		}
		break;
	default:
		break;
	}

	if (NymphAnimation != NULL)
	{
		NymphAnimation->Update(dt * m_speed);
	}
}

void DisguisedEnemy::Response(GameObject* go)
{
	if (go->type > GameObject::PASSIVE_TILE_START && go->type < GameObject::PASSIVE_TILE_END)
	{
		if (vel.y == 0)
		{
			curLocation == ON_GROUND;
		}
		if (currState == IDLE)
		{
			if (go->type == GameObject::STONE_BRICK_TILE)
			{
				NymphAnimation->Reset();
				NymphAnimation->PlayAnimation("StoneBrickTile", -1, 1.8);
			}
			else if (go->type == GameObject::BRICK_TILE)
			{
				NymphAnimation->Reset();
				NymphAnimation->PlayAnimation("BrickTile", -1, 1.8);
			}
			else if (go->type == GameObject::CAVE_TILE)
			{
				NymphAnimation->Reset();
				NymphAnimation->PlayAnimation("CaveTile", -1, 1.8);
			}
			else if (go->type == GameObject::DARK_FOREST_GRASS)
			{
				NymphAnimation->Reset();
				NymphAnimation->PlayAnimation("ForestGrass", -1, 1.8);
			}
			else if (go->type == GameObject::GRASS_SOIL_TILE)
			{
				NymphAnimation->Reset();
				NymphAnimation->PlayAnimation("SoilGrassTile", -1, 1.8);
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
			//play hurt sounds
		}
	}
	//attack player
	if (go->type == GameObject::GO_PLAYER)
	{
		currState = ATTACK;
	}
}

void DisguisedEnemy::Render()
{
	if (NymphAnimation != NULL) {
		MeshRender::GetInstance()->RenderAnimation(
			NymphAnimation->GetSprite(),
			NymphAnimation->GetCurFrame(),
			6,
			false
		);
	}
}

void DisguisedEnemy::dead()
{
	this->active = false;
}

