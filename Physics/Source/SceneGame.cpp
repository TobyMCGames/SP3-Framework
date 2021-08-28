#include "SceneGame.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>
#include "GLFW/glfw3.h"

#include "GameStateManager.h"
#include "GameLevelManager.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "LevelFinal.h"

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
	
	GameLevelManager::GetInstance()->AddGameLevel("Level1", Level1::GetInstance());
	GameLevelManager::GetInstance()->AddGameLevel("Level2", Level2::GetInstance());
	GameLevelManager::GetInstance()->AddGameLevel("Level3", Level3::GetInstance());
	GameLevelManager::GetInstance()->AddGameLevel("Level4", Level4::GetInstance());
	GameLevelManager::GetInstance()->AddGameLevel("LevelFinal", LevelFinal::GetInstance());
	// Set Active Game Level
	GameLevelManager::GetInstance()->SetActiveGameLevel("LevelFinal");

	Application::changeCursor(true);
	ispaused = false;
}

bool SceneGame::Update(double dt)
{
	static bool bLButtonState = false;
	if (!bLButtonState && (cKeyboardController->IsKeyPressed(GLFW_KEY_P) || cKeyboardController->IsKeyPressed(GLFW_KEY_ESCAPE)) 
		&& !Player::GetInstance()->isdead)
	{
		bLButtonState = true;
		if (ispaused == false)
		{
			CSoundController::GetInstance()->PlaySoundByID(22);
		}
	}
	else if (bLButtonState && (!cKeyboardController->IsKeyPressed(GLFW_KEY_P) && !cKeyboardController->IsKeyPressed(GLFW_KEY_ESCAPE)) 
		&& !Player::GetInstance()->isdead)
	{
		bLButtonState = false;
		SceneGUI::GetInstance()->setRenderPause(true);
		ispaused = true;
	}

	if (Player::GetInstance()->isdead)
	{
		SceneGUI::GetInstance()->setRenderRetry(true);
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
	Player::GetInstance()->Reset();
	Player::DestroyInstance();
}

void SceneGame::setisPaused(bool ispaused)
{
	this->ispaused = ispaused;
}

bool SceneGame::getisPaused()
{
	return ispaused;
}
