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
	if (go->type == GameObject::GO_BOMB)
	{
		if (destructable == true)
			this->active = false;
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
