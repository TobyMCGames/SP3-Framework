#include "Player.h"
#include "Application.h"
#include "KeyboardController.h"
#include "GLFW/glfw3.h"
#include "GameLevelManager.h"
#include "ProjectileFactory.h"

Player::Player()
	: curWeapon(Player::PORTALGUN)
	, curItem(0)
	, scrollsnap(0)
	, PlayerAnimation(NULL)
	,playerclone(nullptr)
	,cloneinited(false)
	,controlled(true)
	,swap(false)
{
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

	// Init sprite
	PlayerAnimation = new SpriteAnimation(GameLevelManager::GetInstance()->getcurrentLevel()->GetMeshList(SceneBase::GEO_PLAYER));
	PlayerAnimation->AddAnimation("Idle", 0, 0);
	PlayerAnimation->AddAnimation("Walking", 0, 5);
	PlayerAnimation->AddAnimation("Jumping", 6, 8);
	PlayerAnimation->AddAnimation("Falling", 9, 11);
	PlayerAnimation->PlayAnimation("Idle", -1, 6.f);
}

Player::~Player()
{
}


void Player::Update(double dt, float m_speed)
{
	static Vector3 maxpoint = Vector3(GameLevelManager::GetInstance()->getcurrentLevel()->getworldWidth(),
								GameLevelManager::GetInstance()->getcurrentLevel()->getworldHeight(),
								pos.z);
	double x, y;
	Application::GetCursorPos(&x, &y);
	int w = Application::GetWindowWidth();
	int h = Application::GetWindowHeight();
	mouseWorld = Vector3((x / w) * getsceneWidth(), getsceneHeight() - (y / h) * getsceneHeight());
	mouseWorld += GameLevelManager::GetInstance()->getcurrentLevel()->camera.position;
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

	static bool ShiftPressed = false;
	if (!ShiftPressed && cKeyboardController->IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
	{
		ShiftPressed = true;
		SlowTimeStart = true;
		GameLevelManager::GetInstance()->getcurrentLevel()->m_speed = 1.f;
	}
	else if (ShiftPressed && !cKeyboardController->IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
	{
		ShiftPressed = false;
		SlowTimeEnd = true;
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

	if (cKeyboardController->IsKeyReleased(GLFW_KEY_R))
	{
		if (GameLevelManager::GetInstance()->getcurrentLevel()->getcloned() == false) // summon the clone
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
	if (cKeyboardController->IsKeyReleased(GLFW_KEY_TAB))
	{
		if ((playerclone != nullptr) && (curLocation != Entity::IN_AIR) && (getClone()->getCurLocation() != Entity::IN_AIR))
		{
			swap = true;
		}
		vel.SetZero();
		
		cKeyboardController->ResetKey(GLFW_KEY_TAB);
	}
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
						pos + (normal * scale.x), normal,scale, normal);
				GameLevelManager::GetInstance()->getcurrentLevel()->getProjectileList()->push_back(arrow);
				cout << "arrow created" << endl;
				break;
			}
			case STAFF:
			{
				CSoundController::GetInstance()->PlaySoundByID(2);
				Projectile* magicBall =
					ProjectileFactory::GetInstance()->produceProjectile(ProjectileFactory::PTYPE_MAGICBALL,
						pos + (normal * scale.x), normal, scale, normal);

					GameLevelManager::GetInstance()->getcurrentLevel()->getProjectileList()->push_back(magicBall);
					cout << "Magic ball created" << endl;
					break;
				}
				case PORTALGUN:
				{
					CSoundController::GetInstance()->PlaySoundByID(3);
					Projectile* portal =
						ProjectileFactory::GetInstance()->produceProjectile(ProjectileFactory::PTYPE_PORTAL,
							pos + (normal * scale.x), normal, scale, normal);
					GameLevelManager::GetInstance()->getcurrentLevel()->getProjectileList()->push_back(portal);
					cout << "portal created" << endl;
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
			PlayerAnimation->Reset();
			PlayerAnimation->PlayAnimation("Jumping", 1, getJumpForce() / -GamePhysics::GetInstance()->gravity.y);
		}

		vel.x = 0;
		if (curLocation == ON_GROUND)
		{
			PlayerAnimation->PlayAnimation("Idle", -1, 1);
			if (cKeyboardController->IsKeyPressed(GLFW_KEY_A) || cKeyboardController->IsKeyPressed(GLFW_KEY_D))
			{
				PlayerAnimation->Reset();
				PlayerAnimation->PlayAnimation("Walking", -1, 1.5);
			}
		}
		else if (curLocation == IN_AIR)
		{
			if (vel.y < 0)
			{
				PlayerAnimation->Reset();
				PlayerAnimation->PlayAnimation("Falling", 1, 2);
			}
		}
		if (cKeyboardController->IsKeyDown(GLFW_KEY_D))
		{
			if (pos.x + Default_Speed * dt < maxpoint.x - (scale.x / 2))
			{
				vel.x = Default_Speed;
				curDirection = RIGHT;
			}
		}

		else if (cKeyboardController->IsKeyDown(GLFW_KEY_A))
		{
			if (pos.x - Default_Speed * dt > scale.x / 2)
			{
				vel.x = -Default_Speed;
				curDirection = LEFT;
			}
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

	if (PlayerAnimation != NULL)
	{
		PlayerAnimation->Update(dt* m_speed);
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


void Player::Response(GameObject* go)
{
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

void Player::Render()
{
	if (PlayerAnimation != NULL) {
		GameLevelManager::GetInstance()->getcurrentLevel()->RenderAnimation(
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


