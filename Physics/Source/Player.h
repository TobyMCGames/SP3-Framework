#pragma once
#include "SingletonPattern.h"
#include "Entity.h"

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

protected:
	int Inventory[NUM_ITEMS];
	Weapons curWeapon;

	int curItem;
	double scrollsnap;

	Player();
	~Player();
};

