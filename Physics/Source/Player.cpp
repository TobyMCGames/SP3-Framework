#include "Player.h"
#include "Application.h"
#include "KeyboardController.h"
#include "GLFW/glfw3.h"
#include "GameLevelManager.h"
#include "ProjectileFactory.h"
#include "CentralMesh.h"
#include "MeshRender.h"

Player::Player()
	: curWeapon(Player::BARE_HANDS)
	, curItem(2)
	, scrollsnap(0)
	, PlayerAnimation(NULL)
	, playerclone(nullptr)
	, cloneinited(false)
	, controlled(true)
	, swap(false)
	, Pexitspeed(0, 0, 0)
	, isCompleted(false)
	,isdead(false)
{
	portalCounter = 0;
	for (int i = 0; i < NUM_ITEMS; i++)
	{
		Inventory[i] = 0;
	}
	health = 100;
	current_scene_worldheight = 90.f;
	current_scene_worldwidth = current_scene_worldheight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	Default_Speed = 15;
	cKeyboardController = CKeyboardController::GetInstance();

	// Slow down time mechanic
	TimeSpeed = 1.f; // is this variable even used?
	SlowTimeStart = false;
	SlowTimeEnd = false;
	isWebbedBySpider = false;
	teleport = false;
	//friction = 0;

	// Init sprite
	PlayerAnimation = new SpriteAnimation(CentralMesh::GetInstance()->GetMeshID(CentralMesh::GEO_PLAYER));
	PlayerAnimation->AddAnimation("Idle", 0, 0);
	PlayerAnimation->AddAnimation("Walking", 0, 5);
	PlayerAnimation->AddAnimation("Jumping", 6, 8);
	PlayerAnimation->AddAnimation("Falling", 9, 11);
	PlayerAnimation->PlayAnimation("Idle", -1, 6.f);
	
}

Player::~Player()
{
	delete PlayerAnimation;
}


void Player::Update(double dt, float m_speed)
{
	if (SlowTime == true)
		mana -= 5 * dt * m_speed;
	if (playerclone != nullptr)
		mana -= 2 * dt * m_speed;
	if (mana <= 0)
	{
		if (SlowTime == true)
		{
			SlowTimeEnd = true;
			SlowTime = false;
			GameLevelManager::GetInstance()->getcurrentLevel()->m_speed = 2.7f;
		}
		if (playerclone != nullptr)
		{
			GameLevelManager::GetInstance()->getcurrentLevel()->setcloneDeleted(true);
			GameLevelManager::GetInstance()->getcurrentLevel()->setcloned(false);
			MeshRender::GetInstance()->GetCamera()->setpanTarget(this);
			controlled = true;
		}
	}
	static bool recharging = false;
	if (SlowTime == false && playerclone == nullptr)
	{
		if (recharging == false)
		{
			RechargeTime = 9.f;
			recharging = true;
		}
		else
		{
			if (mana != 100)
			{
				if (RechargeTime <= 0)
				{
					if (mana > 100)
					{
						mana = 100;
						recharging = false;
					}
					mana += 5 * dt * m_speed;
				}
				else
					RechargeTime -= dt * m_speed;
			}
		}
	}
	double x, y;
	Application::GetCursorPos(&x, &y);
	int w = Application::GetWindowWidth();
	int h = Application::GetWindowHeight();
	mouseWorld = Vector3((x / w) * getsceneWidth(), getsceneHeight() - (y / h) * getsceneHeight());
	mouseWorld += MeshRender::GetInstance()->GetCamera()->getPosition();
	playerToMouseDir = (mouseWorld - pos);
	playerToMouseDir.z = 0;
	if (playerToMouseDir.x != 0 && playerToMouseDir.y != 0)
	{
		playerToMouseDir.Normalize();
		normal = playerToMouseDir.Normalized();
		if (normal.x > 0)
			curDirection = RIGHT;
		else if (normal.x < 0)
			curDirection = LEFT;
	}
	///// Slow time mechanic
	if (cKeyboardController->IsKeyDown(GLFW_KEY_LEFT_SHIFT) && mana - 5 * dt * m_speed > 0)
	{
		if (SlowTime == false)
			SlowTimeStart = true;
		SlowTime = true;
		GameLevelManager::GetInstance()->getcurrentLevel()->m_speed = 1.f;
	}
	if (cKeyboardController->IsKeyReleased(GLFW_KEY_LEFT_SHIFT))
	{
		cKeyboardController->ResetKey(GLFW_KEY_LEFT_SHIFT);
		if (SlowTime == true)
			SlowTimeEnd = true;
		SlowTime = false;
		GameLevelManager::GetInstance()->getcurrentLevel()->m_speed = 2.7f;
	}

	if (SlowTimeStart)
	{
		CSoundController::GetInstance()->PlaySoundByID(19);
		SlowTimeStart = false;
	}
	if (SlowTimeEnd)
	{
		CSoundController::GetInstance()->PlaySoundByID(20);
		SlowTimeEnd = false;
	}

	//////Create Clone Mechanic
	if (cKeyboardController->IsKeyReleased(GLFW_KEY_R))
	{
		if (GameLevelManager::GetInstance()->getcurrentLevel()->getcloned() == false && mana - 2 * dt * m_speed > 0) // summon the clone
		{
			if (curLocation != Entity::IN_AIR)
			{
				InitClone();
				GameLevelManager::GetInstance()->getcurrentLevel()->setcloned(true);
			}
		}
		else if (GameLevelManager::GetInstance()->getcurrentLevel()->getcloned() == true) // despawn the clone
		{
			if ((curLocation != Entity::IN_AIR) && (getClone()->getCurLocation() != Entity::IN_AIR))
			{
				GameLevelManager::GetInstance()->getcurrentLevel()->setcloneDeleted(true);
				GameLevelManager::GetInstance()->getcurrentLevel()->setcloned(false);
				controlled = true;
			}
		}
		cKeyboardController->ResetKey(GLFW_KEY_R);
	}
	////// Switch to clone Mechanic
	if (cKeyboardController->IsKeyReleased(GLFW_KEY_TAB))
	{
		if ((playerclone != nullptr) && (curLocation != Entity::IN_AIR) && (getClone()->getCurLocation() != Entity::IN_AIR))
		{
			swap = true;
			vel.SetZero();
		}
		cKeyboardController->ResetKey(GLFW_KEY_TAB);
	}

	/////// Switching Timeline Mechanic
	if (cKeyboardController->IsKeyPressed(GLFW_KEY_LEFT_ALT))
	{
		ChangeTimeline();
		cKeyboardController->ResetKey(GLFW_KEY_LEFT_ALT);
	}

	/// Shooting Mechanic
	static bool bLButtonState = false;
	if (!bLButtonState && Application::IsMousePressed(0))
	{
		bLButtonState = true;
	}
	else if (bLButtonState && !Application::IsMousePressed(0))
	{
		
		bLButtonState = false;

		//FireWeapon = true;
		switch (curWeapon)
		{
			case BOW:
			{
				CSoundController::GetInstance()->PlaySoundByID(1);
				Projectile* arrow =
					ProjectileFactory::GetInstance()->produceProjectile(ProjectileFactory::PTYPE_ARROW,
						pos + (normal * scale.x), normal, Vector3(3.42f, 1.26f, 1.f) , normal);
				GameLevelManager::GetInstance()->getcurrentLevel()->getProjectileList()->push_back(arrow);
				cout << "arrow created" << endl;
				break;
			}
			case STAFF:
			{
				CSoundController::GetInstance()->PlaySoundByID(2);
				Projectile* magicBall =
					ProjectileFactory::GetInstance()->produceProjectile(ProjectileFactory::PTYPE_MAGICBALL,
						pos + (normal * scale.x), normal, Vector3(3.6f, 2.34f, 1.f) , normal);

					GameLevelManager::GetInstance()->getcurrentLevel()->getProjectileList()->push_back(magicBall);
					cout << "Magic ball created" << endl;
					break;
			}
			case PORTALGUN:
			{
				CSoundController::GetInstance()->PlaySoundByID(3);
				Projectile* portal =
					ProjectileFactory::GetInstance()->produceProjectile(ProjectileFactory::PTYPE_PORTAL,
						pos + (normal * scale.x), normal, Vector3(4.5f, 1.89f, 1.f) , normal);
				GameLevelManager::GetInstance()->getcurrentLevel()->getProjectileList()->push_back(portal);
				cout << "portal created" << endl;
				break;
			}
		}
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
	
	if (controlled)
	{
		if (cKeyboardController->IsKeyPressed(GLFW_KEY_SPACE) && curLocation == Entity::ON_GROUND)
		{
			CSoundController::GetInstance()->PlaySoundByID(4);
			vel.y += getJumpForce();
			curLocation = IN_AIR;
			PlayerAnimation->Reset();
			PlayerAnimation->PlayAnimation("Jumping", 1, getJumpForce() / -GamePhysics::GetInstance()->gravity.y);
		}

			/*float friction = 0.5;*/

			if(!teleport)
				vel.x = 0;

		if (curLocation == ON_GROUND)
		{
			if (teleport)
				vel.x = 0;
			teleport = false;
			PlayerAnimation->PlayAnimation("Idle", -1, 1);
			if (cKeyboardController->IsKeyPressed(GLFW_KEY_A) || cKeyboardController->IsKeyPressed(GLFW_KEY_D))
			{
				PlayerAnimation->Reset();
				PlayerAnimation->PlayAnimation("Walking", -1, 1.5);
			}
		}
		else if (curLocation == IN_AIR)
		{
			float friction = 4;
			if (vel.y < 0)
			{
				PlayerAnimation->Reset();
				PlayerAnimation->PlayAnimation("Falling", 1, 2);
			}
			if (vel.x > 0.1)
			{
				vel.x -= friction * dt * m_speed;
			}
			else if (vel.x < -0.1 )
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
			PlayerAnimation->PlayAnimation("Idle", -1, 1);
		}

		if (cKeyboardController->IsKeyPressed(GLFW_KEY_SPACE) && curLocation == Entity::ON_GROUND)
		{
			//cSoundController->PlaySoundByID(2);
			CSoundController::GetInstance()->PlaySoundByID(4);
			this->vel.y += getJumpForce();
			this->curLocation = IN_AIR;
			PlayerAnimation->Reset();
			PlayerAnimation->PlayAnimation("Jumping", 1, getJumpForce() / -GamePhysics::GetInstance()->gravity.y);
		}
		else if (cKeyboardController->IsKeyReleased(GLFW_KEY_SPACE) && curLocation == Entity::IN_AIR)
		{
			if (this->vel.y > 0)
				vel.y *= 0.7;
		}
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
		switch (curItem)
		{
		case TREE_SEED:
			//std::cout << "Current item is TREE_SEED and there are " << Inventory[curItem] << " in inventory" << std::endl;
			curWeapon = PORTALGUN;
			break;
		case VINE_SEED:
			//std::cout << "Current item is VINE_SEED and there are " << Inventory[curItem] << " in inventory" << std::endl;
			curWeapon = BOW;
			break;
		case BOMBS:
			//std::cout << "Current item is BOMB and there are " << Inventory[curItem] << " in inventory" << std::endl;
			//std::cout << "Bombs:" << Inventory[BOMBS] << endl;
			curWeapon = STAFF;
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

	if (PlayerAnimation != NULL)
	{
		PlayerAnimation->Update(dt* m_speed);
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
		isdead = true;
	}
}

bool Player::getSwap()
{
	return swap;
}

void Player::setSwap(bool swap)
{
	this->swap = swap;
}

void Player::setcurWeapon(Weapons curWeapon)
{
	this->curWeapon = curWeapon;
}

PlayerBase::Weapons Player::getcurWeapon()
{
	return curWeapon;
}

PlayerClone* Player::getClone()
{
	return playerclone;
}

void Player::InitClone()
{
	if (playerclone == nullptr)
	{
		playerclone = new PlayerClone();
		playerclone->Init(pos,Vector3(0,0,0), scale, normal);
		playerclone->setcurWeapon(this->curWeapon);
		playerclone->type = GameObject::GO_PLAYERCLONE;
		playerclone->active = true;
		playerclone->Default_Speed = this->Default_Speed;
		playerclone->setsceneWidth(current_scene_worldwidth);
		playerclone->setsceneHeight(current_scene_worldheight);
		playerclone->setcurLocation(Entity::ON_GROUND);
		GameLevelManager::GetInstance()->getcurrentLevel()->entityPush(playerclone);
	}
}

void Player::resetClone()
{
	playerclone = nullptr;
}

bool Player::isControl()
{
	return controlled;
}

void Player::setControl(bool controlled)
{
	this->controlled = controlled;
}

void Player::Reset()
{
	portalCounter = 0;
	if (playerclone != nullptr)
		playerclone = nullptr;
	curWeapon = BARE_HANDS;
	curItem = 0;
	scrollsnap = 0;
	cloneinited = false;
	controlled = true;
	swap = false;
	Pexitspeed.Set(0, 0, 0);
	isCompleted = false;
	isdead = false;
}

void Player::ResetVariables()
{
	coins = 0;
	health = 100;
	mana = 100;
}

void Player::Response(GameObject* go)
{
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
			}
			break;
		}
	}


	if (go->type == GameObject::OUTOFBOUNDS_TILE)
	{
		isdead = true;
	}

	if ((go->type == GameObject::GO_SKELEARROW) || (go->type == GameObject::GO_SKELEARCHER) ||
		(go->type == GameObject::GO_ZOMBIE) || (go->type == GameObject::GO_TURRETBULLET) || 
		(go->type == GameObject::GO_SPIDER) || (go->type == GameObject::GO_SPIDERWEB))
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
			int randHurtSound = rand() % 3;

			if (randHurtSound == 0)
				CSoundController::GetInstance()->PlaySoundByID(5);
			else if (randHurtSound == 1)
				CSoundController::GetInstance()->PlaySoundByID(6);
			else if (randHurtSound == 2)
				CSoundController::GetInstance()->PlaySoundByID(7);
		}
	}

	if (cKeyboardController->IsKeyPressed(GLFW_KEY_E) && (controlled == true))
	{
		switch (go->type)
		{
		case WEAPON_STATION_BOW:
			this->curWeapon = BOW;
			cKeyboardController->ResetKey(GLFW_KEY_E);
			break;
		case WEAPON_STATION_STAFF:
			this->curWeapon = STAFF;
			cKeyboardController->ResetKey(GLFW_KEY_E);
			break;
		case WEAPON_STATION_PORTAL:
			this->curWeapon = PORTALGUN;
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
			isCompleted = true;
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
						pos.Set(portalPos.x - (go->scale.x+0.1), portalPos.y);
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

void Player::Render()
{
	if (PlayerAnimation != NULL) {
		MeshRender::GetInstance()->RenderAnimation(
			PlayerAnimation->GetSprite(),
			PlayerAnimation->GetCurFrame(),
			6,
			2,
			6,
			false
		);
	}
}

SpriteAnimation* Player::getAnimation()
{
	return PlayerAnimation;
}

int Player::GetCurItem()
{
	return curItem;
}

int Player::GetCurItemAmt()
{
	return Inventory[curItem];
}

void Player::ChangeTimeline()
{
	GameLevelBase* level = GameLevelManager::GetInstance()->getcurrentLevel();
	level->ChangeTimelineBlocks();
}



