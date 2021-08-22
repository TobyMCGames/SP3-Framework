#pragma once
#include "Player.h"
//#include "SoundController.h"

class PlayerClone : public Player
{
private:
	bool controlled; 
	Weapons clonedWeapon;

public:
	PlayerClone();
	~PlayerClone();
	bool update(double dt, float m_speed);
	Player::Weapons getcloneWeapon();
	bool isControlled();
};

