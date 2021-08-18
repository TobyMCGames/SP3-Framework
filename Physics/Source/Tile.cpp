#include "Tile.h"
#include "GameLevelManager.h"

Tile::Tile(): 
	tiletype(PASSIVE_TILE)
{
}
Tile::Tile(GameObject::GAMEOBJECT_TYPE objtype)
{
	this->type= objtype;
	switch (objtype)
	{
	case GAMEOBJECT_TYPE::SPIKE_TILE:
		tiletype = INTERACTIVE_TILE;
		break;
	default:
		tiletype = PASSIVE_TILE;
		break;
	}
}


Tile::~Tile()
{
}

/*
Tile* Tile::createTile(Vector3 pos, Vector3 vel, Vector3 Scale, Vector3 rotationAxis, float angle)
{
	this->pos = pos;
	this->active = true;
	this->scale = scale;
	this->vel = vel;
	return this;
}*/

GameObject* Tile::clone(Vector3 pos, Vector3 vel, Vector3 scale,Vector3 normal)
{
	Tile* newTile = new Tile();
	newTile->tiletype = tiletype;
	newTile->type = type;
	newTile->pos = pos;
	newTile->vel = vel;
	newTile->scale = scale;
	newTile->active = true;
	newTile->normal.Set(1, 0, 0);
	return newTile;
}

void Tile::Response(GameObject*)
{
	if (tiletype == TILE_TYPE::PASSIVE_TILE)
	{
		// passive response here
	}
	else if (tiletype == TILE_TYPE::INTERACTIVE_TILE)
	{
		// interactive response here
		
	}
}
