#include "SceneCollision.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>
#include <cmath>
#include "Player.h"

SceneCollision::SceneCollision()
{
	std::cout << "Initialising" << std::endl;
}

SceneCollision::~SceneCollision()
{
}

void SceneCollision::Init()
{
	SceneBase::Init();

	//Calculating aspect ratio
	//m_worldHeight = 100.f;
	//m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	//Physics code here
	m_objectCount = 0;

	//Player Here
	player = Player::GetInstance();
	player->type = GameObject::GAMEOBJECT_TYPE::GO_PLAYER;
//	player->pos.Set(80, 45, 0.1f);
	player->vel.Set(1.f, 1.f, 0);
	player->scale.Set(4.5f,4.5f,1);
	Math::InitRNG();
	loadMap("Maps//SideScrollmap.csv");
	camera.Init(Vector3(0,0,5), Vector3(0,0, 0), Vector3(0, 1, 0), 80, 45);
	//Exercise 1: initialize m_objectCount
}

GameObject* SceneCollision::FetchGO()
{
	//Exercise 2a: implement FetchGO()
	for (std::vector<GameObject*>::iterator it = map.begin(); it != map.end(); it++)
	{
		GameObject* go = (GameObject*)*it;
		if (go->active == false)
		{
			go->active = true;
			//Exercise 2b: increase object count every time an object is set to active
			m_objectCount++;
			return go;
		}
	}
	for (int i = 0; i < 10; i++)
	{
		//m_goList.push_back(new GameObject(GameObject::GO_BALL));
	}
	//Exercise 2b: increase object count every time an object is set to active
	map.back()->active = true;
	m_objectCount++;
	return map.back();
}

void SceneCollision::ReturnGO(GameObject *go)
{
	//Exercise 3: implement ReturnGO()
	go->active = false;
	m_objectCount--;
}

bool SceneCollision::Update(double dt)
{
	SceneBase::Update(dt);
	camera.Update(dt,player);
	player->Update(dt,m_speed);

	for (int i = 0; i < projectileList.size(); i++)
	{
		projectileList[i]->Update(dt, m_speed);
	}
	
	for (int i = 0; i < EntityList.size(); i++)
	{
		EntityList[i]->Update(dt,m_speed);
	}

	if (Application::IsKeyPressed('9'))
	{
		m_speed = Math::Max(0.f, m_speed - 0.1f);
	}
	if (Application::IsKeyPressed('0'))
	{
		m_speed += 0.1f;
	}
	if (Application::IsKeyPressed('R'))
	{
	}
	//Changing Material
	static bool EbuttonState = false;
	if (Application::IsKeyPressed('E') && !EbuttonState)
	{
		EbuttonState = true;
	}
	else if (!Application::IsKeyPressed('E') && EbuttonState)
	{
		EbuttonState = false;
	}
	//Mouse Section
	double x, y;
	Application::GetCursorPos(&x, &y);
	unsigned w = Application::GetWindowWidth();
	unsigned h = Application::GetWindowHeight();
	double PosX = (x / w) * m_worldWidth;
	double PosY = m_worldHeight - (y / h) * m_worldHeight;
	static bool bLButtonState = false;
	if (!bLButtonState && Application::IsMousePressed(0))
	{
		bLButtonState = true;
		std::cout << "LBUTTON DOWN" << std::endl;
	}
	else if (bLButtonState && !Application::IsMousePressed(0))
	{
		bLButtonState = false;
	}
	static bool bRButtonState = false;
	if (Application::IsMousePressed(1))
	{
		if (!bRButtonState) {
			bRButtonState = true;
			std::cout << "RBUTTON DOWN" << std::endl;
		}
	}
	else if (bRButtonState && !Application::IsMousePressed(1))
	{
		bRButtonState = false;
	}

	// ball Spawn
	if (Application::IsKeyPressed(VK_SPACE))
	{
	}

	// Erase Last Shape
	static bool RButtonState = false;
	if (Application::IsKeyPressed('Q') && !RButtonState)
	{
		RButtonState = true;
	}
	else if (!Application::IsKeyPressed('Q') && RButtonState)
	{
		RButtonState = false;
	}

	player->vel += GamePhysics::GetInstance()->gravity * dt * m_speed;
	//Physics Simulation Section
	// Check for gameObjects within screen only
	//Find how many tiles screen is away from left side
	//int XnumTiles = (camera.position.x - fmod(camera.position.x, getTileWidth())) / getTileWidth();
	//int XTilesInScr;
	//if (fmod(camera.position.x, getTileWidth()) > 0)
	//	XTilesInScr = 33;
	//else
	//	XTilesInScr = 32;

	//int YnumTiles = (camera.position.y - fmod(camera.position.y, getTileHeight())) / getTileHeight();
	//int YTilesInScr;
	//if (fmod(camera.position.y, getTileHeight()) > 0)
	//	YTilesInScr = 19;
	//else
	//	YTilesInScr = 18;


	//int XTilesInWorld = getworldWidth() / getTileWidth();
	//int YTilesInWorld = getworldHeight() / getTileHeight();
	//for (int i = XnumTiles; i < XnumTiles + XTilesInScr; i++)
	//{
	//	for (int j = YnumTiles; j < YnumTiles + YTilesInScr; j++)
	//	{
	//		int TileSpace = j * XTilesInWorld + i;
	//		if (map[TileSpace] != nullptr)
	//		{
	//			if (GamePhysics::GetInstance()->CheckCollision(player, map[TileSpace], dt, m_speed))
	//			{
	//				GamePhysics::GetInstance()->CheckCollisionResponse(player, map[TileSpace], dt, m_speed);
	//				//cout << "Collided" << endl;
	//				break;
	//			}

	//		}
	//	}
	//}
	CollisionChecks(dt, m_speed);
	player->pos += player->vel * dt * m_speed;
	return true;
}


void SceneCollision::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//Calculating aspect ratio
	//double m_CamHeight = 100.f;
	//double m_CamWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	// Projection matrix : Orthographic Projection
	Mtx44 projection;
	projection.SetToOrtho(0,160.f, 0,90.f, -10, 10);
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

	//Pass light
	if (lights[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(lights[0].position.x, lights[0].position.y, lights[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
	RenderMesh(meshList[GEO_AXES], false);
	zOffset = 0;
	for (std::vector<GameObject*>::iterator it = map.begin(); it != map.end(); ++it)
	{
		GameObject* go = (GameObject*)*it;
		if (go == nullptr)
			continue;
		if (go->active)
		{
			RenderGO(go);
		}
	}

	for (std::vector<AdvanceGO*>::iterator it = EntityList.begin(); it != EntityList.end(); it++)
	{
		GameObject* go = (GameObject*)*it;
		if (go == nullptr)
			continue;
		if (go->active)
		{
			RenderGO(go);
		}
	}
	RenderPlayer();

	for (std::vector<AdvanceGO*>::iterator it = projectileList.begin(); it != projectileList.end(); it++)
	{
		GameObject* go = (GameObject*)*it;
		if (go == nullptr)
			continue;
		if (go->active)
		{
			RenderGO(go);
		}
	}

	

	//On screen text
	
	std::ostringstream ss;
	//Exercise 5: Render m_objectCount
	ss << "GameObject Count: " << m_objectCount;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 12);
	
	ss.str("");
	ss.precision(5);
	ss << "FPS: " << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3,40,40);
	
	RenderTextOnScreen(meshList[GEO_TEXT], "Collision", Color(0, 1, 0), 3, 0, 0);

}

void SceneCollision::Exit()
{
	SceneBase::Exit();
	//Cleanup GameObjects
	while(map.size() > 0)
	{
		GameObject *go = map.back();
		delete go;
		map.pop_back();
	}

	DestroyInstance();
}
/*
void SceneCollision::ResetList(void)
{
	for (int i = 0; i < map.size(); i++)
	{
		if (map[i]->active == true)
		{
			map[i]->active = false;
			m_objectCount--;
		}
	}
	for (int i = 0; i < EntityList.size(); i++)
	{
		delete EntityList[i];
		EntityList[i] = nullptr;
		EntityList.pop_back(i );
	}
}*/