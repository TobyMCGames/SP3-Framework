#pragma once
#include "SingletonPattern.h"
#include "Entity.h"
#include "GamePhysics.h"
#include "Arrow.h"
#include "MagicBall.h"
#include "Portal.h"

class Player : public Entity, public SingletonPattern<Player>
{
	friend SingletonPattern<Player>;

	const int scrollSensitivity = 3;
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

	virtual void Update(double dt);
	virtual void Response(GameObject*);
	Player::Weapons GetCurrentWeapon();
	float mana;

	Vector3 mouseWorld;
	Vector3 playerToMouseDir;

	bool FireWeapon;

protected:
	int Inventory[NUM_ITEMS];
	Weapons curWeapon;

	int curItem;
	double scrollsnap;
	float current_scene_worldwidth;
	float current_scene_worldheight;
	Player();
	~Player();
};

