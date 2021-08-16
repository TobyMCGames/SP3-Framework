#include "SceneGame.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>

#include "GameStateManager.h"
#include "GameLevelManager.h"
#include "SceneCollision.h"

SceneGame::SceneGame()
{
}

SceneGame::~SceneGame()
{
}

void SceneGame::Init()
{
	// Create game Levels
	GameLevelManager::GetInstance()->AddGameLevel("Level1A", new SceneCollision);

	// Set Active Game Level
	GameLevelManager::GetInstance()->SetActiveGameLevel("Level1A");
}
void SceneGame::Update(double dt)
{
	GameLevelManager::GetInstance()->Update(dt);
	
}

void SceneGame::Render()
{
	GameLevelManager::GetInstance()->Render();
}

void SceneGame::Exit()
{
	SceneBase::Exit();
	GameLevelManager::GetInstance()->Destroy();
}
