#include "SceneGUI.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>
#include "GLFW/glfw3.h"
#include "GameStateManager.h"
SceneGUI::SceneGUI()
	: m_worldHeight(0)
	, m_worldWidth(0)
	, Timetravel(NULL)
{
	GameDialogues.LoadDialogue("Dialogues//Level_3_dialogues.txt"); // load level 4 texts
	GameDialogues.LoadDialogue("Dialogues//Level_4_dialogues.txt"); // load level 4 texts
	GameDialogues.setActive(false);
}

SceneGUI::~SceneGUI()
{
	
}
void SceneGUI::Init()
{
	SceneBase::Init();
	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	Math::InitRNG();
	RenderPause = false;
	RenderRetry = false;
	StartTimer = false;

	camera->Init(Vector3(0, 0, 5), Vector3(0, 0, 0), Vector3(0, 1, 0), 0, 0,m_worldWidth,m_worldHeight);

	Timetravel = new SpriteAnimation(CentralMesh::GetInstance()->GetMeshID(CentralMesh::GEO_TIMETRAVEL));
	Timetravel->AddAnimation("travel", 0, 11);
	Timetravel->PlayAnimation("travel", 1, 0.3f);
}
bool SceneGUI::Update(double dt)
{
	SceneBase::Update(dt);

	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	
	double x, y;
	Application::GetCursorPos(&x, &y);
	unsigned w = Application::GetWindowWidth();
	unsigned h = Application::GetWindowHeight();
	float posX = x / w * 80; //convert (0,800) to (0,80)
	float posY = 1 - (y / h) * 60; //convert (600,0) to (0,60)
	ContButton.Set(1, 1, 1);
	RetryButton.Set(1, 1, 1);
	MenuButton.Set(1, 1, 1);
	QuitButton.Set(1, 1, 1);

	static bool MouseState = false;
	if (!MouseState && Application::IsMousePressed(0))
	{
		MouseState = true;
	}
	else if (MouseState && !Application::IsMousePressed(0))
	{
		MouseState = false;
		cout << "X: " << posX << ", " << "Y: " << posY << endl;
	}

	//pause menu select
	if (RenderPause)
	{
		Application::changeCursor(false);
		if (posX > 25 && posX < 40 && posY > -28 && posY < -25)
		{
			ContButton.Set(1, 0, 0);
			static bool MouseState = false;
			if (!MouseState && Application::IsMousePressed(0))
			{
				CSoundController::GetInstance()->PlaySoundByID(21);
				MouseState = true;
			}
			else if (MouseState && !Application::IsMousePressed(0))
			{
				MouseState = false;
				SceneGame::GetInstance()->setisPaused(false);
				RenderPause = false;
				Application::changeCursor(true);
			}
		}
		if (posX > 25 && posX < 50 && posY > -33 && posY < -30)
		{
			MenuButton.Set(1, 0, 0);
			static bool MouseState = false;
			if (!MouseState && Application::IsMousePressed(0))
			{
				MouseState = true;
			}
			else if (MouseState && !Application::IsMousePressed(0))
			{
				MouseState = false;
				GameStateManager::GetInstance()->SetActiveGameState("IntroState");
			}
		}
		if (posX > 25 && posX < 40 && posY > -38 && posY < -35)
		{
			QuitButton.Set(1, 0, 0);
			static bool MouseState = false;
			if (!MouseState && Application::IsMousePressed(0))
			{
				MouseState = true;
			}
			else if (MouseState && !Application::IsMousePressed(0))
			{
				MouseState = false;
				return false;
			}
		}

		static bool bLButtonState = false;
		if (!bLButtonState && (cKeyboardController->IsKeyPressed(GLFW_KEY_P) || cKeyboardController->IsKeyPressed(GLFW_KEY_ESCAPE))
			&& SceneGame::GetInstance()->getisPaused() == true)
		{
			bLButtonState = true;
			CSoundController::GetInstance()->PlaySoundByID(21);
		}
		else if (bLButtonState && (!cKeyboardController->IsKeyPressed(GLFW_KEY_P) && !cKeyboardController->IsKeyPressed(GLFW_KEY_ESCAPE))
			&& SceneGame::GetInstance()->getisPaused() == true)
		{
			SceneGame::GetInstance()->setisPaused(false);
			bLButtonState = false;
			RenderPause = false;
		}

		
	}
	//retry menu select
	if (RenderRetry)
	{
		Application::changeCursor(false);
		if (posX > 25 && posX < 40 && posY > -28 && posY < -25)
		{
			RetryButton.Set(1, 0, 0);
			static bool MouseState = false;
			if (!MouseState && Application::IsMousePressed(0))
			{
				MouseState = true;
			}
			else if (MouseState && !Application::IsMousePressed(0))
			{
				MouseState = false;
				SceneGame::GetInstance()->setisPaused(false);
				RenderRetry = false;
				GameLevelManager::GetInstance()->getcurrentLevel()->Exit();
				Player::GetInstance()->Reset();
				GameLevelManager::GetInstance()->getcurrentLevel()->Init();
				Application::changeCursor(true);
			}
		}
		if (posX > 25 && posX < 50 && posY > -33 && posY < -30)
		{
			MenuButton.Set(1, 0, 0);
			static bool MouseState = false;
			if (!MouseState && Application::IsMousePressed(0))
			{
				MouseState = true;
			}
			else if (MouseState && !Application::IsMousePressed(0))
			{
				MouseState = false;
				GameStateManager::GetInstance()->SetActiveGameState("IntroState");
			}
		}
		if (posX > 25 && posX < 40 && posY > -38 && posY < -35)
		{
			QuitButton.Set(1, 0, 0);
			static bool MouseState = false;
			if (!MouseState && Application::IsMousePressed(0))
			{
				MouseState = true;
			}
			else if (MouseState && !Application::IsMousePressed(0))
			{
				MouseState = false;
				return false;
			}
		}
	}
	// if in dialogue
		//GameDialogues.Update(dt);

	if (Timetravel != NULL)
	{
		if (Player::GetInstance()->timetraveled > 0)
 			Timetravel->Update(dt);
	}
	if (Player::GetInstance()->IsInDialogue() == true)
	{
		if (GameDialogues.getcurrentSceneConvo()== 0)
		{
			GameDialogues.playDialogue(Player::GetInstance()->getDialoginProgress());
			GameDialogues.setActive(true);
		}
		else
		{
			GameDialogues.Update(dt);
			if (GameDialogues.getEndConvo() == true)
			{
				GameDialogues.setEndConvo(false);
				Player::GetInstance()->setInDialogue(false);
				GameDialogues.setcurrentSceneConvo(0);
				SceneGame::GetInstance()->setisPaused(false);
			}
		}
			
	}
	return true;
}

void SceneGUI::Render()
{

	// Projection matrix : Orthographic Projection
	Mtx44 projection;
	projection.SetToOrtho(0, m_worldWidth, 0, m_worldHeight, -10, 10);
	projectionStack->LoadMatrix(projection);
	
	// Camera matrix
	viewStack->LoadIdentity();
	viewStack->LookAt(
						camera->getPosition().x, camera->getPosition().y, camera->getPosition().z,
						camera->getTarget().x, camera->getTarget().y, camera->getTarget().z,
						camera->getUp().x, camera->getUp().y, camera->getUp().z
					);
	// Model matrix : an identity matrix (model will be at the origin)
	modelStack->LoadIdentity();

	renderGUI();
}

void SceneGUI::Destroy()
{
	DestroyInstance();
}

void SceneGUI::Exit()
{
	SceneBase::Exit();
}

void SceneGUI::renderGUI()
{
	std::ostringstream ss;
	std::ostringstream coins;
	// render health icon
	meshRender->RenderMeshOnScreen(centralMesh->GetMeshID(CentralMesh::GUI_HEART),3,57,3,3);

	// render health bar
	int health = Player::GetInstance()->gethealth();
	meshRender->RenderMeshOnScreen(centralMesh->GetMeshID(CentralMesh::GUI_HEALTHBAR), 10.f - ((100.f - health)*0.05f) ,57, ((health*10.f)/100.f) ,2); //the x value can be replaced by the player's health /10
	
	
	//ss << 10;
	//RenderTextOnScreen(meshList[GEO_TEXT], ss.str() , Color(1, 1, 1),4,38.5,50.5);

	// render the energy Icon
	meshRender->RenderMeshOnScreen(centralMesh->GetMeshID(CentralMesh::GUI_ENERGY), 3,53,3,3);
	float Mana = Player::GetInstance()->getmana();
	// render the energy bar 
	meshRender->RenderMeshOnScreen(centralMesh->GetMeshID(CentralMesh::GUI_ENERGYBAR),8.8f - ((100.f - Mana) * 3.8f/99.f),53,((Mana*7.5f)/100.f),2);//the x value can be replaced by the player's health /20

	//render coins icon
	meshRender->RenderMeshOnScreen(centralMesh->GetMeshID(CentralMesh::GEO_COIN), 3, 49, 4, 4);
	coins << Player::GetInstance()->getCoins();
	meshRender->RenderTextOnScreen(centralMesh->GetMeshID(CentralMesh::GEO_TEXT), coins.str(), Color(1, 1, 1), 3, 5, 47.55);

	// render the backgroudn for the stats gui
	//RenderMeshOnScreen(meshList[GUI_STATS_BG],39.75,52.5,85,15); 

	//render border for item
	meshRender->RenderMeshOnScreen(centralMesh->GetMeshID(CentralMesh::GUI_BORDER), 6, 6, 9.5,10);
	switch (Player::GetInstance()->GetCurItem())
	{
	case PlayerBase::TREE_SEED:
		meshRender->RenderMeshOnScreen(centralMesh->GetMeshID(CentralMesh::GEO_TREE_SEEDS), 6, 7, 7, 7);
		break;
	case PlayerBase::VINE_SEED:
		meshRender->RenderMeshOnScreen(centralMesh->GetMeshID(CentralMesh::GEO_VINE_SEEDS), 6, 7, 7, 7);
		break;
	case PlayerBase::BOMBS:
		meshRender->RenderMeshOnScreen(centralMesh->GetMeshID(CentralMesh::GEO_BOMB_CRATE), 6, 7, 7, 7);
		break;
	case PlayerBase::LOCK_KEY:
		meshRender->RenderMeshOnScreen(centralMesh->GetMeshID(CentralMesh::GEO_KEY), 6, 7, 7, 7);
		break;
	case PlayerBase::WEAPON:
		switch (Player::GetInstance()->getcurWeapon())
		{
		case Player::BOW:
			meshRender->RenderMeshOnScreen(centralMesh->GetMeshID(CentralMesh::GEO_BOW), 6, 7, 7, 7);
			break;
		case Player::STAFF:
			meshRender->RenderMeshOnScreen(centralMesh->GetMeshID(CentralMesh::GEO_STAFF), 6, 7, 7, 7);
			break;
		case Player::PORTALGUN:
			meshRender->RenderMeshOnScreen(centralMesh->GetMeshID(CentralMesh::GEO_PORTALGUN), 6, 7, 7, 7);
			break;
		}
		break;
	}
	ss << Player::GetInstance()->GetCurItemAmt();
	meshRender->RenderTextOnScreen(centralMesh->GetMeshID(CentralMesh::GEO_TEXT), ss.str(), Color(1,1,1), 4, 7.5, 6);

	if (Timetravel != NULL)
	{
		if (Player::GetInstance()->timetraveled > 0)
		{
			MeshRender::GetInstance()->RenderAnimationOnScreen(
				Timetravel->GetSprite(),
				Timetravel->GetCurFrame(),
				6,
				40,
				30,
				85,
				65
			);
		}
		else
			Timetravel->Reset();
	}

	if (Player::GetInstance()->IsInDialogue() == true)
	{
		SceneGame::GetInstance()->setisPaused(true);
		meshRender->RenderMeshOnScreen(centralMesh->GetMeshID(CentralMesh::TEXT_BOX), 40, 10, 40, 20);
		renderDialogue();
	}

	if (RenderPause)
	{
		meshRender->RenderMeshOnScreen(centralMesh->GetMeshID(CentralMesh::GUI_PAUSE), 40, 30, 80, 70);
		meshRender->RenderTextOnScreen(centralMesh->GetMeshID(CentralMesh::GEO_TEXT), "RESUME", ContButton, 3, 29, 30);
		meshRender->RenderTextOnScreen(centralMesh->GetMeshID(CentralMesh::GEO_TEXT), "MAIN MENU", MenuButton, 3, 29, 25);
		meshRender->RenderTextOnScreen(centralMesh->GetMeshID(CentralMesh::GEO_TEXT), "QUIT", QuitButton, 3, 29, 20);
	}
	if (RenderRetry)
	{
		meshRender->RenderMeshOnScreen(centralMesh->GetMeshID(CentralMesh::GUI_RETRY), 40, 30, 80, 70);
		meshRender->RenderTextOnScreen(centralMesh->GetMeshID(CentralMesh::GEO_TEXT), "RETRY", RetryButton, 3, 29, 30);
		meshRender->RenderTextOnScreen(centralMesh->GetMeshID(CentralMesh::GEO_TEXT), "MAIN MENU", MenuButton, 3, 29, 25);
		meshRender->RenderTextOnScreen(centralMesh->GetMeshID(CentralMesh::GEO_TEXT), "QUIT", QuitButton, 3, 29, 20);
	}
}

bool SceneGUI::getRenderPause()
{
	return RenderPause;
}

void SceneGUI::setRenderPause(bool RenderPause)
{
	this->RenderPause = RenderPause;
}

bool SceneGUI::getRenderRetry()
{
	return RenderRetry;
}

void SceneGUI::setRenderRetry(bool RenderRetry)
{
	this->RenderRetry = RenderRetry;
}


void SceneGUI::renderDialogue()
{
	meshRender->RenderTextOnScreen(centralMesh->GetMeshID(CentralMesh::GEO_TEXT)
		, GameDialogues.getCurrentText(), Color(0, 1, 0),2.5,22,15,12.5);
}


