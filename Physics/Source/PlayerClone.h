#pragma once
#include "PlayerBase.h"
//#include "SoundController.h"
class PlayerClone :public PlayerBase
{
private:
	int Inventory[NUM_ITEMS];
	PlayerBase::Weapons curWeapon;
	int curItem;
	double scrollsnap;
	bool controlled;

public:
	PlayerClone();
	~PlayerClone();
	virtual void Update(double dt, float m_speed);
	virtual void Response(GameObject* go);
	virtual void setcurWeapon(Weapons curWeapon);
	virtual Weapons getcurWeapon();
	void setInventory(int Inventory[]);
	void Init(Vector3 pos,Vector3 vel, Vector3 scale,Vector3 normal);
	virtual bool isControl();
	void setControl(bool controlled);
	Vector3 getpos();
	Vector3 getvel();
	Vector3 getscale();
	Vector3 getnormal();
	void setpos(Vector3 pos);
	void setvel(Vector3 vel);
	void setsscale(Vector3 scale);
	void setnormal(Vector3 normal);
	void setcurLocation(Entity::LOCATION curLocation);
};
