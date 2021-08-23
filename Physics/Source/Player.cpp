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
	, mana(100)
	, cKeyboardController(NULL)
	, animation1(NULL)
	, FireWeapon(false)
	, cloned(false)
	, cloningmode(false)
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
	FireWeapon = false;

	// Slow down time mechanic
	TimeSpeed = 1.f; // is this variable even used?
	SlowTime = false;

	// Init sprite
	animation1 = new SpriteAnimation(GameLevelManager::GetInstance()->getcurrentLevel()->GetMeshList(SceneBase::GEO_PLAYER));
	animation1->AddAnimation("Idle", 0, 0);
	animation1->AddAnimation("Walking", 0, 5);
	animation1->AddAnimation("Jumping", 6, 8);
	animation1->AddAnimation("Falling", 9, 11);

	animation1->PlayAnimation("Idle", -1, 6.f);
}

Player::~Player()
{
}

void Player::dead()
{
	// handle restart level, go to main menu, dead screen idk 
	health = 100;
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
	mouseWorld = Vector3((x / w) * current_scene_worldwidth, current_scene_worldheight - (y / h) * current_scene_worldheight);
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

	if (cKeyboardController->IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
	{
		SlowTime = true;
		GameLevelManager::GetInstance()->getcurrentLevel()->m_speed = 1.f;
	}
	if (cKeyboardController->IsKeyReleased(GLFW_KEY_LEFT_SHIFT))
	{
		SlowTime = false;
		GameLevelManager::GetInstance()->getcurrentLevel()->m_speed = 2.7f;
	}

	if (cKeyboardController->IsKeyReleased(GLFW_KEY_R))
	{
		if (cloned == false) // create the clone
		{
			cloningmode = true;
		}
			// reposition

		// check if player already has a clone on screen.
		// go into summoning mode
		// else ignore.
	}
	static bool bLButtonState = false;
	if (!bLButtonState && Application::IsMousePressed(0))
	{
		bLButtonState = true;
	}
	else if (bLButtonState && !Application::IsMousePressed(0))
	{
		
		bLButtonState = false;
		if (cloningmode == false)
		{
			FireWeapon = true;
			switch (curWeapon)
				{
				case BOW:
				{
					CSoundController::GetInstance()->PlaySoundByID(1);
					Projectile* arrow =
						ProjectileFactory::GetInstance()->produceProjectile(ProjectileFactory::PTYPE_ARROW,
							pos + (normal * scale.x), normal, scale, normal);
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
		else // create the clone here
		{
			GameLevelManager::GetInstance()->getcurrentLevel()->
				createPlayerClone(mouseWorld, Vector3(0, 0, 0), Vector3(scale.x, scale.y, scale.z), normal);
			cloned = true;
			cloningmode = false;
		}
		
	}
	FireWeapon = false;

	vel.x = 0;
	if (curLocation == ON_GROUND)
	{
		animation1->PlayAnimation("Idle", -1, 1);
		if (cKeyboardController->IsKeyPressed(GLFW_KEY_A) || cKeyboardController->IsKeyPressed(GLFW_KEY_D))
		{
			animation1->Reset();
			animation1->PlayAnimation("Walking", -1, 1.5);
		}
	}
	else if (curLocation == IN_AIR)
	{
		if (vel.y < 0)
		{
			animation1->Reset();
			animation1->PlayAnimation("Falling", 1, 2);
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
		animation1->PlayAnimation("Idle", -1, 1);
	}
	
	if (cKeyboardController->IsKeyPressed(GLFW_KEY_SPACE) && curLocation == Entity::ON_GROUND)
	{
		//cSoundController->PlaySoundByID(2);
		CSoundController::GetInstance()->PlaySoundByID(4);
		vel.y += JumpForce;
		curLocation = IN_AIR;
		animation1->Reset();
		animation1->PlayAnimation("Jumping", 1, JumpForce / -GamePhysics::GetInstance()->gravity.y);
	}

	scrollsnap += Application::GetYScrollOffset();

	if (scrollsnap > scrollSensitivity)
	{
		curItem++;
		scrollsnap = 0;
	}
	else if (scrollsnap < 0)
	{
		curItem--;
		scrollsnap = scrollSensitivity;
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

	if (animation1 != NULL)
	{
		animation1->Update(dt* m_speed);
	}
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
		
		if(randHurtSound == 0)
			CSoundController::GetInstance()->PlaySoundByID(5);
		else if(randHurtSound == 1)
			CSoundController::GetInstance()->PlaySoundByID(6);
		else if (randHurtSound == 2)
			CSoundController::GetInstance()->PlaySoundByID(7);

		if (health <= 0)
		{
			dead();
		}
	}
	if (cKeyboardController->IsKeyPressed(GLFW_KEY_E))
	{
		switch (go->type)
		{
		case WEAPON_STATION_BOW:
			curWeapon = BOW;
			break;
		case WEAPON_STATION_STAFF:
			curWeapon = STAFF;
			break;
		case WEAPON_STATION_PORTAL:
			curWeapon = PORTALGUN;
			break;
		}
	}
}

void Player::Render()
{
	if (animation1 != NULL) {
		GameLevelManager::GetInstance()->getcurrentLevel()->RenderAnimation(
			animation1->GetSprite(),
			animation1->GetCurFrame(),
			6,
			2,
			6,
			false
		);
	}
}

bool Player::iscloned()
{
	return cloned;
}

Player::Weapons Player::GetCurrentWeapon()
{
	return curWeapon;
}