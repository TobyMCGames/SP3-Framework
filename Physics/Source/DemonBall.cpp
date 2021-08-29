#include "Arrow.h"
#include "DemonBall.h"
#include "GameLevelManager.h"
#include "TileFactory.h"

DemonBall::DemonBall()
{
	Default_Speed = 30.f;
	damage = 25;
}

DemonBall::~DemonBall()
{
}

void DemonBall::Update(double dt, float m_speed)
{
	pos += vel * dt * m_speed;
}

void DemonBall::Response(GameObject* go)
{
	vel = normal * Default_Speed;
	if (go->type > PASSIVE_TILE_START && go->type < PASSIVE_TILE_END)
	{
		if (go->type == TREE_SAPLING_TILE)
		{
			if (go->pos == go->OGpos)
			{
				go->pos.y += go->scale.y;
				go->scale.Set(go->scale.x * 3, go->scale.y * 3, 1);
			}
			else
			{
				go->pos = go->OGpos;
				go->scale.Set(go->scale.x / 3, go->scale.y / 3, 1);
			}
			//active = false;
		}
		else
		{
			std::vector<GameObject*>* map = GameLevelManager::GetInstance()->getcurrentLevel()->getMap();
			for (int i = 0; i < map->size(); i++)
			{
				if (map->at(i) == go)
				{
					GameObject* curTile = map->at(i);
					GameObject* tile;
					switch (go->type)
					{
					case SOIL_TILE:
						tile = GameLevelManager::GetInstance()->getcurrentLevel()->ChangeMapObject(GRASS_SOIL_TILE, curTile);
						delete map->at(i);
						map->at(i) = tile;
						break;
					case GRASS_SOIL_TILE:
						tile = GameLevelManager::GetInstance()->getcurrentLevel()->ChangeMapObject(SOIL_TILE, curTile);
						delete map->at(i);
						map->at(i) = tile;
						break;
					default:
						tile = GameLevelManager::GetInstance()->getcurrentLevel()->ChangeMapObject(LAVA_TILE, curTile);
						delete map->at(i);
						map->at(i) = tile;
						break;
					}
					break;
				}
			}
		}
	}
}

void DemonBall::Render()
{
}

