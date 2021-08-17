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
		GO_PILLAR,
		GO_FLIPPER,
		GO_FLIPPER_PILLAR,

		// MOBS
		GO_PLAYER,
		GO_PLAYERCLONE,
		GO_SKELEARCHER,
		GO_ZOMBIE,
		GO_TURRET,
		GO_SPIDER,
		GO_BOOMER,
		GO_DEMONLORD,

		// PROJECTILES

		GO_ARROW,
		GO_MAGICBALL,
		GO_SKELEARROW,
		GO_DEMONBALL,

		// TILES
		BRICK_TILE,
		STONE_BRICK_TILE,

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

	// SP3 Values for Entities, Projectile & Tiles
	int health;
	int damage;
	float Default_Speed;

	virtual void Response(GameObject*) = 0;


	GameObject(GAMEOBJECT_TYPE typeValue = GO_BALL);
	~GameObject();

};

struct dirt : public GameObject
{
	friend GameObject;
	void Response(GameObject*) {};
	dirt() { type = GAMEOBJECT_TYPE::GO_CUBE; };
	~dirt() {};
};

struct passive_tile : public GameObject
{
	friend GameObject;
	void Response(GameObject*) {};
	passive_tile() { type = GAMEOBJECT_TYPE::GO_CUBE; };
	passive_tile(GAMEOBJECT_TYPE objtype) { this->type = objtype;}
	~passive_tile() {};
};
#endif