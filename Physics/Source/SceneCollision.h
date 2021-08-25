#ifndef GAME_LEVEL_COLLISION_H
#define GAME_LEVEL_COLLISION_H

#include "GameObject.h"
#include <vector>
#include "GameLevelBase.h"
#include "GamePhysics.h"
#include "Player.h"
#include "Entity.h"

class SceneCollision : public GameLevelBase, public SingletonPattern<SceneCollision>
{
	friend SingletonPattern<SceneCollision>;
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
	SceneCollision();
	~SceneCollision();

	//Physics
	//std::vector<GameObject *> m_goList;

	int m_objectCount;

	int curLevel = 1;
	int numLevel = 1;
};

#endif