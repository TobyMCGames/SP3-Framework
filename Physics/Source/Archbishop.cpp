#include "Archbishop.h"
#include "MeshRender.h"
#include "ProjectileFactory.h"
#include "Player.h"
#include "GameLevelManager.h"

Archbishop::Archbishop()
	:firstform(NULL)
	, rotation(0)
	, current_state(IDLE)
	, stateCounter(0)
{
	firstform = new SpriteAnimation(CentralMesh::GetInstance()->GetMeshID(CentralMesh::GEO_ARCHBISHOP_1));
	firstform->AddAnimation("Moving",0,6);
	firstform->PlayAnimation("Moving", -1,6.f);
	health = 1000;
	this->damage = 1;
	Default_Speed = 3.5;
}

Archbishop::~Archbishop()
{
	delete firstform;
}

void Archbishop::Update(double dt, float m_speed)
{
	switch (current_state)
	{
	case IDLE:
		if (stateCounter > 120)
		{
			int rand = Math::RandIntMinMax(1, 4);
			if (rand == 1)
				current_state = SPIN_ATTACK;
			else if (rand == 2)
			{
				current_state = TRACK_PLAYER;
				this->damage = 2;
			}
				
			else if (rand == 3)
			{
				this->damage = 2.5;
				current_state = SPINING_KAMIKAZE;
			}
				
			else if (rand == 4)
				current_state = DISARM_PLAYER;

			stateCounter = 0;
		}
		else
			stateCounter++;
		break;
	case SPIN_ATTACK:
		rotation -= 240.f * dt * m_speed;
		if (rotation <= -3600)
		{
			current_state = IDLE;
			rotation = 0;
			if (Math::RandIntMinMax(0, 1) == 1)
			{
				current_state = DISARM_PLAYER;
				
			}
			else
			{
				current_state = IDLE;
				stateCounter = 0;
			}
		}	
		else
		{
			if (Math::RandIntMinMax(1,50) == 2)
			{
				Projectile* temp;
				Vector3 scale = this->scale;
				scale = scale *0.01 * 20 ;
				Vector3 vel = (Player::GetInstance()->pos - this->pos).Normalized();
				temp =  ProjectileFactory::GetInstance()->produceProjectile(ProjectileFactory::PROJECTILE_TYPES::PTYPE_ARCH_BALL,
					this->pos,vel,scale, Vector3(1, 0, 0));
				GameLevelManager::GetInstance()->getcurrentLevel()->getProjectileList()->push_back(temp);
				CSoundController::GetInstance()->PlaySoundByID(72);
			}
		}
		break;
	case TRACK_PLAYER:
		if (stateCounter < 600)
		{
			vel = (Player::GetInstance()->pos - this->pos).Normalized() * 0.1f;
			pos += vel *Default_Speed*0.5;
			stateCounter++;
			if (stateCounter % 150 == 0)
				CSoundController::GetInstance()->PlaySoundByID(69);
		}
		else 
		{
			current_state = IDLE;
			stateCounter = 0;
			vel = Vector3(0, 0, 0);
		}
		break;

	case DISARM_PLAYER:
		Player::GetInstance()->setcurWeapon(Player::Weapons::BARE_HANDS);
		current_state = IDLE;
		stateCounter = 0;
		break;

	case SPINING_KAMIKAZE:
		rotation -= 360.f * dt * m_speed;
		vel = (Player::GetInstance()->pos - this->pos).Normalized();
		pos += vel * dt * m_speed * Default_Speed;
		stateCounter++; 
		if (stateCounter % 75 == 0)
			CSoundController::GetInstance()->PlaySoundByID(69);
		if (rotation <= -3600)
		{
			if (Math::RandIntMinMax(0,4) == 3)
			{
				current_state = DISARM_PLAYER;
				rotation = 0;
				stateCounter = 0;
			}
			else
			{
				current_state = IDLE;
				stateCounter = 0;
				rotation = 0;
			}
		}
		break;
	case FLEE:
		pos.y += 10;
		if (GameLevelManager::GetInstance()->getcurrentLevel()->CheckWithinScreen(this) == false)
		{
			this->active = false;
			CSoundController::GetInstance()->PlaySoundByID(70);
		}
		break;
	}
	firstform->Update(dt);
}

void Archbishop::Response(GameObject* go)
{
	if (go->type == GameObject::GO_ARROW)
	{
		takeDamage(go->damage);
		go->active = false;
		CSoundController::GetInstance()->PlaySoundByID(71);
	}
	if (health <= 0)
		dead();
}

void Archbishop::Render()
{
	MS* modelStack = MeshRender::GetInstance()->GetModelStack();
	if (firstform != NULL)
	{
		if (current_state == SPIN_ATTACK || current_state == SPINING_KAMIKAZE)
		{
			modelStack->PushMatrix();
			modelStack->Rotate(rotation, 0, 0, 1);
			MeshRender::GetInstance()->RenderAnimation(
				firstform->GetSprite(),
				firstform->GetCurFrame(),
				6,
				false
			);
			modelStack->PopMatrix();
		}
		else if (current_state == IDLE || current_state == TRACK_PLAYER || current_state == FLEE)
		{
			modelStack->PushMatrix();
			MeshRender::GetInstance()->RenderAnimation(
				firstform->GetSprite(),
				firstform->GetCurFrame(),
				6,
				false
			);
			modelStack->PopMatrix();
		}
	}
}

void Archbishop::dead()
{
	current_state = FLEE;
	Interactables* temp = InteractableFactory::GetInstance()->produceInteractable(InteractableFactory::PTYPE_WARP_GATE, OGpos, Vector3(20, 20, 1));
	GameLevelManager::GetInstance()->getcurrentLevel()->getInteractableList()->push_back(temp);
}
