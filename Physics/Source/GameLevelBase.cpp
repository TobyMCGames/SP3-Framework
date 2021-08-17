#include "GameLevelBase.h"
#include <fstream>
#include "Application.h"

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
	while (!file.eof()) {
		char line[256];
		file.getline(line, 256);
		if (!file.eof())
			linesinreverse.push_back(line);
	}
	float xOffset = 0, yOffset = 0;
	GameObject* temp = nullptr;
	for (int row = linesinreverse.size() - 1; row >= 0; row--)
	{
		for (unsigned int col = 0; col < 256; col++)
		{
			
			temp = nullptr;
			switch (linesinreverse[row][col])
			{
			case ',':
				commacounter++;
				continue;
			case '0':
				xOffset += TILEWIDTH;
				if (col - commacounter > highestcol)
					highestcol = col;
				continue;
			case '1':
				temp = new passive_tile(GameObject::GAMEOBJECT_TYPE::STONE_BRICK_TILE);
				temp->active = true;
				temp->pos.Set(xOffset + temp->scale.x / 2 * TILEWIDTH - (TILEWIDTH/2.f), yOffset + temp->scale.y / 2 * TILEHEIGHT + (TILEHEIGHT/2.f), 0);
				temp->vel.Set(0, 0, 0);
				temp->scale.Set(TILEWIDTH, TILEHEIGHT, 1);
				xOffset += TILEWIDTH;
				break;
			case '2':
				temp = new passive_tile(GameObject::GAMEOBJECT_TYPE::BRICK_TILE);
				temp->active = true;
				temp->pos.Set(xOffset + temp->scale.x / 2 * TILEWIDTH, yOffset + temp->scale.y / 2 * TILEHEIGHT, 0);
				temp->vel.Set(0, 0, 0);
				temp->scale.Set(TILEWIDTH, TILEHEIGHT, 1);
				xOffset += TILEWIDTH;
				break;
			case 'P':
				player->GetInstance();
				player->pos.Set((col - commacounter) * TILEWIDTH, ((linesinreverse.size() -row) * TILEHEIGHT), 0.1f);
				xOffset += TILEWIDTH;
				continue;
			}
			if ((col-commacounter) > highestcol)
				highestcol = col - commacounter;
			if (temp != nullptr)
				map.push_back(temp);
			else
				break;
		}
		xOffset = 0;
		yOffset += TILEHEIGHT;
		commacounter = 0;
	}
	m_worldWidth = highestcol * TILEWIDTH;
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
