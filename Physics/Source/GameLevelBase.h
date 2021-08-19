#ifndef GAME_LEVEL_BASE_H
#define GAME_LEVEL_BASE_H

#include "SceneBase.h"
#include "Player.h"
#include "GamePhysics.h"
#include <vector>
#include <string>
#include "SceneCamera.h"
using namespace std;

class GameLevelBase : public SceneBase
{
private:
	const float TILEWIDTH = 5;
	const float TILEHEIGHT = 5;

	const int YTILE_SCREEN = 18;
	const int XTILE_SCREEN = 32;

protected:
	vector<GameObject*>map;
	vector<AdvanceGO*> EntityList;
	vector<AdvanceGO*> projectileList;
	Player* player;
	float m_worldWidth;
	float m_worldHeight;

public:
	GameLevelBase();
	~GameLevelBase();
	virtual void Init() = 0;
	virtual bool Update(double dt) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
	virtual void RenderPlayer();
	bool loadMap(std::string file_path);
	float getworldWidth();
	float getworldHeight();
	float getTileWidth();
	float getTileHeight();
	
	
	bool CheckWithinScreen(GameObject* go);
	void CollisionChecks(double dt, float m_speed);

	std::vector<AdvanceGO*>* getProjectileList();
};

#endif