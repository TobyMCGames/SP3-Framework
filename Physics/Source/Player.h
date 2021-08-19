#pragma once
#include "SingletonPattern.h"
#include "Entity.h"
#include "GamePhysics.h"
#include "Arrow.h"
#include "MagicBall.h"
#include "Portal.h"
#include "KeyboardController.h"
#include "irrKlang.h"

using namespace irrklang;
#pragma comment(lib, "irrKlang.lib")

class Player : public Entity, public SingletonPattern<Player>
{
	friend SingletonPattern<Player>;

	const int scrollSensitivity = 3;
	const float JumpForce = 22;
	const float ArrowForce = 30;
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
	virtual void Response(GameObject* go);
	void SetSounds();
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

	CKeyboardController* cKeyboardController;

	//Player sounds
	ISoundEngine* arrowSound;
};

