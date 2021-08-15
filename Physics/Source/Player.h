#pragma once
#include "SingletonPattern.h"

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

	

protected:

};

