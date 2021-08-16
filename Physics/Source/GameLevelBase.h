#ifndef GAME_LEVEL_BASE_H
#define GAME_LEVEL_BASE_H

#include "SceneBase.h"
#include "Player.h"
#include "GamePhysics.h"
#include <vector>
#include <string>
using namespace std;

class GameLevelBase : public SceneBase
{
protected:
	vector<GameObject*>map;
	Player* player;
public:
	GameLevelBase();
	~GameLevelBase();
	virtual void Init() = 0;
	virtual void Update(double dt) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
	bool SetMap(string);
};

#endif