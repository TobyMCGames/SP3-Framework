#include "PlayerBase.h"
#include "Application.h"
#include "KeyboardController.h"
#include "GLFW/glfw3.h"
#include "PlayerClone.h"
#include "GameLevelManager.h"
#include "ProjectileFactory.h"



void PlayerBase::Update(double dt, float m_speed)
{
}

void PlayerBase::Response(GameObject* go)
{
	
}

void PlayerBase::dead()
{
}

int PlayerBase::getScrollSensitivity()
{
	return scrollSensitivity;
}

float PlayerBase::getJumpForce()
{
	return JumpForce;
}

float PlayerBase::getsceneWidth()
{
	return current_scene_worldwidth;
}

float PlayerBase::getsceneHeight()
{
	return current_scene_worldheight;
}

void PlayerBase::setsceneWidth(float scenewidth)
{
	this->current_scene_worldwidth = scenewidth;
}

void PlayerBase::setsceneHeight(float sceneheight)
{
	current_scene_worldheight = sceneheight;
}


float PlayerBase::getmana()
{
	return mana;
}

int PlayerBase::getCoins()
{
	return coins;
}

int PlayerBase::gethealth()
{
	return health;
}

void PlayerBase::playRandHurtSound()
{
	int randHurtSound = rand() % 3;

	if (randHurtSound == 0)
		CSoundController::GetInstance()->PlaySoundByID(5);
	else if (randHurtSound == 1)
		CSoundController::GetInstance()->PlaySoundByID(6);
	else if (randHurtSound == 2)
		CSoundController::GetInstance()->PlaySoundByID(7);
}


PlayerBase::PlayerBase()
	:mana(100)
	,coins(0)
	,SlowTime(false)
	,TimeSpeed(1)
	,current_scene_worldwidth(0)
	,current_scene_worldheight(0)
{
	
}

PlayerBase::~PlayerBase()
{
}


