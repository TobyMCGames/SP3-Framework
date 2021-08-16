#pragma once
#include "SingletonPattern.h"
#include "Entity.h"

class Player : public SingletonPattern<Player>
{
	friend SingletonPattern<Player>;
public:
	enum materials
	{
		ELASTIC,
		NON_ELASTIC,
		NUM_MATERIAL
	};

	Player();
	~Player();
	virtual void Responses(GameObject*);
	

protected:

};

