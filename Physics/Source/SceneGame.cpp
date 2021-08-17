#include "SceneGame.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>

#include "GameStateManager.h"
#include "GameLevelManager.h"
#include "SceneCollision.h"

#include "SceneGUI.h"
SceneGame::SceneGame()
{
}

SceneGame::~SceneGame()
{
}

void SceneGame::Init()
{
	// Init GUI
	SceneGUI::GetInstance()->Init();

	// Create game Levels
	GameLevelManager::GetInstance()->AddGameLevel("Level1A", SceneCollision::GetInstance());

	// Set Active Game Level
	GameLevelManager::GetInstance()->SetActiveGameLevel("Level1A");

	ispaused = false;
}



void SceneGame::Update(double dt)
{
	static bool bLButtonState = false;
	if (!bLButtonState && Application::IsKeyPressed('P'))
	{
		bLButtonState = true;
	}
	else if (bLButtonState && !Application::IsKeyPressed('P'))
	{
		bLButtonState = false;
		SceneGUI::GetInstance()->RenderPause = true;
		ispaused = true;
	}


	if(!ispaused)
		GameLevelManager::GetInstance()->Update(dt);

	SceneGUI::GetInstance()->Update(dt);
}


void SceneGame::Render()
{
	GameLevelManager::GetInstance()->Render();
	SceneGUI::GetInstance()->Render();
}

void SceneGame::Exit()
{

	GameLevelManager::GetInstance()->Destroy();
	GameLevelManager::DestroyInstance();
	SceneGUI::GetInstance()->Exit();
	SceneGUI::DestroyInstance();
}
