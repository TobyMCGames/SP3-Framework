#include "SceneGame.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>
#include "GLFW/glfw3.h"

#include "GameStateManager.h"
#include "GameLevelManager.h"
#include "SceneCollision.h"
#include "Level3.h"

#include "SceneGUI.h"
SceneGame::SceneGame()
	: ispaused(false)
{
}

SceneGame::~SceneGame()
{
	
}

void SceneGame::Init()
{
	// Init keyboard
	cKeyboardController = CKeyboardController::GetInstance();

	// Init GUI
	SceneGUI::GetInstance()->Init();

	// Create game Levels
	//GameLevelManager::GetInstance()->AddGameLevel("Level1A", SceneCollision::GetInstance());
	
	GameLevelManager::GetInstance()->AddGameLevel("Level3", Level3::GetInstance());
	GameLevelManager::GetInstance()->AddGameLevel("Level4", SceneCollision::GetInstance());
	// Set Active Game Level
	GameLevelManager::GetInstance()->SetActiveGameLevel("Level4");

	Application::changeCursor(true);
	ispaused = false;
}



bool SceneGame::Update(double dt)
{
	static bool bLButtonState = false;
	if (!bLButtonState && (cKeyboardController->IsKeyPressed(GLFW_KEY_P) || cKeyboardController->IsKeyPressed(GLFW_KEY_ESCAPE)))
	{
		bLButtonState = true;
		if (ispaused == false)
		{
			CSoundController::GetInstance()->PlaySoundByID(22);
		}
	}
	else if (bLButtonState && (!cKeyboardController->IsKeyPressed(GLFW_KEY_P) && !cKeyboardController->IsKeyPressed(GLFW_KEY_ESCAPE)))
	{
		bLButtonState = false;
		SceneGUI::GetInstance()->RenderPause = true;
		ispaused = true;
	}


	if (!ispaused)
		if (GameLevelManager::GetInstance()->Update(dt) == false)
			return false;

	if (SceneGUI::GetInstance()->Update(dt) == false)
		return false;

	return true;
}


void SceneGame::Render()
{
	GameLevelManager::GetInstance()->Render();
	SceneGUI::GetInstance()->Render();
}

void SceneGame::Destroy()
{
	DestroyInstance();
}

void SceneGame::Exit()
{

	GameLevelManager::GetInstance()->Destroy();
	GameLevelManager::DestroyInstance();
	SceneGUI::GetInstance()->Exit();
	SceneGUI::GetInstance()->Destroy();
}
