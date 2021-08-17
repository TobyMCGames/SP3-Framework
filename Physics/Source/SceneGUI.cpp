#include "SceneGUI.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>

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

}
void SceneGUI::Update(double dt)
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
	PlayButton.Set(1, 1, 1);
	if (posX > 37 && posX < 48 && posY > -49 && posY < -44)
	{
		PlayButton.Set(1, 0, 0);
		//Mouse Section
		static bool bLButtonState = false;
		if(!bLButtonState && Application::IsMousePressed(0))
		{
			bLButtonState = true;
		}
		else if(bLButtonState && !Application::IsMousePressed(0))
		{
			bLButtonState = false;
			GameStateManager::GetInstance()->SetActiveGameState("PlayGameState");
		}
	}
	
}

void SceneGUI::Render()
{

	// Projection matrix : Orthographic Projection
	Mtx44 projection;
	projection.SetToOrtho(0, m_worldWidth, 0, m_worldHeight, -10, 10);
	projectionStack.LoadMatrix(projection);
	
	// Camera matrix
	viewStack.LoadIdentity();
	viewStack.LookAt(
						camera.position.x, camera.position.y, camera.position.z,
						camera.target.x, camera.target.y, camera.target.z,
						camera.up.x, camera.up.y, camera.up.z
					);
	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();

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
	RenderMeshOnScreen(meshList[GUI_HEART],40,57.5,3,3);
	// render health bar
	RenderMeshOnScreen(meshList[GUI_HEALTHBAR], 40,54.5,10,2); //the x value can be replaced by the player's health /10

	
	//ss << 10;
	//RenderTextOnScreen(meshList[GEO_TEXT], ss.str() , Color(1, 1, 1),4,38.5,50.5);

	// render the energy Icon
	RenderMeshOnScreen(meshList[GUI_ENERGY], 57.5,56.5,3,3);
	// render the energy bar 
	RenderMeshOnScreen(meshList[GUI_ENERGYBAR],57.5,53.5,7.5,2);//the x value can be replaced by the player's health /20

	// render the backgroudn for the stats gui
	RenderMeshOnScreen(meshList[GUI_STATS_BG],39.75,52.5,85,15); 

	// render Attack 
	RenderMeshOnScreen(meshList[GUI_ATK_ICON], 39.5, 50, 3, 3);
	//render attack value
	ss << 5; // player's attack value
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(1, 1, 1), 3,41.5,48.5);
}