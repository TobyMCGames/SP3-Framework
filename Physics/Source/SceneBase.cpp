#include "SceneBase.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <fstream>
#include <sstream>

SceneBase::SceneBase()
	: cKeyboardController(NULL)
	, meshRender(NULL)
	, centralMesh(NULL)
{
	
}

SceneBase::~SceneBase()
{
}

void SceneBase::Init()
{
	cKeyboardController = CKeyboardController::GetInstance();
	meshRender = MeshRender::GetInstance();
	modelStack = meshRender->GetModelStack();
	viewStack = meshRender->GetViewStack();
	projectionStack = meshRender->GetProjectionStack();
	centralMesh = CentralMesh::GetInstance();
	camera = meshRender->GetCamera();
	camera->setpanTarget();
}

bool SceneBase::Update(double dt)
{
	//Keyboard Section
	/*if(Application::IsKeyPressed('1'))
		glEnable(GL_CULL_FACE);*/
	if(Application::IsKeyPressed('2'))
		glDisable(GL_CULL_FACE);
	if(Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if(Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	fps = (float)(1.f / dt);

	return true;
}

void SceneBase::RenderGO(GameObject* go)
{
	switch (go->type)
	{
	case GameObject::GO_BALL:
		//Exercise 4: render a sphere using scale and pos
		modelStack->PushMatrix();
		{
			modelStack->Translate(go->pos.x, go->pos.y, go->pos.z+zOffset);
			modelStack->Scale(go->scale.x, go->scale.y, go->scale.z);
			centralMesh->ChangeMat(CentralMesh::GEO_BALL, Color(1.f, 1.f, 1.f), 1.f, 0.6f, 0.3f, 1.f);
			meshRender->RenderMesh(centralMesh->GetMeshID(CentralMesh::GEO_BALL), true);
		}
		modelStack->PopMatrix();
		//Exercise 11: think of a way to give balls different colors
		break;
	case GameObject::GO_WALL:
		modelStack->PushMatrix();
		{
			modelStack->Translate(go->pos.x, go->pos.y, go->pos.z + zOffset);
			modelStack->Rotate(Math::RadianToDegree(atan2f(go->normal.y, go->normal.x)), 0, 0, 1);
			modelStack->Scale(go->scale.x, go->scale.y, go->scale.z);
			centralMesh->ChangeMat(CentralMesh::GEO_CUBE, Color(1.f, 0.f, 0.5f), 1.f, 0.6f, 0.3f, 1.f);
			meshRender->RenderMesh(centralMesh->GetMeshID(CentralMesh::GEO_CUBE), true);
		}
		modelStack->PopMatrix();
		break;
	case GameObject::GO_PILLAR:
		modelStack->PushMatrix();
		{
			modelStack->Translate(go->pos.x, go->pos.y, go->pos.z + zOffset);
			modelStack->Scale(go->scale.x, go->scale.y, go->scale.z);
			centralMesh->ChangeMat(CentralMesh::GEO_CYLINDER, Color(1.f, 0.f, 0.5f), 1.f, 0.6f, 0.3f, 1.f);
			meshRender->RenderMesh(centralMesh->GetMeshID(CentralMesh::GEO_CYLINDER), true);
		}
		modelStack->PopMatrix();
		break;
	case GameObject::GO_FLIPPER:
		modelStack->PushMatrix();
		{
			modelStack->Translate(go->pos.x, go->pos.y, go->pos.z + zOffset);
			modelStack->Rotate(Math::RadianToDegree(atan2f(go->normal.y, go->normal.x)), 0, 0, 1);
			modelStack->Scale(go->scale.x, go->scale.y, go->scale.z);
			centralMesh->ChangeMat(CentralMesh::GEO_CUBE, Color(1.f, 0.5f, 0.05f), 1.f, 0.6f, 0.3f, 1.f);
			meshRender->RenderMesh(centralMesh->GetMeshID(CentralMesh::GEO_CUBE), true);
		}
		modelStack->PopMatrix();
		break;
	case GameObject::GO_FLIPPER_PILLAR:
		modelStack->PushMatrix();
		{
			modelStack->Translate(go->pos.x, go->pos.y, go->pos.z + zOffset);
			modelStack->Scale(go->scale.x, go->scale.y, go->scale.z);
			centralMesh->ChangeMat(CentralMesh::GEO_CYLINDER, Color(1.f, 0.5f, 0.05f), 1.f, 0.6f, 0.3f, 1.f);
			meshRender->RenderMesh(centralMesh->GetMeshID(CentralMesh::GEO_CYLINDER), true);
		}
		modelStack->PopMatrix();
		break;

	case GameObject::STONE_BRICK_TILE:
		modelStack->PushMatrix();
		modelStack->Translate(go->pos.x, go->pos.y, go->pos.z + zOffset);
		modelStack->Scale(go->scale.x, go->scale.y, go->scale.z);
		meshRender->RenderMesh(centralMesh->GetMeshID(CentralMesh::GEO_STONEBRICK), false);
		modelStack->PopMatrix();
		break;

	case GameObject::BRICK_TILE:
		modelStack->PushMatrix();
		modelStack->Translate(go->pos.x, go->pos.y, go->pos.z + zOffset);
		modelStack->Scale(go->scale.x, go->scale.y, go->scale.z);
		meshRender->RenderMesh(centralMesh->GetMeshID(CentralMesh::GEO_BRICK), false);
		modelStack->PopMatrix();
		break;

	case GameObject::SOIL_TILE:
		modelStack->PushMatrix();
		modelStack->Translate(go->pos.x, go->pos.y, go->pos.z + zOffset);
		modelStack->Scale(go->scale.x, go->scale.y, go->scale.z);
		meshRender->RenderMesh(centralMesh->GetMeshID(CentralMesh::GEO_SOIL_TILE), false);
		modelStack->PopMatrix();
		break;

	case GameObject::GRASS_SOIL_TILE:
		modelStack->PushMatrix();
		modelStack->Translate(go->pos.x, go->pos.y, go->pos.z + zOffset);
		modelStack->Scale(go->scale.x, go->scale.y, go->scale.z);
		meshRender->RenderMesh(centralMesh->GetMeshID(CentralMesh::GEO_GRASS_SOIL_TILE), false);
		modelStack->PopMatrix();
		break;

	case GameObject::SPIKE_TILE:
		modelStack->PushMatrix();
		modelStack->Translate(go->pos.x, go->pos.y, go->pos.z + zOffset);
		modelStack->Scale(go->scale.x, go->scale.y, go->scale.z);
		meshRender->RenderMesh(centralMesh->GetMeshID(CentralMesh::GEO_SPIKE), false);
		modelStack->PopMatrix();
		break;

	case GameObject::GO_ARROW:
		modelStack->PushMatrix();
		modelStack->Translate(go->pos.x, go->pos.y, go->pos.z + zOffset);
		modelStack->Rotate(Math::RadianToDegree(atan2f(go->normal.y, go->normal.x)), 0, 0, 1);
		modelStack->Scale(go->scale.x, go->scale.y, go->scale.z);
		meshRender->RenderMesh(centralMesh->GetMeshID(CentralMesh::GEO_ARROW), false);
		modelStack->PopMatrix();
		break;

	case GameObject::GO_MAGICBALL:
		modelStack->PushMatrix();
		modelStack->Translate(go->pos.x, go->pos.y, go->pos.z + zOffset);
		modelStack->Rotate(Math::RadianToDegree(atan2f(go->normal.y, go->normal.x)), 0, 0, 1);
		modelStack->Scale(go->scale.x, go->scale.y, go->scale.z);
		//meshRender->RenderMesh(centralMesh->GetMeshID(CentralMesh::GEO_MAGICBALL), false);
		go->Render();
		modelStack->PopMatrix();
		break;

	case GameObject::GO_PORTAL:
		modelStack->PushMatrix();
		modelStack->Translate(go->pos.x, go->pos.y, go->pos.z + zOffset);
		modelStack->Rotate(Math::RadianToDegree(atan2f(go->normal.y, go->normal.x)), 0, 0, 1);
		modelStack->Scale(go->scale.x, go->scale.y, go->scale.z);
		meshRender->RenderMesh(centralMesh->GetMeshID(CentralMesh::GEO_PORTAL), false);
		modelStack->PopMatrix();
		break;

	case GameObject::PORTAL_GATE_ENTRANCE:
		modelStack->PushMatrix();
		modelStack->Translate(go->pos.x, go->pos.y, go->pos.z + zOffset);
		modelStack->Rotate(Math::RadianToDegree(atan2f(go->normal.y, go->normal.x)), 0, 0, 1);
		modelStack->Scale(go->scale.x, go->scale.y, go->scale.z);
		meshRender->RenderMesh(centralMesh->GetMeshID(CentralMesh::GEO_PORTAL_GATE_ENTRANCE), false);
		modelStack->PopMatrix();
		break;

	case GameObject::PORTAL_GATE_EXIT:
		modelStack->PushMatrix();
		modelStack->Translate(go->pos.x, go->pos.y, go->pos.z + zOffset);
		modelStack->Rotate(Math::RadianToDegree(atan2f(go->normal.y, go->normal.x)), 0, 0, 1);
		modelStack->Scale(go->scale.x, go->scale.y, go->scale.z);
		meshRender->RenderMesh(centralMesh->GetMeshID(CentralMesh::GEO_PORTAL_GATE_EXIT), false);
		modelStack->PopMatrix();
		break;

	case GameObject::GO_SKELEARROW:
		modelStack->PushMatrix();
		modelStack->Translate(go->pos.x, go->pos.y, go->pos.z + zOffset);
		modelStack->Rotate(Math::RadianToDegree(atan2f(go->normal.y, go->normal.x)), 0, 0, 1);
		modelStack->Scale(go->scale.x, go->scale.y, go->scale.z);
		meshRender->RenderMesh(centralMesh->GetMeshID(CentralMesh::GEO_SKELEARROW), false);
		modelStack->PopMatrix();
		break;

	case GameObject::GO_SPIDERWEB:
		modelStack->PushMatrix();
		modelStack->Translate(go->pos.x, go->pos.y, go->pos.z + zOffset);
		modelStack->Rotate(Math::RadianToDegree(atan2f(go->normal.y, go->normal.x)), 0, 0, 1);
		modelStack->Scale(go->scale.x, go->scale.y, go->scale.z);
		meshRender->RenderMesh(centralMesh->GetMeshID(CentralMesh::GEO_SPIDERWEB), false);
		modelStack->PopMatrix();
		break;

	case GameObject::GO_TURRETBULLET:
		modelStack->PushMatrix();
		modelStack->Translate(go->pos.x, go->pos.y+0.7, go->pos.z + zOffset);
		modelStack->Rotate(Math::RadianToDegree(atan2f(go->normal.y, go->normal.x)), 0, 0, 1);
		modelStack->Scale(go->scale.x, go->scale.y, go->scale.z);
		meshRender->RenderMesh(centralMesh->GetMeshID(CentralMesh::GEO_TURRETBULLET), false);
		modelStack->PopMatrix();
		break;

	case GameObject::GO_ZOMBIE:
		modelStack->PushMatrix();
		modelStack->Translate(go->pos.x, go->pos.y, go->pos.z + zOffset);
		if(go->vel.x < 0)
			modelStack->Rotate(180, 0, 1, 0);
		else
			modelStack->Rotate(0, 0, 1, 0);
		modelStack->Scale(go->scale.x, go->scale.y, go->scale.z);
		meshRender->RenderMesh(centralMesh->GetMeshID(CentralMesh::GEO_ZOMBIE), false);
		modelStack->PopMatrix();
		break;
	case GameObject::GO_SKELEARCHER:
		//std::cout << "SKARCHER" << go->pos.z + zOffset << std::endl;
		modelStack->PushMatrix();
		{
			modelStack->Translate(go->pos.x, go->pos.y, go->pos.z + zOffset);
			modelStack->Scale(go->scale.x, go->scale.y, go->scale.z);
			meshRender->RenderMesh(centralMesh->GetMeshID(CentralMesh::GEO_SKELETONARCHER), false);
			modelStack->PushMatrix();
			{
				modelStack->Translate(0, 0,0.001f);
				zOffset += 0.001f;
				if (go->normal.x >= 0)
					modelStack->Rotate(Math::RadianToDegree(atan2f(go->normal.y, go->normal.x)), 0, 0, 1);
				else
				{
					modelStack->Rotate(180, 0, 1, 0);
					modelStack->Rotate(Math::RadianToDegree(atan2f(go->normal.y, -go->normal.x)), 0, 0, 1);
				}
				modelStack->PushMatrix();
				{
					modelStack->Translate(0.35, 0, 0);
					meshRender->RenderMesh(centralMesh->GetMeshID(CentralMesh::GEO_BOW), false);
				}
				modelStack->PopMatrix();
			}
			modelStack->PopMatrix();
		}
		modelStack->PopMatrix();
		break;
	case GameObject::GO_SPIDER:
		modelStack->PushMatrix();
		modelStack->Translate(go->pos.x, go->pos.y, go->pos.z + zOffset);
		modelStack->Scale(go->scale.x, go->scale.y, go->scale.z);
		meshRender->RenderMesh(centralMesh->GetMeshID(CentralMesh::GEO_SPIDER), false);
		modelStack->PopMatrix();
		break;
	case GameObject::GO_TURRET:
		modelStack->PushMatrix();
		modelStack->Translate(go->pos.x, go->pos.y, go->pos.z + zOffset);
		modelStack->Scale(go->scale.x, go->scale.y, go->scale.z);
		meshRender->RenderMesh(centralMesh->GetMeshID(CentralMesh::GEO_TURRET), false);
		modelStack->PopMatrix();
		break;
	case GameObject::WEAPON_STATION_BOW:
		modelStack->PushMatrix();
		modelStack->Translate(go->pos.x, go->pos.y, go->pos.z + zOffset);
		modelStack->Scale(go->scale.x, go->scale.y, go->scale.z);
		meshRender->RenderMesh(centralMesh->GetMeshID(CentralMesh::GEO_WEAPON_STATION), false);
		modelStack->PushMatrix();
		{
			modelStack->Translate(0, 1.f, 0);
			meshRender->RenderMesh(centralMesh->GetMeshID(CentralMesh::GEO_BOW), false);
		}
		modelStack->PopMatrix();
		modelStack->PopMatrix();
		break;
	case GameObject::WEAPON_STATION_STAFF:
		modelStack->PushMatrix();
		modelStack->Translate(go->pos.x, go->pos.y, go->pos.z + zOffset);
		modelStack->Scale(go->scale.x, go->scale.y, go->scale.z);
		meshRender->RenderMesh(centralMesh->GetMeshID(CentralMesh::GEO_WEAPON_STATION), false);
		modelStack->PushMatrix();
		{
			modelStack->Translate(0, 1.f, 0);
			meshRender->RenderMesh(centralMesh->GetMeshID(CentralMesh::GEO_STAFF), false);
		}
		modelStack->PopMatrix();
		modelStack->PopMatrix();
		break;
	case GameObject::WEAPON_STATION_PORTAL:
		modelStack->PushMatrix();
		modelStack->Translate(go->pos.x, go->pos.y, go->pos.z + zOffset);
		modelStack->Scale(go->scale.x, go->scale.y, go->scale.z);
		meshRender->RenderMesh(centralMesh->GetMeshID(CentralMesh::GEO_WEAPON_STATION), false);
		modelStack->PushMatrix();
		{
			modelStack->Translate(0, 1.f, 0);
			meshRender->RenderMesh(centralMesh->GetMeshID(CentralMesh::GEO_PORTALGUN), false);
		}
		modelStack->PopMatrix();
		modelStack->PopMatrix();
		break;
	case GameObject::WARP_GATE:
		modelStack->PushMatrix();
		modelStack->Translate(go->pos.x, go->pos.y, go->pos.z + zOffset);
		modelStack->Scale(go->scale.x, go->scale.y, go->scale.z);
		meshRender->RenderMesh(centralMesh->GetMeshID(CentralMesh::GEO_WARP_GATE_TILE), false);
		modelStack->PopMatrix();
	}
	zOffset += 0.001f;
}

void SceneBase::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void SceneBase::Destroy()
{
}

void SceneBase::Exit()
{
	camera = nullptr;
	modelStack = nullptr;
	viewStack = nullptr;
	projectionStack = nullptr;
	cKeyboardController = nullptr;
}
