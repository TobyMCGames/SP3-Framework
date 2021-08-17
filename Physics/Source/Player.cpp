#include "Player.h"
#include "Application.h"
#include "GameLevelManager.h"
Player::Player()
	: curWeapon(BOW)
	, curItem(0)
	, scrollsnap(0)
	, mana(100)
{
	for (int i = 0; i < NUM_ITEMS; i++)
	{
		Inventory[i] = 0;
	}
	health = 100;
	
}

Player::~Player()
{
}


void Player::Update(double dt)
{
	static Vector3 maxpoint = Vector3(GameLevelManager::GetInstance()->getcurrentLevel()->getworldWidth(),
								GameLevelManager::GetInstance()->getcurrentLevel()->getworldHeight(),
								pos.z);

	if (Application::IsKeyPressed('W'))
	{
		if (pos.y + vel.y < maxpoint.y - scale.y / 2)
			pos.y += vel.y;
		else
			pos.y = maxpoint.y - scale.y / 2;
	}

	if (Application::IsKeyPressed('S'))
	{
		if (pos.y - vel.y > scale.y / 2)
			pos.y -= vel.y;
		else
			pos.y = scale.y / 2;
	}

	if (Application::IsKeyPressed('A'))
	{
		if (pos.x - vel.x > scale.x / 2)
			pos.x -= vel.x;
		else
			pos.x = scale.x / 2;
	}

	if (Application::IsKeyPressed('D'))
	{
		if (pos.x + vel.x < maxpoint.x - scale.x / 2)
			pos.x += vel.x;
		else
			pos.x = maxpoint.x - scale.x / 2;
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
}

void Player::Response(GameObject*)
{
}
