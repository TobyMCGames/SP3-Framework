#include "Application.h"
#include "GLFW/glfw3.h"
#include "PlayerClone.h"
#include "GameLevelManager.h"
#include "ProjectileFactory.h"
#include "CentralMesh.h"
#include "MeshRender.h"

PlayerClone::PlayerClone()
	:controlled(false)
	,CloneAnimation(NULL)
{
	CloneAnimation = new SpriteAnimation(CentralMesh::GetInstance()->GetMeshID(CentralMesh::GEO_PLAYER));
	CloneAnimation->AddAnimation("CloneIdle", 0, 0);
	CloneAnimation->AddAnimation("CloneWalking", 0, 5);
	CloneAnimation->AddAnimation("CloneJumping", 6, 8);
	CloneAnimation->AddAnimation("CloneFalling", 9, 11);
	CloneAnimation->PlayAnimation("CloneIdle", -1, 6.f);
}

PlayerClone::~PlayerClone()
{
	delete CloneAnimation;
	CloneAnimation = nullptr;
}
void PlayerClone::setcurWeapon(Weapons curWeapon)
{
	this->curWeapon = curWeapon;
}

PlayerBase::Weapons PlayerClone::getcurWeapon()
{
	return curWeapon;
}

void PlayerClone::setInventory(int Inventory[])
{
	
}

void PlayerClone::Init(Vector3 pos, Vector3 vel, Vector3 scale, Vector3 normal)
{
	this->pos = pos;
	this->vel = vel;
	this->scale = scale;
	this->normal = normal;
}

bool PlayerClone::isControl()
{
	return controlled;
}

void PlayerClone::setControl(bool controlled)
{
	this->controlled = controlled;
}

Vector3 PlayerClone::getpos()
{
	return pos;
}

Vector3 PlayerClone::getvel()
{
	return vel;
}

Vector3 PlayerClone::getscale()
{
	return scale;
}

Vector3 PlayerClone::getnormal()
{
	return normal;
}

void PlayerClone::setpos(Vector3 pos)
{
	this->pos = pos;
}

void PlayerClone::setvel(Vector3 vel)
{
	this->vel = vel;
}

void PlayerClone::setsscale(Vector3 scale)
{
	this->scale = scale;
}

void PlayerClone::setnormal(Vector3 normal)
{
	this->normal = normal;
}

void PlayerClone::setcurLocation(Entity::LOCATION curLocation)
{
	this->curLocation = curLocation;
}

SpriteAnimation* PlayerClone::getAnimation()
{
	return CloneAnimation;
}

Entity::LOCATION PlayerClone::getCurLocation()
{
	return this->curLocation;
}



void PlayerClone::Update(double dt, float m_speed)
{
	static Vector3 maxpoint = Vector3(GameLevelManager::GetInstance()->getcurrentLevel()->getworldWidth(),
		GameLevelManager::GetInstance()->getcurrentLevel()->getworldHeight(),
		this->pos.z);
	double x, y;
	Application::GetCursorPos(&x, &y);
	int w = Application::GetWindowWidth();
	int h = Application::GetWindowHeight();
	mouseWorld = Vector3((x / w) * current_scene_worldwidth, current_scene_worldheight - (y / h) * current_scene_worldheight);
	mouseWorld += MeshRender::GetInstance()->GetCamera()->getPosition();
	playerToMouseDir = (mouseWorld - this->pos);
	playerToMouseDir.z = 0;
	if (playerToMouseDir.x != 0 && playerToMouseDir.y != 0)
	{
		playerToMouseDir.Normalize();
		this->normal = playerToMouseDir.Normalized();
		if (normal.x > 0)
			curDirection = RIGHT;
		else if (normal.x < 0)
			curDirection = LEFT;
	}


	static bool bLCButtonState = false;
	if (!bLCButtonState && Application::IsMousePressed(1))
	{
		bLCButtonState = true;
	}
	else if (bLCButtonState && !Application::IsMousePressed(1))
	{

		bLCButtonState = false;

	//	FireWeapon = true;
		switch (this->curWeapon)
		{
		case BOW:
		{
			CSoundController::GetInstance()->PlaySoundByID(1);
			Projectile* arrow =
				ProjectileFactory::GetInstance()->produceProjectile(ProjectileFactory::PTYPE_ARROW,
					pos + (normal * scale.x), normal, Vector3(3.42f, 1.26f, 1.f), normal);
			GameLevelManager::GetInstance()->getcurrentLevel()->getProjectileList()->push_back(arrow);
			cout << "arrow created" << endl;
			break;
		}
		case STAFF:
		{
			CSoundController::GetInstance()->PlaySoundByID(2);
			Projectile* magicBall =
				ProjectileFactory::GetInstance()->produceProjectile(ProjectileFactory::PTYPE_MAGICBALL,
					pos + (normal * scale.x), normal, Vector3(3.6f, 2.34f, 1.f), normal);

			GameLevelManager::GetInstance()->getcurrentLevel()->getProjectileList()->push_back(magicBall);
			cout << "Magic ball created" << endl;
			break;
		}
		case PORTALGUN:
		{
			CSoundController::GetInstance()->PlaySoundByID(3);
			Projectile* portal =
				ProjectileFactory::GetInstance()->produceProjectile(ProjectileFactory::PTYPE_PORTAL,
					pos + (normal * scale.x), normal, Vector3(4.5f, 1.89f, 1.f), normal);
			GameLevelManager::GetInstance()->getcurrentLevel()->getProjectileList()->push_back(portal);
			cout << "portal created" << endl;
			break;
		}
		}
	}
//	FireWeapon = false;
	vel.x = 0;
	if (controlled)
	{
		if (cKeyboardController->IsKeyPressed(GLFW_KEY_SPACE) && this->curLocation == Entity::ON_GROUND)
		{
			//cSoundController->PlaySoundByID(2);
			CSoundController::GetInstance()->PlaySoundByID(4);
			vel.y += getJumpForce();
			this->curLocation = IN_AIR;
			CloneAnimation->Reset();
			CloneAnimation->PlayAnimation("CloneJumping", 1, getJumpForce() / -GamePhysics::GetInstance()->gravity.y);
		}

		if (this->curLocation == ON_GROUND)
		{
			CloneAnimation->PlayAnimation("CloneIdle", -1, 1);
			if (cKeyboardController->IsKeyPressed(GLFW_KEY_A) || cKeyboardController->IsKeyPressed(GLFW_KEY_D))
			{
				CloneAnimation->Reset();
				CloneAnimation->PlayAnimation("CloneWalking", -1, 1.5);
			}
		}
		else if (this->curLocation == IN_AIR)
		{
			if (vel.y < 0)
			{
				CloneAnimation->Reset();
				CloneAnimation->PlayAnimation("CloneFalling", 1, 2);
			}
		}
		if (cKeyboardController->IsKeyDown(GLFW_KEY_D))
		{
			if (pos.x + Default_Speed * dt < maxpoint.x - (scale.x / 2))
			{
				vel.x = Default_Speed;
				this->curDirection = RIGHT;
			}
		}

		else if (cKeyboardController->IsKeyDown(GLFW_KEY_A))
		{
			if (pos.x - Default_Speed * dt > scale.x / 2)
			{
				vel.x = -Default_Speed;
				this->curDirection = LEFT;
			}
		}

		if (cKeyboardController->IsKeyDown(GLFW_KEY_A) && cKeyboardController->IsKeyDown(GLFW_KEY_D))
		{
			vel.x = 0;
			CloneAnimation->PlayAnimation("CloneIdle", -1, 1);
		}
	}

		/*if (cKeyboardController->IsKeyPressed(GLFW_KEY_W))
		{
			if (pos.y + Default_Speed * dt < maxpoint.y - scale.y / 2)
				vel.y = Default_Speed;
		}
		if (cKeyboardController->IsKeyPressed(GLFW_KEY_S))
		{
			if (pos.y - Default_Speed * dt > scale.y / 2)
				vel.y = -Default_Speed;
		}
		if (!cKeyboardController->IsKeyPressed(GLFW_KEY_W) && !cKeyboardController->IsKeyPressed(GLFW_KEY_S))
		{
			vel.y = 0;
		}*/

		scrollsnap += Application::GetYScrollOffset();

		if (scrollsnap > getScrollSensitivity())
		{
			curItem++;
			scrollsnap = 0;
		}
		else if (scrollsnap < 0)
		{
			curItem--;
			scrollsnap = getScrollSensitivity();
		}
		if (curItem < 0)
		{
			curItem = NUM_ITEMS - 1;
		}
		else if (curItem >= NUM_ITEMS)
		{
			curItem = 0;
		}

		switch (curItem)
		{
		case TREE_SEED:
			//std::cout << "Current item is TREE_SEED and there are " << Inventory[curItem] << " in inventory" << std::endl;
			break;
		case VINE_SEED:
			//std::cout << "Current item is VINE_SEED and there are " << Inventory[curItem] << " in inventory" << std::endl;
			break;
		case BOMBS:
			//std::cout << "Current item is BOMB and there are " << Inventory[curItem] << " in inventory" << std::endl;
			break;
		default:
			//std::cout << "Invalid curItem in Player.cpp" << std::endl;
			break;
		}
	if (curLocation == IN_AIR)
	{
		//cout << "In air" << endl;
	}
	curLocation = IN_AIR;
	if (CloneAnimation != NULL)
	{
		CloneAnimation->Update(dt * m_speed);
	}
}

void PlayerClone::Response(GameObject* go)
{
	cKeyboardController = CKeyboardController::GetInstance();
	if (go->type > GameObject::PASSIVE_TILE_START && go->type < GameObject::PASSIVE_TILE_END)
	{
		if (vel.y == 0)
		{
			curLocation = ON_GROUND;
		}
	}
	if ((go->type == GameObject::GO_SKELEARROW) || (go->type == GameObject::GO_SKELEARCHER) ||
		(go->type == GameObject::GO_ZOMBIE) || (go->type == GameObject::GO_TURRETBULLET))
	{
		takeDamage(go->damage);
		int randHurtSound = rand() % 3;

		if (randHurtSound == 0)
			CSoundController::GetInstance()->PlaySoundByID(5);
		else if (randHurtSound == 1)
			CSoundController::GetInstance()->PlaySoundByID(6);
		else if (randHurtSound == 2)
			CSoundController::GetInstance()->PlaySoundByID(7);

		if (health <= 0)
		{
			dead();
		}
	}
	if (cKeyboardController->IsKeyPressed(GLFW_KEY_E) && (controlled == true))
	{
		switch (go->type)
		{
		case WEAPON_STATION_BOW:
			this->curWeapon = BOW;
			break;
		case WEAPON_STATION_STAFF:
			this->curWeapon = STAFF;
			break;
		case WEAPON_STATION_PORTAL:
			this->curWeapon = PORTALGUN;
			break;
		}
	}
}

void PlayerClone::Render()
{
	if (CloneAnimation != NULL) {
		MeshRender::GetInstance()->RenderAnimation(
			CloneAnimation->GetSprite(),
			CloneAnimation->GetCurFrame(),
			6,
			false
		);
	}
}


