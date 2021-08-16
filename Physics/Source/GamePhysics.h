#pragma once
#include "SingletonPattern.h"
#include "GameObject.h"

class GamePhysics : public SingletonPattern<GamePhysics>
{
	friend SingletonPattern<GamePhysics>;

protected:
	Vector3 gravity;

	//Auditing
	float m1, m2;
	Vector3 u1, u2, v1, v2;

	GamePhysics();
	~GamePhysics();

public:
	void Update(GameObject* go, double dt);
	bool CheckCollision(GameObject* go1, GameObject* go2, double dt);
	void CheckCollisionResponse(GameObject* go1, GameObject* go2, double dt);

};

