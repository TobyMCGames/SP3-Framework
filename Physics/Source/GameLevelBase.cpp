#include "GameLevelBase.h"
#include <fstream>

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
	int linescounter = 0;
	while (!file.eof()) {
		char line[256];
		file.getline(line, 256);
		linesinreverse.push_back(line);
	}
	float xOffset = 0, yOffset = 0;
	GameObject* temp = nullptr;
	for (int row = linesinreverse.size() - 2; row >= 0; row--)
	{
		for (unsigned int col = 0; col < 256; col++)
		{
			temp = nullptr;
			switch (linesinreverse[row][col])
			{
			case ',':
				continue;
			case '0':
				xOffset += TILEWIDTH;
				continue;
			}
			if (temp != nullptr)
				map.push_back(temp);
			else
				break;
		}
		xOffset = 0;
		yOffset += TILEHEIGHT;
	}
	return true;
}
