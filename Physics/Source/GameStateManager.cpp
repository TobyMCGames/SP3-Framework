#include "GameStateManager.h"

GameStateManager::GameStateManager()
	: ActiveGameState(nullptr)
	, NextGameState(nullptr)
	, cSoundController(NULL)
{
	//Sounds
	cSoundController = CSoundController::GetInstance();
	cSoundController->Init();

	//Projectile sounds
	cSoundController->LoadSound("Sounds\\Sounds_Projectiles\\Arrow.wav", 1, true);
	cSoundController->LoadSound("Sounds\\Sounds_Projectiles\\Magic_Ball.wav", 2, true);
	cSoundController->LoadSound("Sounds\\Sounds_Projectiles\\Portal_2.wav", 3, true);

	//player sounds
	cSoundController->LoadSound("Sounds\\Sounds_Player\\Jump.ogg", 4, true);
	cSoundController->LoadSound("Sounds\\Sounds_Player\\Hurt.wav", 5, true);
	cSoundController->LoadSound("Sounds\\Sounds_Player\\Hurt_2.wav", 6, true);
	cSoundController->LoadSound("Sounds\\Sounds_Player\\Hurt_3.wav", 7, true);

	//zombie sounds
	cSoundController->LoadSound("Sounds\\Sounds_Zombie\\Zombie_Idle.wav", 8, true);
	cSoundController->LoadSound("Sounds\\Sounds_Zombie\\Zombie_Attack.wav", 9, true);
	cSoundController->LoadSound("Sounds\\Sounds_Zombie\\Zombie_Attack_2.wav", 10, true);
	cSoundController->LoadSound("Sounds\\Sounds_Zombie\\Zombie_Hurt.wav", 11, true);
	cSoundController->LoadSound("Sounds\\Sounds_Zombie\\Zombie_Hurt_2.wav", 12, true);
	cSoundController->LoadSound("Sounds\\Sounds_Zombie\\Zombie_Death.wav", 13, true);

	//turret Sounds
	cSoundController->LoadSound("Sounds\\Sounds_Turret\\Turret_Shoot.wav", 14, true);
	cSoundController->LoadSound("Sounds\\Sounds_Turret\\Turret_Hurt_2.wav", 15, true);
	cSoundController->LoadSound("Sounds\\Sounds_Turret\\Turret_Death.wav", 18, true);
}

GameStateManager::~GameStateManager()
{
}

void GameStateManager::Destroy()
{
	// Set the handlers to CGameState to nullptr
	ActiveGameState = nullptr;
	NextGameState = nullptr;

	// Delete all scenes stored and empty the entire map
	std::map<std::string, SceneBase*>::iterator it, end;
	end = GameStateMap.end();
	for (it = GameStateMap.begin(); it != end; ++it)
	{
		delete it->second;
	}
	// Clear the map
	GameStateMap.clear();
	cSoundController->DestroyInstance();
}

bool GameStateManager::Update(const double dt)
{
	// Check for change of scene
	if (NextGameState != ActiveGameState)
	{
		if (ActiveGameState)
		{
			// Scene is valid, need to call appropriate function to exit
			ActiveGameState->Exit();
		}
		//
		// Set the new active CGameState
		ActiveGameState = NextGameState;
		// Init the new active CGameState
		ActiveGameState->Init();
	}

	// Update the active CGameState
	if (ActiveGameState)
	{
		if (ActiveGameState->Update(dt) == false)
			return false;
	}

	return true;
}

void GameStateManager::Render(void)
{
	if (ActiveGameState)
		ActiveGameState->Render();
}

bool GameStateManager::AddGameState(const std::string& _name, SceneBase* _scene)
{
	// Check if this _name already exists in the map...
	if (CheckGameStateExist(_name))
	{
		// If it does not exist, then unable to proceed
		cout << "GameStateManager::AddGameState - Duplicate scene name provided" << endl;
		return false;
	}

	// Check if the _scene is valid
	if (_scene == nullptr)
	{
		cout << "GameStateManager::AddGameState - Invalid scene pointer" << endl;
		return false;
	}

	// If nothing is wrong, then add the scene to our map
	GameStateMap[_name] = _scene;
	cout << "GameState " << _name << " was added" << endl;

	return true;
}

bool GameStateManager::RemoveGameState(const std::string& _name)
{
	// Check if this _name does not exists in the map...
	if (!CheckGameStateExist(_name))
	{
		// If it does not exist, then unable to proceed
		cout << "GameStateManager::RemoveGameState - scene name does not exists" << endl;
		return false;
	}

	// Find the CGameState*
	SceneBase* target = GameStateMap[_name];
	if (target == ActiveGameState || target == NextGameState)
	{
		cout << "Unable to remove active/next scene" << endl;
		return false;
	}

	// Delete and remove from our map
	delete target;
	GameStateMap.erase(_name);

	return true;
}

bool GameStateManager::SetActiveGameState(const std::string& _name)
{
	// Check if this _name does not exists in the map...
	if (!CheckGameStateExist(_name))
	{
		// If it does not exist, then unable to proceed
		cout << "GameStateManager::SetActiveGameState - scene name does not exists" << endl;
		return false;
	}

	// Scene exist, set the next scene pointer to that scene
	NextGameState = GameStateMap[_name];

	return true;
}

bool GameStateManager::CheckGameStateExist(const std::string& _name)
{
	return GameStateMap.count(_name) != 0;
}
