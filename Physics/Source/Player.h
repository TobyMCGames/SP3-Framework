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
	float mana;
	void setmaxpoint(Vector3 maxpoint);
	Vector3 getmaxpoint();

protected:
	int Inventory[NUM_ITEMS];
	Weapons curWeapon;


	Vector3 maxpoint;
	int curItem;
	double scrollsnap;
	float current_scene_worldwidth;
	float current_scene_worldheight;
	Player();
	~Player();
};

