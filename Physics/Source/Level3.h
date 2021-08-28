#ifndef GAME_LEVEL_3_H
#define GAME_LEVEL_3_H

#include "GameObject.h"
#include <vector>
#include "GameLevelBase.h"
#include "GamePhysics.h"
#include "Player.h"
#include "Entity.h"
#include "GameLevelManager.h"

class Level3 : public GameLevelBase, public SingletonPattern<Level3>
{
	friend SingletonPattern<Level3>;
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

	//void ResetList(void);
	GameObject* FetchGO();
	void ReturnGO(GameObject *go);

	void UpdateLevel();

protected:
	Level3();
	~Level3();

	//Physics
	//std::vector<GameObject *> m_goList;

	int m_objectCount;

	int curSubLevel = 1;
	int numSubLevels = 3;
};

#endif