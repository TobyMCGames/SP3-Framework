#pragma once
#include "Entity.h"
//#include "SoundController.h"
#include "KeyboardController.h"
#include "GamePhysics.h"

class PlayerBase :public Entity
{
private:
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
		BARE_HANDS,
		BOW,
		STAFF,
		PORTALGUN
	};
	
	virtual void Update(double dt, float m_speed);
	virtual void Response(GameObject* go)=0;
	virtual void dead();
	int getScrollSensitivity();
	float getJumpForce();
	float getsceneWidth();
	float getsceneHeight();
	void setsceneWidth(float scenewidth);
	void setsceneHeight(float sceneheight);
	virtual Weapons getcurWeapon() = 0;
	virtual void setcurWeapon(Weapons curWeapon) =0;
	virtual bool isControl()=0;
	virtual void setControl(bool control)=0;
	float getmana();
	int gethealth();
	

protected:
	PlayerBase();
	~PlayerBase();

	Vector3 mouseWorld;
	Vector3 playerToMouseDir;
	CKeyboardController* cKeyboardController;
	float TimeSpeed;
	bool SlowTime;
	float current_scene_worldwidth;
	float current_scene_worldheight;
	float mana;
};
