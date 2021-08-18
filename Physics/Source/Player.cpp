#include "Player.h"
#include "Application.h"
#include "KeyboardController.h"
#include "GLFW/glfw3.h"
#include "GameLevelManager.h"
Player::Player()
	: curWeapon(BOW)
	, curItem(0)
	, scrollsnap(0)
	, mana(100)
	, cKeyboardController(NULL)
{
	for (int i = 0; i < NUM_ITEMS; i++)
	{
		Inventory[i] = 0;
	}
	health = 100;
	Default_Speed = 20;
	cKeyboardController = CKeyboardController::GetInstance();
}

Player::~Player()
{
}


void Player::Update(double dt)
{
	static Vector3 maxpoint = Vector3(GameLevelManager::GetInstance()->getcurrentLevel()->getworldWidth(),
								GameLevelManager::GetInstance()->getcurrentLevel()->getworldHeight(),
								pos.z);
	vel.y = 0;
	if (cKeyboardController->IsKeyDown(GLFW_KEY_W))
	{
		if (pos.y + Default_Speed * dt < maxpoint.y - scale.y / 2)
			vel.y = Default_Speed;
	}

	if (cKeyboardController->IsKeyDown(GLFW_KEY_S))
	{
		if (pos.y - Default_Speed * dt > scale.y / 2)
			vel.y = -Default_Speed;
	}

	vel.x = 0;
	if (cKeyboardController->IsKeyDown(GLFW_KEY_A))
	{
		if (pos.x - Default_Speed * dt > scale.x / 2)
			vel.x = -Default_Speed;
	}

	if (cKeyboardController->IsKeyDown(GLFW_KEY_D))
	{
		if (pos.x + Default_Speed * dt < maxpoint.x - scale.x / 2)
			vel.x = Default_Speed;
	}
	
	if (cKeyboardController->IsKeyDown(GLFW_KEY_SPACE) && curLocation == Entity::ON_GROUND)
	{
		vel.y += JumpForce;
		curLocation = Entity::IN_AIR;

	}

	pos.x += vel.x * dt;
	pos.y += vel.y * dt;

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
}

void Player::Response(GameObject* go)
{
	if (go->type > GameObject::PASSIVE_TILE_START && go->type < GameObject::PASSIVE_TILE_END)
	{
		if (vel.x == 0 && go->normal.x != 0)
		{
			/*if (vel.y > 0)
				vel.y = 0;
			else
			curLocation = ON_GROUND;*/
		}
	}
}
