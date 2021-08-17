#pragma once
#include "SingletonPattern.h"
#include <map>
#include <string>
#include "GameLevelBase.h"
using namespace std;

class GameLevelManager : public SingletonPattern<GameLevelManager>
{
	friend SingletonPattern<GameLevelManager>;
protected:
	GameLevelManager();
	~GameLevelManager();

	map< string, GameLevelBase*> GameLevelMap;

	GameLevelBase* ActiveGameLevel;
	GameLevelBase* NextGameLevel;

public:
	// Destroy this CGameLevelManager
	void Destroy();

	// System Interface
	// Update this class instance
	bool Update(const double dt);
	// Render this class instance
	void Render(void);

	// User Interface
	bool AddGameLevel(const std::string& _name, GameLevelBase* _scene);
	bool RemoveGameLevel(const std::string& _name);
	bool SetActiveGameLevel(const std::string& _name);
	bool CheckGameLevelExist(const std::string& _name);
};

