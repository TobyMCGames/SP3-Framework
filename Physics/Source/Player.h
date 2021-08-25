#pragma once
#include "SingletonPattern.h"
#include "PlayerBase.h"
#include "PlayerClone.h"
#include "SpriteAnimation.h"
#include "Portal.h"

class Player : public PlayerBase , public SingletonPattern<Player>
{
	friend SingletonPattern<Player>;
public:
	virtual void Update(double dt, float m_speed);
	// Slow down time mechanic
	bool getSwap();
	void setSwap(bool swap);
	virtual void setcurWeapon(Weapons curWeapon);
	virtual void Response(GameObject* go);
	virtual Weapons getcurWeapon();
	PlayerClone* getClone();
	void InitClone();
	void resetClone();
	virtual bool isControl();
	void setControl(bool controlled);
	bool cloneinited;
	virtual void Render();
	SpriteAnimation* getAnimation();
	int portalCounter;

	bool isCompleted;
	
protected:
	int Inventory[NUM_ITEMS];
	Weapons curWeapon;
	int curItem;
	double scrollsnap;
	PlayerClone* playerclone;
	Portal* portal;
	bool swap; 
	bool controlled;
	bool SlowTimeStart;
	bool SlowTimeEnd;
	bool isWebbedBySpider;
	Vector3 Pexitspeed;
	bool teleport;
	float webbedTimeLeft;
	
private:
	Player();
	~Player();
	SpriteAnimation* PlayerAnimation;

};

