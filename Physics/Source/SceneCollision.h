#ifndef SCENE_COLLISION_H
#define SCENE_COLLISION_H

#include "GameObject.h"
#include <vector>
#include "SceneBase.h"
#include "Player.h"
#include "GamePhysics.h"

class SceneCollision : public SceneBase
{
	static const int MIN_LINE_LENGTH = 2;
	static const int MAX_LINE_LENGTH = 4;
	static const int LINE_THICKNESS = 1;
	static const int DISPENSER_FORCE = 10;

public:
	SceneCollision();
	~SceneCollision();

	virtual void Init();
	virtual void Update(double dt);
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

	//Physics
	std::vector<GameObject *> m_goList;

	float m_speed;
	float m_worldWidth;
	float m_worldHeight;
	int m_objectCount;

	//Line Drawing
	Player* player;



};

#endif