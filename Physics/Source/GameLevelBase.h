#ifndef GAME_LEVEL_BASE_H
#define GAME_LEVEL_BASE_H

#include "SceneBase.h"
#include "Player.h"
#include "GamePhysics.h"
#include <vector>
#include <string>
#include "SceneCamera.h"
#include <map>

using namespace std;

class GameLevelBase : public SceneBase
{
private:
	const float TILEWIDTH = 5;
	const float TILEHEIGHT = 5;

	const int YTILE_SCREEN = 18;
	const int XTILE_SCREEN = 32;
	std::map<std::string,int> Legend;

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
	bool loadLegend(std::string file_path);
	GameObject* getdictionaryObject(std::string key,Vector3 pos, Vector3 vel,Vector3 scale,Vector3 normal);
	bool loadMap(std::string file_path);
	const float GAMESPEED = 2.7f;
	float getworldWidth();
	float getworldHeight();
	float getTileWidth();
	float getTileHeight();
	void cleanupList(std::vector<int>* indexlist);
	bool CheckWithinScreen(GameObject* go);
	void CollisionChecks(double dt, float m_speed);

	float m_speed;
	std::vector<AdvanceGO*>* getProjectileList();
};

#endif