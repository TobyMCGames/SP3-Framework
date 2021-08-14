#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Vector3.h"

struct GameObject
{
	enum GAMEOBJECT_TYPE
	{
		GO_NONE = 0,
		GO_BALL,
		GO_CUBE,
		GO_WALL,
		GO_NONELASTIC_WALL,
		GO_PILLAR,
		GO_NONELASTIC_PILLAR,
		GO_FLIPPER,
		GO_FLIPPER_PILLAR,
		GO_BOUNCER,
		GO_DISPENSER,
		GO_GOAL,

		GO_TOTAL, //must be last
	};
	GAMEOBJECT_TYPE type;
	Vector3 pos;
	Vector3 vel;
	Vector3 scale;
	Vector3 normal;
	float hp;
	bool active;
	float mass;
	GameObject* target;

	Vector3 dir; //direction/orientation
	float momentOfInertia;
	float angularVelocity; //in radians
	Vector3 pivot;

	float timer;


	GameObject(GAMEOBJECT_TYPE typeValue = GO_BALL);
	~GameObject();
};

#endif