#ifndef GAME_LEVEL_1_H
#define GAME_LEVEL_1_H

#include "GameObject.h"
#include <vector>
#include "GameLevelBase.h"
#include "GamePhysics.h"
#include "Player.h"
#include "Entity.h"

class Level1 : public GameLevelBase, public SingletonPattern<Level1>
{
	friend SingletonPattern<Level1>;
	static const int MIN_LINE_LENGTH = 2;
	static const int MAX_LINE_LENGTH = 4;
	static const int LINE_THICKNESS = 1;
	static const int DISPENSER_FORCE = 10;

public:

	virtual void Init();
	virtual bool Update(double dt);
	virtual void Render();
	virtual void Destroy();
	virtual void Exit();


	void UpdateLevel();

protected:
	Level1();
	~Level1();


	int numSubLevels = 3;
};

#endif