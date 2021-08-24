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

	camera->Init(Vector3(0, 0, 5), Vector3(0, 0, 0), Vector3(0, 1, 0), 0, 0);
}
bool SceneHTP::Update(double dt)
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
	if (posX > 7 && posX < 18 && posY > -57 && posY < -52)
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
	return true;
}

void SceneHTP::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Projection matrix : Orthographic Projection
	Mtx44 projection;
	projection.SetToOrtho(0, m_worldWidth, 0, m_worldHeight, -10, 10);
	projectionStack->LoadMatrix(projection);
	
	// Camera matrix
	viewStack->LoadIdentity();
	viewStack->LookAt(
						camera->position.x, camera->position.y, camera->position.z,
						camera->target.x, camera->target.y, camera->target.z,
						camera->up.x, camera->up.y, camera->up.z
					);
	// Model matrix : an identity matrix (model will be at the origin)
	modelStack->LoadIdentity();
	
	meshRender->RenderMesh(centralMesh->GetMeshID(CentralMesh::GEO_AXES), false);
	////////////// Background Image  /////////////////////
	modelStack->PushMatrix();
	modelStack->Translate(m_worldWidth/2, m_worldHeight/2, -1);
	modelStack->Scale(88, 55, 55);
	meshRender->RenderMesh(centralMesh->GetMeshID(CentralMesh::GEO_CONTROLS), false);
	modelStack->PopMatrix();

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
	ss << "<Back";
	meshRender->RenderTextOnScreen(centralMesh->GetMeshID(CentralMesh::GEO_TEXT), ss.str(), BackButton, 4, 7, 2);
}

void SceneHTP::Destroy()
{
	DestroyInstance();
}

void SceneHTP::Exit()
{
	SceneBase::Exit();
}
