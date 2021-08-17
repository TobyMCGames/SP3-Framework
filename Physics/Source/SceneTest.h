#ifndef SCENETEST_H
#define SCENETEST_H

#include "GameObject.h"
#include <vector>
#include "GameLevelBase.h"
#include "GamePhysics.h"
#include "SingletonPattern.h"

class SceneTest : public GameLevelBase, public SingletonPattern<SceneTest>
{
	friend SingletonPattern<SceneTest>;
	static const int MIN_LINE_LENGTH = 2;
	static const int MAX_LINE_LENGTH = 4;
	static const int LINE_THICKNESS = 1;
	static const int DISPENSER_FORCE = 10;

public:

	virtual void Init();
	virtual bool Update(double dt);
	virtual void Render();
	virtual void Exit();

	void ResetList(void);

	void RenderGO(GameObject *go);

	GameObject* FetchGO();
	void ReturnGO(GameObject *go);

	/*void MakePillar(float x, float  y, float thickness, GameObject::GAMEOBJECT_TYPE type);
	void MakeThinWall(float x, float y, float angleDeg, float thickness, float height);
	void MakeThickWall(float x, float y, float angleDeg, float thickness, float height);
	void MakeFlipper(float x, float y, Vector3 pivotPos, float defaultAngle, float angleSpeed, float thickness, float height);*/

protected:
	SceneTest();
	~SceneTest();

	//Physics
	std::vector<GameObject*> m_goList;



	float m_speed;
	float m_worldWidth;
	float m_worldHeight;
	int m_objectCount;


};

#endif