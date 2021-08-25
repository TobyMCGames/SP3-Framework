#include "Tile.h"
#include "GameLevelManager.h"

Tile::Tile() :
	tiletype(PASSIVE_TILE),
	destructable(true)
{
}


Tile::~Tile()
{
}



void Tile::Response(GameObject* go)
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

void Tile::Render()
{

}

bool Tile::getDestructable()
{
	return destructable;
}

void Tile::setDestructable(bool destructable)
{
	this->destructable = destructable;
}
