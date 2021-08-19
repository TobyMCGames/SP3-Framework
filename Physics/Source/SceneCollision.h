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
	virtual void Exit();

	//void ResetList(void);
	GameObject* FetchGO();
	void ReturnGO(GameObject *go);

	/*void MakePillar(float x, float  y, float thickness, GameObject::GAMEOBJECT_TYPE type);
	void MakeThinWall(float x, float y, float angleDeg, float thickness, float height);
	void MakeThickWall(float x, float y, float angleDeg, float thickness, float height);
	void MakeFlipper(float x, float y, Vector3 pivotPos, float defaultAngle, float angleSpeed, float thickness, float height);*/

protected:
	SceneCollision();
	~SceneCollision();

	//Physics
	//std::vector<GameObject *> m_goList;

	float m_speed;
	int m_objectCount;
};

#endif