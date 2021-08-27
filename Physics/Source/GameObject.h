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
		ENTITY_START,
		GO_PLAYER,
		GO_PLAYERCLONE,
		GO_SKELEARCHER,
		GO_ZOMBIE,
		GO_TURRET,
		GO_SPIDER,
		GO_BOOMER,
		GO_NYMPH,
		GO_DEMONLORD,
		ENTITY_END,

		// PROJECTILES
		PROJECTILE_START,
		GO_ARROW,
		GO_MAGICBALL,
		GO_SKELEARROW,
		GO_DEMONBALL,
		GO_PORTAL,
		GO_BOMB,
		GO_SPIDERWEB,
		GO_TURRETBULLET,
		PROJECTILE_END,

		// TILES
		PASSIVE_TILE_START,
		BRICK_TILE,
		STONE_BRICK_TILE,
		SPIKE_TILE,
		SOIL_TILE,
		GRASS_SOIL_TILE,
		CAVE_TILE,
		FRAGILE_CAVE_TILE,
		LAVA_TILE,
		STONE_WATERFALL_TILE,
		TREE_SAPLING_TILE,
		DARK_FOREST_GROUND,
		DARK_FOREST_GRASS,
		CASTLE_PLATFORM,
		LARGE_STONE_2,
		PASSIVE_TILE_END,

		AGGRO_TILE_START,
		OUTOFBOUNDS_TILE,
		AGGRO_TILE_END,

		// INTERACTABLES
		INTERACTABLE_START,
		WEAPON_STATION_BOW,
		WEAPON_STATION_STAFF,
		WEAPON_STATION_PORTAL,
		PORTAL_GATE_ENTRANCE,
		PORTAL_GATE_EXIT,
		WARP_GATE,
		BOMB_CRATE,
		TREE_SEEDS,
		VINE_SEEDS,
		FALLING_PLATFORM,
		DOOR_1_TILE,
		DOOR_2_TILE,
		DOOR_3_TILE,
		DOOR_4_TILE,
		DOOR_5_TILE,
		COIN,
		HEALTHPOTION,
		INTERACTABLE_END,

		GO_TOTAL //must be last
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
	Vector3 OGpos;

	virtual void Response(GameObject* go) = 0;
	virtual void Render() = 0;
	//virtual void timeTravel() = 0;
	

	GameObject(GAMEOBJECT_TYPE typeValue = GO_BALL);
	~GameObject();
	void setTransform(Vector3 pos, Vector3 vel, Vector3 scale);
};
#endif