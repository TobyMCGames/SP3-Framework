#pragma once
#include "SingletonPattern.h"
#include "GameObject.h"

class GamePhysics : public SingletonPattern<GamePhysics>
{
	friend SingletonPattern<GamePhysics>;

protected:

	//Auditing
	float m1, m2;
	Vector3 u1, u2, v1, v2;

	GamePhysics();
	~GamePhysics();

	enum COLLIDEPOS
	{
		NOTHING,
		UP,
		DOWN,
		LEFT,
		RIGHT,
		TOP_RIGHT,
		TOP_LEFT,
		BOTTOM_RIGHT,
		BOTTOM_LEFT,
	};
	COLLIDEPOS collidepos;

public:
	Vector3 gravity;

	void Update(GameObject* go, double dt, float m_speed);
	bool CheckCollision(GameObject* go1, GameObject* go2, double dt, float m_speed);
	void CheckCollisionResponse(GameObject* go1, GameObject* go2, double dt, float m_speed);
	bool CheckCorner(GameObject* go1, GameObject* go2, double dt);
	COLLIDEPOS GetCollidePos();
	//AABB for projectiles
	bool AABB(GameObject* go1, GameObject* go2);
	bool DistanceCheck(GameObject* go1, GameObject* go2);
	COLLIDEPOS checkCollidePos(GameObject* go1, GameObject* go2);
};

