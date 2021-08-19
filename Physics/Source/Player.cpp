#include "Player.h"
#include "Application.h"
#include "KeyboardController.h"
#include "GLFW/glfw3.h"
#include "GameLevelManager.h"
#include "ProjectileFactory.h"
Player::Player()
	: curWeapon(Player::STAFF)
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
}

Player::~Player()
{
}


void Player::Update(double dt)
{
	Entity::Update(dt);

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
			Vector3 vel = playerToMouseDir * ArrowForce;
			Projectile* arrow = 
				ProjectileFactory::getObject
				(ProjectileFactory::PROJECTILE_TYPES::PTYPE_ARROW, pos, vel, scale,normal);
				GameLevelManager::GetInstance()->getcurrentLevel()->getProjectileList()->push_back(arrow);
				cout << "arrow created" << endl;
				break;
			}
		case STAFF:
			{
				Projectile* magicBall = 
					ProjectileFactory::getObject
					(ProjectileFactory::PROJECTILE_TYPES::PTYPE_MAGICBALL, pos,normal*10, scale, normal);
				GameLevelManager::GetInstance()->getcurrentLevel()->getProjectileList()->push_back(magicBall);
				cout << "Magic ball created" << endl;
				break;
			}
		case PORTALGUN:
			{
				Projectile* portal = 
					ProjectileFactory::getObject
					(ProjectileFactory::PROJECTILE_TYPES::PTYPE_PORTAL, pos,normal*5, scale, normal);
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
		cout << "In air" << endl;
	}
	curLocation = IN_AIR;
}

void Player::Response(GameObject* go)
{
	if (go->type > GameObject::PASSIVE_TILE_START && go->type < GameObject::PASSIVE_TILE_END)
	{
		if (vel.y == 0)
			curLocation = ON_GROUND;
	}
}

Player::Weapons Player::GetCurrentWeapon()
{
	return curWeapon;
}


