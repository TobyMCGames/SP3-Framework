#include "Player.h"
#include "Application.h"
#include "KeyboardController.h"
#include "GLFW/glfw3.h"
#include "PlayerClone.h"


PlayerClone::PlayerClone() :
	controlled(false),
	clonedWeapon(Weapons::BOW)
{
}

PlayerClone::~PlayerClone()
{
}

bool PlayerClone::update(double dt, float m_speed)
{
	return true;
}

Player::Weapons PlayerClone::getcloneWeapon()
{
	return clonedWeapon;
}

bool PlayerClone::isControlled()
{
	return controlled;
}


