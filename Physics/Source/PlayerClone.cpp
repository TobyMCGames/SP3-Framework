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
	,isWebbedBySpider(false)
	, webbedTimeLeft(0)
	,teleport(false)
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

	cKeyboardController = CKeyboardController::GetInstance();
	static bool bLButtonState = false;
	if (!bLButtonState && Application::IsMousePressed(0))
	{
		bLButtonState = true;
	}
	else if (bLButtonState && !Application::IsMousePressed(0))
	{

		bLButtonState = false;

		//FireWeapon = true;
		if (curItem == WEAPON)
		{
			switch (curWeapon)
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
		else
		{
			switch (curItem)
			{
			case BOMBS:
				if (Inventory[BOMBS] > 0)
				{
					Projectile* bomb = ProjectileFactory::GetInstance()->produceProjectile(ProjectileFactory::PTYPE_BOMB,
						(pos + normal * scale.x), normal, Vector3(3, 3, 1), normal);
					GameLevelManager::GetInstance()->getcurrentLevel()->getProjectileList()->push_back(bomb);
					Inventory[BOMBS]--;
					cout << "bomb created" << endl;
				}
				break;
			}
		}
	}

	if (controlled)
	{
		if (cKeyboardController->IsKeyPressed(GLFW_KEY_SPACE) && curLocation == Entity::ON_GROUND)
		{
			CSoundController::GetInstance()->PlaySoundByID(4);
			vel.y += getJumpForce();
			curLocation = IN_AIR;
			CloneAnimation->Reset();
			CloneAnimation->PlayAnimation("Jumping", 1, getJumpForce() / -GamePhysics::GetInstance()->gravity.y);
		}

		/*float friction = 0.5;*/

		if (!teleport)
			vel.x = 0;

		if (curLocation == ON_GROUND)
		{
			if (teleport)
				vel.x = 0;
			teleport = false;
			CloneAnimation->PlayAnimation("Idle", -1, 1);
			if (cKeyboardController->IsKeyPressed(GLFW_KEY_A) || cKeyboardController->IsKeyPressed(GLFW_KEY_D))
			{
				CloneAnimation->Reset();
				CloneAnimation->PlayAnimation("Walking", -1, 1.5);
			}
		}
		else if (curLocation == IN_AIR)
		{
			float friction = 4;
			if (vel.y < 0)
			{
				CloneAnimation->Reset();
				CloneAnimation->PlayAnimation("Falling", 1, 2);
			}
			if (vel.x > 0.1)
			{
				vel.x -= friction * dt * m_speed;
			}
			else if (vel.x < -0.1)
			{
				vel.x += friction * dt * m_speed;
			}
			else
				vel.x = 0;
		}
		if (cKeyboardController->IsKeyDown(GLFW_KEY_D))
		{
			vel.x = Default_Speed;
			curDirection = RIGHT;
		}

		else if (cKeyboardController->IsKeyDown(GLFW_KEY_A))
		{
			vel.x = -Default_Speed;
			curDirection = LEFT;
		}

		if (cKeyboardController->IsKeyDown(GLFW_KEY_A) && cKeyboardController->IsKeyDown(GLFW_KEY_D))
		{
			vel.x = 0;
			CloneAnimation->PlayAnimation("Idle", -1, 1);
		}

		if (cKeyboardController->IsKeyPressed(GLFW_KEY_SPACE) && curLocation == Entity::ON_GROUND)
		{
			//cSoundController->PlaySoundByID(2);
			CSoundController::GetInstance()->PlaySoundByID(4);
			this->vel.y += getJumpForce();
			this->curLocation = IN_AIR;
			CloneAnimation->Reset();
			CloneAnimation->PlayAnimation("Jumping", 1, getJumpForce() / -GamePhysics::GetInstance()->gravity.y);
		}
		else if (cKeyboardController->IsKeyReleased(GLFW_KEY_SPACE) && curLocation == Entity::IN_AIR)
		{
			if (this->vel.y > 0)
				vel.y *= 0.7;
		}
	}
	if (cKeyboardController->IsKeyPressed(GLFW_KEY_1))
	{
		curItem = TREE_SEED;
		cKeyboardController->ResetKey(GLFW_KEY_1);
	}
	if (cKeyboardController->IsKeyPressed(GLFW_KEY_2))
	{
		curItem = VINE_SEED;
		cKeyboardController->ResetKey(GLFW_KEY_2);
	}
	if (cKeyboardController->IsKeyPressed(GLFW_KEY_3))
	{
		curItem = BOMBS;
		cKeyboardController->ResetKey(GLFW_KEY_3);
	}
	if (cKeyboardController->IsKeyPressed(GLFW_KEY_4))
	{
		curItem = WEAPON;
		cKeyboardController->ResetKey(GLFW_KEY_4);
	}

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

	if (curLocation == IN_AIR)
	{
		//cout << "In air" << endl;
	}
	curLocation = IN_AIR;

	if (CloneAnimation != NULL)
	{
		CloneAnimation->Update(dt * m_speed);
	}

	// player get webbed by spider mechanics
	if (isWebbedBySpider == true)
	{
		Default_Speed = 4;
		webbedTimeLeft -= dt * m_speed;
		if (webbedTimeLeft < 0.f)
		{
			isWebbedBySpider = false;
		}
	}
	else
	{
		Default_Speed = 15;
	}

	if (InvincibilityTimer > 0)
	{
		InvincibilityTimer -= dt * m_speed;
	}
	else
	{
		curState = STATE_NORMAL;
	}
	if (health <= 0)
	{
		dead();
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
		switch (go->type)
		{
		case SPIKE_TILE:
			if (curState == STATE_NORMAL)
			{
				takeDamage(5);
				curState = STATE_INVINCIBLE;
				InvincibilityTimer = 1.5;
				//Player::playRandHurtSound();
			}
			break;
		}
	}


	if (go->type == GameObject::OUTOFBOUNDS_TILE)
	{
		this->active = false;
		GameLevelManager::GetInstance()->getcurrentLevel()->setcloneDeleted(true);
		GameLevelManager::GetInstance()->getcurrentLevel()->setcloned(false);
		GameLevelManager::GetInstance()->getcurrentLevel()->swapcontrols();
		Player::GetInstance()->setControl(true);
	}

	if ((go->type == GameObject::GO_SKELEARROW) || (go->type == GameObject::GO_SKELEARCHER) ||
		(go->type == GameObject::GO_ZOMBIE) || (go->type == GameObject::GO_TURRETBULLET) || (go->type == GameObject::GO_HEAVYSKELEARCHER) ||
		(go->type == GameObject::GO_SPIDER) || (go->type == GameObject::GO_SPIDERWEB) || (go->type == GameObject::GO_NYMPH))
	{
		if (curState == STATE_NORMAL)
		{
			if (go->type == GameObject::GO_SPIDERWEB)
			{
				isWebbedBySpider = true;
				webbedTimeLeft = 3.f;
			}
			takeDamage(go->damage);
			curState = STATE_INVINCIBLE;
			InvincibilityTimer = 1.5;
			playRandHurtSound();
		}
	}

	if (cKeyboardController->IsKeyPressed(GLFW_KEY_E) && (controlled == true))
	{
		switch (go->type)
		{
		case WEAPON_STATION_BOW:
			this->curWeapon = BOW;
			this->curItem = Player::WEAPON;
			cKeyboardController->ResetKey(GLFW_KEY_E);
			break;
		case WEAPON_STATION_STAFF:
			this->curWeapon = STAFF;
			this->curItem = Player::WEAPON;
			cKeyboardController->ResetKey(GLFW_KEY_E);
			break;
		case WEAPON_STATION_PORTAL:
			this->curWeapon = PORTALGUN;
			this->curItem = Player::WEAPON;
			cKeyboardController->ResetKey(GLFW_KEY_E);
			break;
		case BOMB_CRATE:
			Inventory[BOMBS]++;
			cKeyboardController->ResetKey(GLFW_KEY_E);
			go->active = false;
			break;
		case VINE_SEEDS:
			Inventory[VINE_SEED]++;
			cKeyboardController->ResetKey(GLFW_KEY_E);
			break;
		case TREE_SEEDS:
			Inventory[TREE_SEED]++;
			cKeyboardController->ResetKey(GLFW_KEY_E);
			go->active = false;
			break;
		case TREE_SAPLING_TILE:
			if (go->pos == go->OGpos)
			{
				Inventory[TREE_SEED]++;
				cKeyboardController->ResetKey(GLFW_KEY_E);
				go->active = false;
			}
			break;
		case WARP_GATE:
			cKeyboardController->ResetKey(GLFW_KEY_E);
			break;
		case SOIL_TILE:
			if (curItem == TREE_SEED)
			{
				bool HasTree = false;
				for (int i = 0; i < GameLevelManager::GetInstance()->getcurrentLevel()->getInteractableList()->size(); i++)
				{
					if (GameLevelManager::GetInstance()->getcurrentLevel()->getInteractableList()->at(i)->type == TREE_SAPLING_TILE)
					{
						if (GameLevelManager::GetInstance()->getcurrentLevel()->getInteractableList()->at(i)->OGpos == go->pos)
						{
							HasTree = true;
							break;
						}
					}
				}
				if (HasTree == false)
				{
					Inventory[curItem]--;
					AdvanceGO* temp = InteractableFactory::GetInstance()->produceInteractable(
						InteractableFactory::PTYPE_TREE,
						Vector3(go->pos.x, go->pos.y + 5, go->pos.z),
						Vector3(5, 5, 1)
					);
					temp->OGpos = temp->pos;
					GameLevelManager::GetInstance()->getcurrentLevel()->getInteractableList()->push_back(temp);
				}
			}
			cKeyboardController->ResetKey(GLFW_KEY_E);
			break;
		}
	}

	if (go->type == GameObject::COIN)
	{
		coins++;
		go->active = false;
	}

	if (go->type == GameObject::HEALTHPOTION)
	{
		if (health < 100)
		{
			health += 20;
			go->active = false;
		}

	}

	if (go->type == GameObject::PORTAL_GATE_ENTRANCE)
	{

		for (int i = 0; i < GameLevelManager::GetInstance()->getcurrentLevel()->getInteractableList()->size(); i++)
		{
			if (GameLevelManager::GetInstance()->getcurrentLevel()->getInteractableList()->at(i)->type == PORTAL_GATE_ENTRANCE)
			{
				if (GameLevelManager::GetInstance()->getcurrentLevel()->getInteractableList()->at(i) != go)
				{
					teleport = true;
					Vector3 portalN = GameLevelManager::GetInstance()->getcurrentLevel()->getInteractableList()->at(i)->normal;
					Vector3 portalPos = GameLevelManager::GetInstance()->getcurrentLevel()->getInteractableList()->at(i)->pos;
					float angle;
					angle = atan2f(go->normal.y, go->normal.x);
					Vector3 ExitN = portalN.Rotated(Math::RadianToDegree(-angle));
					angle = atan2f(-ExitN.y, -ExitN.x);
					vel.Rotate(Math::RadianToDegree(angle));
					//if portal facing right
					if (portalN.x == 1)
					{
						pos.Set(portalPos.x - (go->scale.x + 0.1), portalPos.y);
					}
					//if portal facing left
					else if (portalN.x == -1)
					{
						pos.Set(portalPos.x + (go->scale.x + 0.1), portalPos.y);
					}
					//if facing up
					else if (portalN.y == 1)
					{
						pos.Set(portalPos.x, portalPos.y - (go->scale.y + 0.1));
					}
					//if facing down
					else if (portalN.y == -1)
					{
						pos.Set(portalPos.x, portalPos.y + (go->scale.y + 0.1));
					}
					break;
				}
				else
				{
					continue;
				}
			}
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


