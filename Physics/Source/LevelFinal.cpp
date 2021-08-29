#include "LevelFinal.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>
#include <cmath>
#include "Player.h"
#include "GameLevelManager.h"
#include "GameStateManager.h"
#include "SceneGame.h"

//Remove later
#include "InteractableFactory.h"

LevelFinal::LevelFinal()
{
}

LevelFinal::~LevelFinal()
{
}

void LevelFinal::Init()
{
	SceneBase::Init();

	Math::InitRNG();
	UpdateLevel();
	//camera->setDebugMode();

	//CSoundController::GetInstance()->PlaySoundByID(18);
	startloopCounter = 0;
	CSoundController::GetInstance()->PlaySoundByID(80);
}

void LevelFinal::UpdateLevel()
{
	if (SceneGame::GetInstance()->curSubLevel <= numSubLevels)
	{
		switch (SceneGame::GetInstance()->curSubLevel)
		{
		case 1:
			GameLevelBase::Exit();
			loadMap("Maps//Map_LEVEL_FINAL.csv");
			camera->Init(Vector3(0, 0, 5), Vector3(0, 0, 0), Vector3(0, 1, 0), 80, 45,
				getworldWidth(), getworldHeight());
			camera->setpanTarget(player);
			break;
		}
	}
	else
	{
		SceneGame::GetInstance()->curSubLevel = 1;
		SceneGame::GetInstance()->curLevel = 1;
		GameStateManager::GetInstance()->SetActiveGameState("CreditsState");
	}
}

bool LevelFinal::Update(double dt)
{
	SceneBase::Update(dt);
	if (player->isControl() == true)
	{
		camera->setpanTarget(player);
	}
	else if (player->getClone()->isControl() == true)
	{
		camera->setpanTarget(player->getClone());
	}

	if (camera->getPanningMode() == false)
		camera->Update(dt);
	else
		camera->panToTarget(dt,m_speed);

	for (int i = 0; i < projectileList.size(); i++)
	{
		if (projectileList[i] == NULL)
			continue;
 		if (projectileList[i]->active == false)
			continue;
		AdvanceGO* curProjectile = projectileList[i];
		if (curProjectile->type == GameObject::GO_ARROW ||
			curProjectile->type == GameObject::GO_MAGICBALL ||
			curProjectile->type == GameObject::GO_PORTAL)
		{
			projectileList[i]->Update(dt, GAMESPEED);
		}
		else
			projectileList[i]->Update(dt, m_speed);
	}
	
	for (int i = 0; i < EntityList.size(); i++)
	{
		if (EntityList[i] == nullptr)
			continue;
		if (EntityList[i]->active == false)
			continue;
		if ((EntityList[i]->type == GameObject::GO_PLAYER)) {
			EntityList[i]->Update(dt, GAMESPEED);
		}
		else if (EntityList[i]->type == GameObject::GO_PLAYERCLONE)
		{
			EntityList[i]->Update(dt, GAMESPEED);
		}
		else
		{
			if (CheckWithinScreen(EntityList[i])) 
			{
				EntityList[i]->Update(dt, m_speed);
			}
		}
		if (clonedeleted == true)
		{
			if (EntityList[i]->type == GameObject::GO_PLAYERCLONE)
			{
				delete EntityList[i];
				EntityList[i] = nullptr;
				player->resetClone();
				clonedeleted = false;
			}
		}
	}
	cleanupLists(false, &EntityList);

	if (player->getSwap() == true)
	{
		swapcontrols();
		player->setSwap(false);
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
	if (player == nullptr || player->active == false)
		return false;
	player->vel += GamePhysics::GetInstance()->gravity * dt * GAMESPEED;
	if(player->getClone() != nullptr)
		player->getClone()->vel += GamePhysics::GetInstance()->gravity * dt * GAMESPEED;
	CollisionChecks(dt, m_speed);
	if (CheckWithinScreen(player))
		player->pos += player->vel * dt * GAMESPEED;

	if (player->getClone() != nullptr)
	{
		if (CheckWithinScreen(player->getClone()))
			player->getClone()->setpos(player->getClone()->getpos() + player->getClone()->getvel() * dt * GAMESPEED);
	}
	if (Player::GetInstance()->isCompleted)
	{
		SceneGame::GetInstance()->curSubLevel++;
		GameLevelBase::Exit();
		UpdateLevel();
		Player::GetInstance()->isCompleted = false;
	}

	return true;
}


void LevelFinal::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//Calculating aspect ratio
	//double m_CamHeight = 100.f;
	//double m_CamWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	// Projection matrix : Orthographic Projection
	Mtx44 projection;
	projection.SetToOrtho(0,160.f, 0,90.f, -10, 10);
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

	meshRender->RenderMesh(centralMesh->GetMeshID(CentralMesh::GEO_AXES), false);
	modelStack->PushMatrix();
	modelStack->Translate(getworldWidth()/2, getworldHeight()/2,-1);
	modelStack->Scale(getworldWidth(), getworldHeight(), -1);
	meshRender->RenderMesh(centralMesh->GetMeshID(CentralMesh::GO_BACKGROUND_CAVE), false);
	modelStack->PopMatrix();
	zOffset = 0.001f;
	for (std::vector<GameObject*>::iterator it = map.begin(); it != map.end(); ++it)
	{
		GameObject* go = (GameObject*)*it;
		if (go == nullptr)
			continue;
		if (!CheckWithinScreen(go) || go->active == false)
			continue;

		if (go->type != GameObject::OUTOFBOUNDS_TILE)
			RenderGO(go);
	}

	for (std::vector<AdvanceGO*>::iterator it = InteractableList.begin(); it != InteractableList.end(); it++)
	{
		GameObject* go = (GameObject*)*it;
		if (go == nullptr)
			continue;

		if (!CheckWithinScreen(go) || go->active == false)
			continue;

		RenderGO(go);
	}

	for (std::vector<AdvanceGO*>::iterator it = EntityList.begin(); it != EntityList.end(); it++)
	{
		GameObject* go = (GameObject*)*it;
		if (go == nullptr)
			continue;

		if (!CheckWithinScreen(go) || go->active == false)
			continue;

		RenderGO(go);
		if (go->type == GameObject::GO_DEMONLORD)
		{
			float scaleX = 32 * go->health / 3500.f;
			if (scaleX < 0)
				scaleX = 0;
			meshRender->RenderMeshOnScreen(centralMesh->GetMeshID(CentralMesh::GEO_QUAD), 40, 56, scaleX, 4);
			meshRender->RenderMeshOnScreen(centralMesh->GetMeshID(CentralMesh::GEO_DEMONLORD_HEALTHBAR), 40, 56, 40, 8);
		}
	}
	if (player != nullptr)
		RenderPlayer();

	for (std::vector<AdvanceGO*>::iterator it = projectileList.begin(); it != projectileList.end(); it++)
	{
		GameObject* go = (GameObject*)*it;
		if (go == nullptr)
			continue;

		if (!CheckWithinScreen(go) || go->active == false)
			continue;

		RenderGO(go);

	}

	

	//On screen text
	
	std::ostringstream ss;
	ss.precision(5);
	ss << "FPS: " << fps;
	meshRender->RenderTextOnScreen(centralMesh->GetMeshID(CentralMesh::GEO_TEXT), ss.str(), Color(0, 1, 0), 3,40,40);
	
	meshRender->RenderTextOnScreen(centralMesh->GetMeshID(CentralMesh::GEO_TEXT), "Collision", Color(0, 1, 0), 3, 0, 0);

}

void LevelFinal::Destroy()
{
	DestroyInstance();
}

void LevelFinal::Exit()
{
	SceneBase::Exit();
	GameLevelBase::Exit();
	//Cleanup GameObjects
	while(map.size() > 0)
	{
		GameObject *go = map.back();
		delete go;
		map.pop_back();
	}
	CSoundController::GetInstance()->StopSounds();
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