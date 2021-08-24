#ifndef GAME_LEVEL_BASE_H
#define GAME_LEVEL_BASE_H

#include "SceneBase.h"
#include "GamePhysics.h"
#include <vector>
#include <string>
#include "SceneCamera.h"
#include <map>
#include "PlayerClone.h"

using namespace std;

class GameLevelBase : public SceneBase
{
private:
	const float TILEWIDTH = 5;
	const float TILEHEIGHT = 5;

	const int YTILE_SCREEN = 18;
	const int XTILE_SCREEN = 32;
	const float offset = 0.005f;

protected:
	vector<GameObject*>map;
	vector<AdvanceGO*> EntityList;
	vector<AdvanceGO*> projectileList;
	vector<AdvanceGO*> InteractableList;
	Player* player;
	PlayerClone* playerclone;
	float m_worldWidth;
	float m_worldHeight;

public:
	GameLevelBase();
	~GameLevelBase();
	virtual void Init() = 0;
	virtual bool Update(double dt) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
	void RenderPlayer();
	void RenderPlayerClone();
	void createPlayerClone(Vector3 pos,Vector3 vel,Vector3 scale, Vector3 normal); // probably can make it generalised 

	void mapinitPlayer(Vector3 pos, Vector3 vel, Vector3 scale, Vector3 normal);
	bool loadMap(std::string file_path);
	//void SetMapInfo(const unsigned int uiRow, const unsigned int uiCol, const int iValue, const bool bInvert = true);
	//bool FindValue(const int iValue, unsigned int& uirRow, unsigned int& uirCol, const bool bInvert = true);
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
	std::vector<AdvanceGO*>* getInteractableList();
};

#endif