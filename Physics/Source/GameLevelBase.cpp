#include "GameLevelBase.h"
#include <fstream>
#include "Application.h"
#include "TileFactory.h"
#include "PrototypeFactory.h"

GameLevelBase::GameLevelBase()
{

}

GameLevelBase::~GameLevelBase()
{

}

bool GameLevelBase::loadMap(std::string file_path)
{
	ifstream file;
	file.open(file_path);
	if (!file.is_open()) {
		cout << "File can not be opened" << endl;
		return false;
	}
	std::vector<std::string> linesinreverse;
	int commacounter = 0;
	int highestcol = 0;
	Vector3 pos = Vector3(0, 0, 0);
	Vector3 vel = Vector3(0, 0, 0);
	Vector3 scale = Vector3(TILEWIDTH * 1.f, TILEHEIGHT*1.f, 1);
	while (!file.eof()) {
		char line[256];
		file.getline(line, 256);
		if (!file.eof())
			linesinreverse.push_back(line);
	}
	float xOffset = 0, yOffset = 0;
	GameObject* temp = nullptr;
	Entity* tempEntity = nullptr;
	bool isEntity = false;
	for (int row = linesinreverse.size() - 1; row >= 0; row--)
	{
		for (int col = 0; col < 256; col++)
		{
			scale = Vector3(TILEWIDTH, TILEHEIGHT, 1);
			vel = Vector3(0, 0, 0);
			
			temp = nullptr;
			tempEntity = nullptr;
			isEntity = false;
			switch (linesinreverse[row][col])
			{
			case ',':
				commacounter++;
				continue;
			case '0':
				xOffset += TILEWIDTH;
				if (col - commacounter > highestcol)
					highestcol = col;
				map.push_back(temp);
				continue;
			case '1': // brick 
				pos.Set(xOffset + scale.x / 2, yOffset + scale.y / 2 , 0);
				temp = TileFactory::getObject(TileFactory::TILE_LIST::BRICK,pos,vel,scale);
				break;
			case '2': // stone brick
				pos.Set(xOffset + scale.x / 2, yOffset + scale.y / 2 , 0);
				temp = TileFactory::getObject(TileFactory::TILE_LIST::STONEBRICK,pos,vel,scale);
				break;
			case '3': // spike 
				pos.Set(xOffset  + scale.x / 2, yOffset + scale.y / 2, 0);
				temp = TileFactory::getObject(TileFactory::TILE_LIST::SPIKE, pos, vel, scale);
				break;
			case '4': // zombie
				pos.Set(xOffset + scale.x / 2, yOffset + scale.y / 2, 0);
				tempEntity = PrototypeFactory::getObject(PrototypeFactory::ZOMBIE,pos,vel,scale);
				temp = tempEntity;
				isEntity = true;
				break;
			case '5': // Skeleton Archer
				pos.Set(xOffset + scale.x / 2, yOffset + scale.y / 2, 0);
				tempEntity = PrototypeFactory::getObject(PrototypeFactory::SKELE_ARCHER, pos, vel, scale);
				temp = tempEntity;
				isEntity = true;
				break;
			case '6': // Spider
				pos.Set(xOffset + scale.x / 2, yOffset + scale.y / 2, 0);
				tempEntity = PrototypeFactory::getObject(PrototypeFactory::SPIDER, pos, vel, scale);
				temp = tempEntity;
				isEntity = true;
				break;
			case '7': // Nymph
				pos.Set(xOffset + scale.x / 2, yOffset + scale.y / 2, 0);
				tempEntity = PrototypeFactory::getObject(PrototypeFactory::NYMPH, pos, vel, scale);
				temp = tempEntity;
				isEntity = true;
				break;
			case '8': // Turret
				pos.Set(xOffset + scale.x / 2, yOffset + scale.y / 2, 0);
				tempEntity = PrototypeFactory::getObject(PrototypeFactory::TURRET, pos, vel, scale);
				temp = tempEntity;
				isEntity = true;
				break;
			case '9': // Boomer
				pos.Set(xOffset + scale.x / 2, yOffset + scale.y / 2, 0);
				tempEntity = PrototypeFactory::getObject(PrototypeFactory::BOOMER, pos, vel, scale);
				temp = tempEntity;
				isEntity = true;
				break;
			case '10': // Demon Lord
				pos.Set(xOffset + scale.x / 2, yOffset + scale.y / 2, 0);
				tempEntity = PrototypeFactory::getObject(PrototypeFactory::DEMON_LORD, pos, vel, scale);
				temp = tempEntity;
				isEntity = true;
				break;
				
			case 'P':
				player->GetInstance();
				player->pos.Set((col - commacounter) * TILEWIDTH + (TILEWIDTH / 2.f), ((linesinreverse.size() -row) * TILEHEIGHT - (TILEHEIGHT / 2.f)), 0.1f);
				player->vel.SetZero();
				xOffset += TILEWIDTH;
				map.push_back(temp);
				continue;
			}
			xOffset += TILEWIDTH;
			if ((col-commacounter) > highestcol)
				highestcol = col - commacounter;
			if (temp != nullptr)
			{
				map.push_back(temp);
			}
			else if (isEntity == true)
			{
				map.push_back(nullptr);
				EntityList.push_back(tempEntity);
			}	
			else
				break;
		}
		xOffset = 0;
		yOffset += TILEHEIGHT;
		commacounter = 0;
	}
	m_worldWidth = (highestcol * TILEWIDTH);
	m_worldHeight = (linesinreverse.size())*TILEHEIGHT;
	return true;
}

float GameLevelBase::getworldWidth()
{
	return m_worldWidth;
}

float GameLevelBase::getworldHeight()
{
	return m_worldHeight;
}

float GameLevelBase::getTileWidth()
{
	return TILEWIDTH;
}

float GameLevelBase::getTileHeight()
{
	return TILEHEIGHT;
}

std::vector<Projectile*>* GameLevelBase::getProjectileList()
{
	return &projectileList;
}
