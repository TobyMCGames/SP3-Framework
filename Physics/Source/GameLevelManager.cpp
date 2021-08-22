#include "GameLevelManager.h"

GameLevelManager::GameLevelManager()
	: ActiveGameLevel(nullptr)
	, NextGameLevel(nullptr)
	, cSoundController(NULL)
{
	//Sounds
	cSoundController = CSoundController::GetInstance();
	cSoundController->Init();

	//Projectile sounds
	cSoundController->LoadSound(FileSystem::getPath("Sounds\\Sounds_Projectiles\\Arrow.wav"), 1, true);
	cSoundController->LoadSound(FileSystem::getPath("Sounds\\Sounds_Projectiles\\Magic_Ball.wav"), 2, true);
	cSoundController->LoadSound(FileSystem::getPath("Sounds\\Sounds_Projectiles\\Portal_2.wav"), 3, true);

	//player sounds
	cSoundController->LoadSound(FileSystem::getPath("Sounds\\Sounds_Player\\Jump.ogg"), 4, true);
	cSoundController->LoadSound(FileSystem::getPath("Sounds\\Sounds_Player\\Hurt.wav"), 5, true);  
	cSoundController->LoadSound(FileSystem::getPath("Sounds\\Sounds_Player\\Hurt_2.wav"), 6, true);
	cSoundController->LoadSound(FileSystem::getPath("Sounds\\Sounds_Player\\Hurt_3.wav"), 7, true);

	//zombie sounds
	cSoundController->LoadSound(FileSystem::getPath("Sounds\\Sounds_Zombie\\Zombie_Idle.wav"), 8, true);
	cSoundController->LoadSound(FileSystem::getPath("Sounds\\Sounds_Zombie\\Zombie_Attack.wav"), 9, true);
	cSoundController->LoadSound(FileSystem::getPath("Sounds\\Sounds_Zombie\\Zombie_Attack_2.wav"), 10, true);
	cSoundController->LoadSound(FileSystem::getPath("Sounds\\Sounds_Zombie\\Zombie_Hurt.wav"), 11, true);
	cSoundController->LoadSound(FileSystem::getPath("Sounds\\Sounds_Zombie\\Zombie_Hurt_2.wav"), 12, true);
	cSoundController->LoadSound(FileSystem::getPath("Sounds\\Sounds_Zombie\\Zombie_Death.wav"), 13, true);

	//turret Sounds
	cSoundController->LoadSound(FileSystem::getPath("Sounds\\Sounds_Turret\\Turret_Shoot.wav"), 14, true);
	cSoundController->LoadSound(FileSystem::getPath("Sounds\\Sounds_Turret\\Turret_Hurt_2.wav"), 15, true);
	cSoundController->LoadSound(FileSystem::getPath("Sounds\\Sounds_Turret\\Turret_Death.wav"), 18, true);
}

GameLevelManager::~GameLevelManager()
{
	cSoundController = NULL;
}

void GameLevelManager::Destroy()
{
	// Set the handlers to CGameLevel to nullptr
	ActiveGameLevel = nullptr;
	NextGameLevel = nullptr;

	// Delete all scenes stored and empty the entire map
	std::map<std::string, GameLevelBase*>::iterator it, end;
	end = GameLevelMap.end();
	for (it = GameLevelMap.begin(); it != end; ++it)
	{
		GameLevelBase* level = it->second;
		level->Exit();
	}
	// Clear the map
	GameLevelMap.clear();
}

bool GameLevelManager::Update(const double dt)
{
	// Check for change of scene
	if (NextGameLevel != ActiveGameLevel)
	{
		if (ActiveGameLevel)
		{
			// Scene is valid, need to call appropriate function to exit
			ActiveGameLevel->Exit();
		}
		//
		// Set the new active CGameLevel
		ActiveGameLevel = NextGameLevel;
		// Init the new active CGameLevel
		ActiveGameLevel->Init();
	}

	// Update the active CGameLevel
	if (ActiveGameLevel)
	{
		if (ActiveGameLevel->Update(dt) == false)
			return false;
	}

	return true;
}

void GameLevelManager::Render(void)
{
	if (ActiveGameLevel)
		ActiveGameLevel->Render();
}

bool GameLevelManager::AddGameLevel(const std::string& _name, GameLevelBase* _scene)
{
	// Check if this _name already exists in the map...
	if (CheckGameLevelExist(_name))
	{
		// If it does not exist, then unable to proceed
		cout << "GameLevelManager::AddGameLevel - Duplicate scene name provided" << endl;
		return false;
	}

	// Check if the _scene is valid
	if (_scene == nullptr)
	{
		cout << "GameLevelManager::AddGameLevel - Invalid scene pointer" << endl;
		return false;
	}

	// If nothing is wrong, then add the scene to our map
	GameLevelMap[_name] = _scene;
	cout << "GameLevel " << _name << " was added" << endl;

	return true;
}

bool GameLevelManager::RemoveGameLevel(const std::string& _name)
{
	// Check if this _name does not exists in the map...
	if (!CheckGameLevelExist(_name))
	{
		// If it does not exist, then unable to proceed
		cout << "GameLevelManager::RemoveGameLevel - scene name does not exists" << endl;
		return false;
	}

	// Find the CGameLevel*
	SceneBase* target = GameLevelMap[_name];
	if (target == ActiveGameLevel || target == NextGameLevel)
	{
		cout << "Unable to remove active/next scene" << endl;
		return false;
	}

	// Delete and remove from our map
	delete target;
	GameLevelMap.erase(_name);

	return true;
}

bool GameLevelManager::SetActiveGameLevel(const std::string& _name)
{
	// Check if this _name does not exists in the map...
	if (!CheckGameLevelExist(_name))
	{
		// If it does not exist, then unable to proceed
		cout << "GameLevelManager::SetActiveGameLevel - scene name does not exists" << endl;
		return false;
	}

	// Scene exist, set the next scene pointer to that scene
	NextGameLevel = GameLevelMap[_name];

	return true;
}

bool GameLevelManager::CheckGameLevelExist(const std::string& _name)
{
	return GameLevelMap.count(_name) != 0;
}

GameLevelBase* GameLevelManager::getcurrentLevel()
{
	return ActiveGameLevel;
}

