#ifndef GAME_LEVEL_FINAL_H
#define GAME_LEVEL_FINAL_H

#include "GameObject.h"
#include <vector>
#include "GameLevelBase.h"
#include "GamePhysics.h"
#include "Player.h"
#include "Entity.h"

class LevelFinal : public GameLevelBase, public SingletonPattern<LevelFinal>
{
	friend SingletonPattern<LevelFinal>;
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
	LevelFinal();
	~LevelFinal();

	int curSubLevel = 1;
	int numSubLevels = 1;
};

#endif