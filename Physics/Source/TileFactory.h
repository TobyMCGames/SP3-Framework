#pragma once
#include "SingletonPattern.h"
#include "Tile.h"

class TileFactory :public SingletonPattern<TileFactory>
{
public:
	enum TILE_LIST
	{
		BRICK,
		STONEBRICK,
		SPIKE,
		SOIL,
		GRASS_SOIL,
		NUM_TILE
	};
	GameObject* ProduceTile(TILE_LIST tile_name, Vector3 pos, Vector3 scale, Vector3 vel = Vector3(0, 0, 0), Vector3 normal = Vector3(1, 0, 0));
};






