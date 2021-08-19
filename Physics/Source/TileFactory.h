#pragma once
#include "Tile.h"

class TileFactory
{
public:
	enum TILE_LIST
	{
		BRICK,
		STONEBRICK,
		SPIKE,
		// leave this last
		NUM_TILE
	};

	static GameObject* getObject(int choice,Vector3 pos, Vector3 vel, Vector3 scale, Vector3 normal = Vector3(1,0,0));
	TileFactory();
	~TileFactory();
	

private:
	static Tile* TilePrototypes[NUM_TILE];
};

Tile* TileFactory::TilePrototypes[] = {
	new Tile(GameObject::GAMEOBJECT_TYPE::BRICK_TILE),
	new Tile(GameObject::GAMEOBJECT_TYPE::STONE_BRICK_TILE),
	new Tile(GameObject::GAMEOBJECT_TYPE::SPIKE_TILE),
};

GameObject* TileFactory::getObject(int choice,Vector3 pos,Vector3 vel,Vector3 scale,Vector3 normal) {
	return TilePrototypes[choice]->clone(pos,vel,scale,normal);
}

TileFactory::TileFactory()
{

}

TileFactory::~TileFactory()
{
	// delete array here	
	int arrsize = sizeof(TilePrototypes) / sizeof(TilePrototypes[0]);
	for (int i = 0; i < arrsize; i++)
	{
		delete TilePrototypes[i];
		TilePrototypes[i] = nullptr;
	}
}






