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
	m_speed = 2.7f;

	m_objectCount = 0;

	//Player Here
	player = Player::GetInstance();
	player->type = GameObject::GAMEOBJECT_TYPE::GO_PLAYER;
//	player->pos.Set(80, 45, 0.1f);
	player->vel.Set(1.f, 1.f, 0);
	player->scale.Set(5.f,5.f,1);
	Math::InitRNG();
	loadMap("Maps//SideScrollmap.csv");
	camera.Init(Vector3(0,0,5), Vector3(0,0, 0), Vector3(0, 1, 0), 80, 45);
	//Exercise 1: initialize m_objectCount
	
}

GameObject* SceneCollision::FetchGO()
{
	//Exercise 2a: implement FetchGO()
	for (std::vector<GameObject*>::iterator it = m_goList.begin(); it != m_goList.end(); it++)
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
	m_goList.back()->active = true;
	m_objectCount++;
	return m_goList.back();
}

void SceneCollision::ReturnGO(GameObject *go)
{
	//Exercise 3: implement ReturnGO()
	go->active = false;
	m_objectCount--;
}

//void SceneCollision::MakePillar(float x, float y, float thickness, GameObject::GAMEOBJECT_TYPE type)
//{
//	GameObject* go = FetchGO();
//	go->type = type;
//	go->active = true;
//	go->pos.Set(x, y, 0);
//	go->scale.Set(thickness, thickness, thickness);
//}
//
//void SceneCollision::MakeThinWall(float x, float y, float angleDeg, float thickness, float height)
//{
//	GameObject* go = FetchGO();
//	go->type = GameObject::GO_NONELASTIC_WALL;
//	go->active = true;
//	go->pos.Set(x, y, 0);
//	go->normal.Set(cosf(Math::DegreeToRadian(angleDeg)), sinf(Math::DegreeToRadian(angleDeg)), 0);
//	go->scale.Set(thickness, height, 1.f);
//
//	MakePillar(
//		go->pos.x - height * sinf(Math::DegreeToRadian(angleDeg)),
//		go->pos.y + height * cosf(Math::DegreeToRadian(angleDeg)),
//		thickness,
//		GameObject::GO_NONELASTIC_PILLAR);
//
//	MakePillar(
//		go->pos.x + height * sinf(Math::DegreeToRadian(angleDeg)),
//		go->pos.y - height * cosf(Math::DegreeToRadian(angleDeg)),
//		thickness,
//		GameObject::GO_NONELASTIC_PILLAR);
//}
//
//void SceneCollision::MakeThickWall(float x, float y, float angleDeg, float thickness, float height)
//{
//	angleDeg = Math::DegreeToRadian(angleDeg);
//
//	GameObject* go = FetchGO();
//	go->type = GameObject::GO_NONELASTIC_WALL;
//	go->active = true;
//	go->pos.Set(x, y);
//	go->normal.Set(cosf(angleDeg), sinf(angleDeg), 0);
//	go->scale.Set(thickness, height, 1.f);
//
//	GameObject* go2 = FetchGO();
//	go2->type = GameObject::GO_NONELASTIC_WALL;
//	go2->active = true;
//	go2->pos.Set(x, y);
//	go2->normal.Set(sinf(-angleDeg), cosf(-angleDeg), 0);
//	go2->scale.Set(height, thickness, 1.f);
//
//	MakePillar(x + (thickness - 0.0005f) * cosf(angleDeg) - (height + 0.0005f) * sinf(angleDeg),
//		y + (height - 0.0005f) * cosf(angleDeg) + (thickness + 0.0005f) * sinf(angleDeg),
//		0.1f,
//		GameObject::GO_NONELASTIC_PILLAR);
//	MakePillar(x + (-thickness + 0.0005f) * cosf(angleDeg) - (height + 0.0005f) * sinf(angleDeg),
//		y + (height - 0.0005f) * cosf(angleDeg) + (-thickness - 0.0005f) * sinf(angleDeg),
//		0.1f,
//		GameObject::GO_NONELASTIC_PILLAR);
//	MakePillar(x + (thickness - 0.0005f) * cosf(angleDeg) - (-height - 0.0005f) * sinf(angleDeg),
//		y + (-height + 0.0005f) * cosf(angleDeg) + (thickness - 0.0005f) * sinf(angleDeg),
//		0.1f,
//		GameObject::GO_NONELASTIC_PILLAR);
//	MakePillar(x + (-thickness + 0.0005f) * cosf(angleDeg) - (-height + 0.0005f) * sinf(angleDeg),
//		y + (-height + 0.0005f) * cosf(angleDeg) + (-thickness + 0.0005f) * sinf(angleDeg),
//		0.1f,
//		GameObject::GO_NONELASTIC_PILLAR);
//}
//
//void SceneCollision::MakeFlipper(float x, float y,Vector3 pivotPos, float defaultAngle, float angleSpeed, float thickness, float height)
//{
//	GameObject* go = FetchGO();
//	go->type = GameObject::GO_FLIPPER;
//	go->pivot = pivotPos;
//	go->scale.Set(thickness, height, thickness);
//	go->normal = Vector3(0, 1, 0).Rotate(defaultAngle);
//	go->angularVelocity = angleSpeed;
//	
//	Vector3 PivToPos = Vector3(x, y, 0) - pivotPos;
//	float angle = Math::DegreeToRadian(defaultAngle);
//	go->pos.Set(
//		x,
//		y,
//		0
//	);
//
//	go = FetchGO();
//	go->type = GameObject::GO_FLIPPER_PILLAR;
//	go->pivot = pivotPos;
//	go->scale.Set(thickness, thickness, thickness);
//	go->normal = Vector3(0, 1, 0).Rotate(defaultAngle);
//	go->angularVelocity = angleSpeed;
//	go->pos.Set(
//		x + height * cos(angle),
//		y + height * sin(angle),
//		0
//	);
//
//	go = FetchGO();
//	go->type = GameObject::GO_FLIPPER_PILLAR;
//	go->pivot = pivotPos;
//	go->scale.Set(thickness, thickness, thickness);
//	go->normal = Vector3(0, 1, 0).Rotate(defaultAngle);
//	go->angularVelocity = angleSpeed;
//	go->pos.Set(
//		x + -height * cos(angle),
//		y + -height * sin(angle),
//		0
//	);
//}

bool SceneCollision::Update(double dt)
{
	SceneBase::Update(dt);
	camera.Update(dt,player);
	player->Update(dt);

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

	//Physics Simulation Section
	// Check for gameObjects within screen only
	//Find how many tiles screen is away from left side
	int XnumTiles = (camera.position.x - fmod(camera.position.x, getTileWidth())) / getTileWidth();
	int XTilesInScr;
	if (fmod(camera.position.x, getTileWidth()) > 0)
		XTilesInScr = 33;
	else
		XTilesInScr = 32;

	int YnumTiles = (camera.position.y - fmod(camera.position.y, getTileHeight())) / getTileHeight();
	int YTilesInScr;
	if (fmod(camera.position.y, getTileHeight()) > 0)
		YTilesInScr = 19;
	else
		YTilesInScr = 18;


	int XTilesInWorld = getworldWidth() / getTileWidth();
	int YTilesInWorld = getworldHeight() / getTileHeight();
	for (int i = XnumTiles; i < XnumTiles + XTilesInScr; i++)
	{
		for (int j = YnumTiles; j < YnumTiles + YTilesInScr; j++)
		{
			int TileSpace = j * XTilesInWorld + i;
			if (map[TileSpace] != nullptr)
			{
				if (GamePhysics::GetInstance()->CheckCollision(player, map[TileSpace], dt))
				{
					GamePhysics::GetInstance()->CheckCollisionResponse(player, map[TileSpace], dt);
					cout << "Collided" << endl;
				}

			}
		}
	}

	player->Update(dt);

	return true;
}


void SceneCollision::RenderGO(GameObject *go)
{
	switch(go->type)
	{
	case GameObject::GO_BALL:
		//Exercise 4: render a sphere using scale and pos
		modelStack.PushMatrix();
		{
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
			SceneBase::ChangeMat(SceneBase::GEO_BALL, Color(1.f, 1.f, 1.f), 1.f, 0.6f, 0.3f, 1.f);
			RenderMesh(meshList[SceneBase::GEO_BALL], true);
		}
		modelStack.PopMatrix();
		//Exercise 11: think of a way to give balls different colors
		break;
	case GameObject::GO_WALL:
		modelStack.PushMatrix();
		{
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Rotate(Math::RadianToDegree(atan2f(go->normal.y, go->normal.x)), 0, 0, 1);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
			SceneBase::ChangeMat(SceneBase::GEO_CUBE, Color(1.f, 0.f, 0.5f), 1.f, 0.6f, 0.3f, 1.f);
			RenderMesh(meshList[SceneBase::GEO_CUBE], true);
		}
		modelStack.PopMatrix();
		break;
	case GameObject::GO_PILLAR:
		modelStack.PushMatrix();
		{
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
			SceneBase::ChangeMat(SceneBase::GEO_CYLINDER, Color(1.f, 0.f, 0.5f), 1.f, 0.6f, 0.3f, 1.f);
			RenderMesh(meshList[SceneBase::GEO_CYLINDER], true);
		}
		modelStack.PopMatrix();
		break;
	case GameObject::GO_FLIPPER:
		modelStack.PushMatrix();
		{
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Rotate(Math::RadianToDegree(atan2f(go->normal.y, go->normal.x)), 0, 0, 1);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
			SceneBase::ChangeMat(SceneBase::GEO_CUBE, Color(1.f, 0.5f, 0.05f), 1.f, 0.6f, 0.3f, 1.f);
			RenderMesh(meshList[SceneBase::GEO_CUBE], true);
		}
		modelStack.PopMatrix();
		break;
	case GameObject::GO_FLIPPER_PILLAR:
		modelStack.PushMatrix();
		{
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
			SceneBase::ChangeMat(SceneBase::GEO_CYLINDER, Color(1.f, 0.5f, 0.05f), 1.f, 0.6f, 0.3f, 1.f);
			RenderMesh(meshList[SceneBase::GEO_CYLINDER], true);
		}
		modelStack.PopMatrix();
		break;

	case GameObject::STONE_BRICK_TILE:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[STONEBRICK_TILE], false);
		modelStack.PopMatrix();
		break;


	case GameObject::BRICK_TILE:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[BRICK_TILE], false);
		modelStack.PopMatrix();
		break;
	case GameObject::GO_PLAYER:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_PLAYER], false);
		modelStack.PopMatrix();
		break;

	case GameObject::ROCK_TILE:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		ChangeMat(GEO_CUBE, Color(0.7f, 0.7f, 0.7f), 1.f, 0.6f, 0.3f, 1.f);
		RenderMesh(meshList[GEO_CUBE], false);
		modelStack.PopMatrix();
		break;

	case GameObject::SOIL_TILE:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		ChangeMat(GEO_CUBE, Color(1.f, 0.4f, 0.4f), 1.f, 0.6f, 0.3f, 1.f);
		RenderMesh(meshList[GEO_CUBE], false);
		modelStack.PopMatrix();
		break;

	case GameObject::GRASS_SOIL_TILE:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		ChangeMat(GEO_CUBE, Color(0.7f, 1.f, 0.f), 1.f, 0.6f, 0.3f, 1.f);
		RenderMesh(meshList[GEO_CUBE], false);
		modelStack.PopMatrix();
		break;

	case GameObject::GRASS_SOIL_FLOWERS_TILE:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		ChangeMat(GEO_CUBE, Color(0.7f, 1.f, 0.f), 1.f, 0.6f, 0.3f, 1.f);
		RenderMesh(meshList[GEO_CUBE], false);
		modelStack.PopMatrix();
		break;
	}
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

	for(std::vector<GameObject *>::iterator it = map.begin(); it != map.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if (go == nullptr)
			continue;
		if(go->active)
		{
			RenderGO(go);
		}
	}

	RenderGO(player);
	//On screen text


	std::ostringstream ss;
	//Exercise 5: Render m_objectCount
	ss << "GameObject Count: " << m_objectCount;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 12);
	
	ss.str("");
	ss.precision(5);
	ss << "FPS: " << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 3);
	
	RenderTextOnScreen(meshList[GEO_TEXT], "Collision", Color(0, 1, 0), 3, 0, 0);

}

void SceneCollision::Exit()
{
	SceneBase::Exit();
	//Cleanup GameObjects
	while(m_goList.size() > 0)
	{
		GameObject *go = m_goList.back();
		delete go;
		m_goList.pop_back();
	}

	DestroyInstance();
}

void SceneCollision::ResetList(void)
{
	for (int i = 0; i < m_goList.size(); i++)
	{
		if (m_goList[i]->active == true)
		{
			m_goList[i]->active = false;
			m_objectCount--;
		}
	}
}