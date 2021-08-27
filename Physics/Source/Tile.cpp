#include "Tile.h"
#include "GameLevelManager.h"

Tile::Tile() :
	tiletype(PASSIVE_TILE),
	destructable(false)
{
}


Tile::~Tile()
{
}



void Tile::Response(GameObject* go)
{

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
