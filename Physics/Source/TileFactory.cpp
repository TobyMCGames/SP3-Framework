#include "TileFactory.h"
GameObject* TileFactory::ProduceTile(TILE_LIST tile_name, Vector3 pos, Vector3 scale, Vector3 vel, Vector3 normal)
{
	Tile* newTile = new Tile();
	switch (tile_name)
	{
		case BRICK:
			newTile->type = GameObject::BRICK_TILE;
			newTile->setDestructable(true);
			break;
		case STONEBRICK:
			newTile->type = GameObject::STONE_BRICK_TILE;
			break;
		case SPIKE:
			newTile->type = GameObject::SPIKE_TILE;
			break;
		case SOIL:
			newTile->type = GameObject::SOIL_TILE;
			break;
		case GRASS_SOIL:
			newTile->type = GameObject::GRASS_SOIL_TILE;
			break;
		case CAVE_TILE:
			newTile->type = GameObject::CAVE_TILE;
			break;
		case FRAGILE_CAVE_TILE:
			newTile->type = GameObject::FRAGILE_CAVE_TILE;
			break;
		case LAVA_TILE:
			newTile->type = GameObject::LAVA_TILE;
			break;
		case STONE_WATERFALL_TILE:
			newTile->type = GameObject::STONE_WATERFALL_TILE;
			break;
		case DOOR_1_TILE:
			newTile->type = GameObject::DOOR_1_TILE;
			break;
		case DOOR_2_TILE:
			newTile->type = GameObject::DOOR_2_TILE;
			break;
		case DOOR_3_TILE:
			newTile->type = GameObject::DOOR_3_TILE;
			break;
		case DOOR_4_TILE:
			newTile->type = GameObject::DOOR_4_TILE;
			break;
		case DOOR_5_TILE:
			newTile->type = GameObject::DOOR_5_TILE;
			break;
		case DARK_FOREST_GRASS:
			newTile->type = GameObject::DARK_FOREST_GRASS;
			break;
		case DARK_FOREST_GROUND:
			newTile->type = GameObject::DARK_FOREST_GROUND;
			break;
		case CASTLE_PLATFORM:
			newTile->type = GameObject::CASTLE_PLATFORM;
			break;
		case OOB_TILE:
			newTile->type = GameObject::OUTOFBOUNDS_TILE;
			break;
	}
	newTile->active = true;
	newTile->pos = pos;
	newTile->OGpos = pos;
	newTile->vel = vel;
	newTile->scale = scale;
	newTile->normal = normal;
	return newTile;
}