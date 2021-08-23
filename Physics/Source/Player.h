#pragma once
#include "SingletonPattern.h"
#include "PlayerBase.h"
#include "PlayerClone.h"
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
	virtual void dead();
	virtual Weapons getcurWeapon();
	PlayerClone* getClone();
	void InitClone();
	virtual bool isControl();
	void setControl(bool controlled);
	bool cloneinited;
	
protected:
	int Inventory[NUM_ITEMS];
	Weapons curWeapon;
	int curItem;
	double scrollsnap;
	PlayerClone* playerclone;
	bool swap; 
	bool controlled;
	
private:
	Player();
	~Player();
};

