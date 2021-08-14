#ifndef SCENE_COLLISION_H
#define SCENE_COLLISION_H

#include "GameObject.h"
#include <vector>
#include "SceneBase.h"
#include "PlayerA2.h"

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
	bool CheckCollision(GameObject* go1, GameObject* go2, float dt);
	void CheckCollisionResponse(GameObject* go1, GameObject* go2, float dt);

	void MakePillar(float x, float  y, float thickness, GameObject::GAMEOBJECT_TYPE type);
	void MakeThinWall(float x, float y, float angleDeg, float thickness, float height);
	void MakeThickWall(float x, float y, float angleDeg, float thickness, float height);
	void MakeFlipper(float x, float y, Vector3 pivotPos, float defaultAngle, float angleSpeed, float thickness, float height);


	void level1();
	void level2();
	void level3();
protected:

	//Physics
	std::vector<GameObject *> m_goList;

	float m_speed;
	float m_worldWidth;
	float m_worldHeight;
	GameObject *m_ghost;
	int m_objectCount;

	//Line Drawing
	PlayerA2 player;
	GameObject* ball;
	GameObject* spawner;
	GameObject* goal;

	std::vector<GameObject*>* shape;                    //temporarily stores current line being drawn
	std::vector< std::vector<GameObject*>*> shape_list; //Stores all shapes drawn on screen
	Vector3 start;                                      //Start of line being drawn

	int ShapeCount = 0;
	float CurInkCost = 0;
	std::vector<int> LastInkCost;

	//Level Control
	int curLevel = 1;
	int num_levels = 3;
	bool levelCompleted;

	//Auditing
	float m1, m2;
	Vector3 u1, u2, v1, v2;
};

#endif