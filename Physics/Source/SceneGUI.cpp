#include "SceneGUI.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>
#include "GLFW/glfw3.h"

#include "GameStateManager.h"

SceneGUI::SceneGUI()
	: m_worldHeight(0)
	, m_worldWidth(0)
{
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

	if (RenderPause)
	{
		Application::changeCursor(false);
		if (posX > 25 && posX < 40 && posY > -28 && posY < -25)
		{
			ContButton.Set(1, 0, 0);
			static bool MouseState = false;
			if (!MouseState && Application::IsMousePressed(0))
			{
				MouseState = true;
			}
			else if (MouseState && !Application::IsMousePressed(0))
			{
				MouseState = false;
				SceneGame::GetInstance()->ispaused = false;
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
			&& SceneGame::GetInstance()->ispaused == true)
		{
			bLButtonState = true;
		}
		else if (bLButtonState && (!cKeyboardController->IsKeyPressed(GLFW_KEY_P) && !cKeyboardController->IsKeyPressed(GLFW_KEY_ESCAPE))
			&& SceneGame::GetInstance()->ispaused == true)
		{
			SceneGame::GetInstance()->ispaused = false;
			bLButtonState = false;
			RenderPause = false;
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

void SceneGUI::Exit()
{
	SceneBase::Exit();
}

void SceneGUI::renderGUI()
{
	std::ostringstream ss;
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

	// render the backgroudn for the stats gui
	//RenderMeshOnScreen(meshList[GUI_STATS_BG],39.75,52.5,85,15); 

	//render border for weapon
	meshRender->RenderMeshOnScreen(centralMesh->GetMeshID(CentralMesh::GUI_BORDER), 6, 6, 9.5,10);

	//// render Attack 
	//RenderMeshOnScreen(meshList[GUI_ATK_ICON], 39.5, 50, 3, 3);
	////render attack value
	//ss << 5; // player's attack value
	meshRender->RenderTextOnScreen(centralMesh->GetMeshID(CentralMesh::GEO_TEXT), ss.str(), Color(1, 1, 1), 3,41.5,48.5);

	if (RenderPause)
	{
		meshRender->RenderMeshOnScreen(centralMesh->GetMeshID(CentralMesh::GUI_PAUSE), 40, 30, 80, 70);
		meshRender->RenderTextOnScreen(centralMesh->GetMeshID(CentralMesh::GEO_TEXT), "RESUME", ContButton, 3, 29, 30);
		meshRender->RenderTextOnScreen(centralMesh->GetMeshID(CentralMesh::GEO_TEXT), "MAIN MENU", MenuButton, 3, 29, 25);
		meshRender->RenderTextOnScreen(centralMesh->GetMeshID(CentralMesh::GEO_TEXT), "QUIT", QuitButton, 3, 29, 20);
	}
}


