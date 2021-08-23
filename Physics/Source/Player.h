#pragma once
#include "SingletonPattern.h"
#include "Entity.h"
#include "GamePhysics.h"
#include "Arrow.h"
#include "MagicBall.h"
#include "Portal.h"
#include "KeyboardController.h"
#include "SpriteAnimation.h"

class Player : public Entity, public SingletonPattern<Player>
{
	friend SingletonPattern<Player>;

	const int scrollSensitivity = 3;
	const float JumpForce = 22;
public:
	enum Items
	{
		TREE_SEED,
		VINE_SEED,
		BOMBS,
		NUM_ITEMS
	};

	enum Weapons
	{
		BOW,
		STAFF,
		PORTALGUN
	};

	virtual void Update(double dt, float m_speed);
	virtual void Response(GameObject* go);
	virtual void Render();
	bool iscloned();
	Player::Weapons GetCurrentWeapon();
	float mana;
	Vector3 mouseWorld;
	Vector3 playerToMouseDir;

	
	bool FireWeapon;

	// Slow down time mechanic
	float TimeSpeed;
	bool SlowTime;

protected:
	int Inventory[NUM_ITEMS];
	Weapons curWeapon;
	bool cloned;
	bool cloningmode;
	int curItem;
	double scrollsnap;
	float current_scene_worldwidth;
	float current_scene_worldheight;
	Player();
	~Player();
	virtual void dead();

	CKeyboardController* cKeyboardController;

	SpriteAnimation* animation1;
};

