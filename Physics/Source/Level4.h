#ifndef GAME_LEVEL_4_H
#define GAME_LEVEL_4_H

#include "GameObject.h"
#include <vector>
#include "GameLevelBase.h"
#include "GamePhysics.h"
#include "Player.h"
#include "Entity.h"

class Level4 : public GameLevelBase, public SingletonPattern<Level4>
{
	friend SingletonPattern<Level4>;
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
	Level4();
	~Level4();
	int curSubLevel = 3;
	int numSubLevels = 3;
};

#endif