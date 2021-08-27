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
		CAVE_TILE,
		FRAGILE_CAVE_TILE,
		LAVA_TILE,
		STONE_WATERFALL_TILE,
		DOOR_1_TILE,
		DOOR_2_TILE,
		DOOR_3_TILE,
		DOOR_4_TILE,
		DOOR_5_TILE,
		DARK_FOREST_GRASS,
		DARK_FOREST_GROUND,
		OOB_TILE,
		NUM_TILE
	};
	GameObject* ProduceTile(TILE_LIST tile_name, Vector3 pos, Vector3 scale, Vector3 vel = Vector3(0, 0, 0), Vector3 normal = Vector3(1, 0, 0));
};






