#pragma once
#include "SingletonPattern.h"
#include <map>
#include <string>
#include "SceneBase.h"
#include "SoundController.h"
using namespace std;

class GameStateManager : public SingletonPattern<GameStateManager>
{
	friend SingletonPattern<GameStateManager>;
protected:
	GameStateManager();
	~GameStateManager();
	map< string, SceneBase*> GameStateMap;

	SceneBase* ActiveGameState;
	SceneBase* NextGameState;
	CSoundController* cSoundController;

public:
	// Destroy this CGameStateManager
	void Destroy();

	// System Interface
	// Update this class instance
	bool Update(const double dt);
	// Render this class instance
	void Render(void);

	// User Interface
	bool AddGameState(const std::string& _name, SceneBase* _scene);
	bool RemoveGameState(const std::string& _name);
	bool SetActiveGameState(const std::string& _name);
	bool CheckGameStateExist(const std::string& _name);
};

