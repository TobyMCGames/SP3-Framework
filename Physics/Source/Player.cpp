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
	, FireWeapon(false)
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

	//SOUNDS
	//arrowSound = createIrrKlangDevice();
	//magicballSound = createIrrKlangDevice();
	//portal = createIrrKlangDevice();
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

	static bool bLButtonState = false;
	if (!bLButtonState && Application::IsMousePressed(0))
	{
		bLButtonState = true;
	}
	else if (bLButtonState && !Application::IsMousePressed(0))
	{
		bLButtonState = false;
		FireWeapon = true;
		switch (curWeapon)
		{
		case BOW:
			{
			//arrowSound->play2D("..\\Physics\\Sounds\\Sounds_Projectiles\\Arrow.wav", false);
			Projectile* arrow = 
				ProjectileFactory::GetInstance()->produceProjectile(ProjectileFactory::PTYPE_ARROW,
					pos + (normal*scale.x), normal, scale, normal);
				GameLevelManager::GetInstance()->getcurrentLevel()->getProjectileList()->push_back(arrow);
				cout << "arrow created" << endl;
				break;
			}
		case STAFF:
			{
		//	magicballSound->play2D("..\\Physics\\Sounds\\Sounds_Projectiles\\Magic_Ball.wav", false);
			Projectile* magicBall =
				ProjectileFactory::GetInstance()->produceProjectile(ProjectileFactory::PTYPE_MAGICBALL,
					pos + (normal * scale.x), normal, scale, normal);

				GameLevelManager::GetInstance()->getcurrentLevel()->getProjectileList()->push_back(magicBall);
				cout << "Magic ball created" << endl;
				break;
			}
		case PORTALGUN:
			{
		// 	portal->play2D("..\\Physics\\Sounds\\Sounds_Projectiles\\Portal_2.wav", false);
				Projectile* portal = 
					ProjectileFactory::GetInstance()->produceProjectile(ProjectileFactory::PTYPE_PORTAL,
						pos + (normal * scale.x), normal, scale, normal);
				GameLevelManager::GetInstance()->getcurrentLevel()->getProjectileList()->push_back(portal);
				cout << "portal created" << endl;
				break;
			}
		}
	}
	FireWeapon = false;

	if (cKeyboardController->IsKeyPressed(GLFW_KEY_SPACE) && curLocation == Entity::ON_GROUND)
	{
		vel.y += JumpForce;
		curLocation = IN_AIR;
	}

	if (cKeyboardController->IsKeyPressed(GLFW_KEY_A) && cKeyboardController->IsKeyPressed(GLFW_KEY_D))
	{
		vel.x = 0;
	}

	else if (cKeyboardController->IsKeyPressed(GLFW_KEY_D))
	{
		if (pos.x + Default_Speed * dt < maxpoint.x - (scale.x / 2))
			vel.x = Default_Speed;
	}

	else if (cKeyboardController->IsKeyPressed(GLFW_KEY_A))
	{
		if (pos.x - Default_Speed * dt > scale.x / 2)
			vel.x = -Default_Speed;
	}

	if (!cKeyboardController->IsKeyPressed(GLFW_KEY_A) && !cKeyboardController->IsKeyPressed(GLFW_KEY_D))
	{
		vel.x = 0;
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
		(go->type == GameObject::GO_ZOMBIE))
	{
		takeDamage(go->damage);

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

//void Player::SetSounds()
//{
//	if (!arrowSound) {
//		arrowSound = createIrrKlangDevice();
//	}
//}

Player::Weapons Player::GetCurrentWeapon()
{
	return curWeapon;
}