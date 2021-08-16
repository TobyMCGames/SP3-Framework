#include "SceneHTP.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>

#include "GameStateManager.h"

SceneHTP::SceneHTP()
{
}

SceneHTP::~SceneHTP()
{
}

void SceneHTP::Init()
{
	SceneBase::Init();
	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	BackButton.Set(1, 1, 1);

	Math::InitRNG();

}
void SceneHTP::Update(double dt)
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
	BackButton.Set(1, 1, 1);
	if (posX > 37 && posX < 48 && posY > -49 && posY < -44)
	{
		BackButton.Set(1, 0, 0);
		//Mouse Section
		static bool bLButtonState = false;
		if(!bLButtonState && Application::IsMousePressed(0))
		{
			bLButtonState = true;
		}
		else if(bLButtonState && !Application::IsMousePressed(0))
		{
			bLButtonState = false;
			GameStateManager::GetInstance()->SetActiveGameState("IntroState");
		}
	}
	
}

void SceneHTP::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
	
	RenderMesh(meshList[GEO_AXES], false);
	////////////// Background Image  /////////////////////
	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidth/2, m_worldHeight/2, -1);
	modelStack.Scale(88, 55, 55);
	RenderMesh(meshList[GEO_BACKGROUND], false);
	modelStack.PopMatrix();

	////Title Logo
	//modelStack.PushMatrix();
	//{
	//	modelStack.Translate(m_worldWidth / 2 +3, m_worldHeight / 10 * 7, 0);
	//	modelStack.Scale(60, 60, 60);
	//	RenderMesh(meshList[GEO_TITLE], false);
	//}
	//modelStack.PopMatrix();

	//On screen text
	std::ostringstream ss;
	ss.str("");
	ss << "back";
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), BackButton, 4, 39.5, 10);
}

void SceneHTP::Exit()
{
	SceneBase::Exit();
}
