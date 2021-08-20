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
{
	for (int i = 0; i < 256; ++i) {
		textWidth[i] = NULL;
	}
}

SceneBase::~SceneBase()
{
}

void SceneBase::Init()
{
	cKeyboardController = CKeyboardController::GetInstance();
	zOffset = 0.f;
	FontLoader("Image//FontData.csv");
	// Black background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 
	
	glDisable(GL_CULL_FACE);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	m_programID = LoadShaders( "Shader//comg.vertexshader", "Shader//comg.fragmentshader" );
	
	// Get a handle for our uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	//m_parameters[U_MODEL] = glGetUniformLocation(m_programID, "M");
	//m_parameters[U_VIEW] = glGetUniformLocation(m_programID, "V");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");
	// Get a handle for our "colorTexture" uniform
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
	// Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");
	
	// Use our shader
	glUseProgram(m_programID);

	lights[0].type = Light::LIGHT_DIRECTIONAL;
	lights[0].position.Set(0, 0, -20);
	lights[0].color.Set(1, 1, 1);
	lights[0].power = 1;
	lights[0].kC = 1.f;
	lights[0].kL = 0.01f;
	lights[0].kQ = 0.001f;
	lights[0].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[0].cosInner = cos(Math::DegreeToRadian(30));
	lights[0].exponent = 3.f;
	lights[0].spotDirection.Set(0.f, 0.f, 1.f);
	
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glUniform1i(m_parameters[U_NUMLIGHTS], 0);

	glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &lights[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], lights[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], lights[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], lights[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], lights[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], lights[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], lights[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], lights[0].exponent);

	camera.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0),0,0);

	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	meshList[GEO_BALL] = MeshBuilder::GenerateSphere("ball", Color(1, 1, 1), 10, 10, 1.f);
	meshList[GEO_CYLINDER] = MeshBuilder::GenerateCylinder("cylinder", Color(1, 1, 1), 20, 1.f, 1.f);
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(1, 1 ,1), 2.f);
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_TEXT]->material.kAmbient.Set(1, 0, 0);

	//GAMESTATE PAGES
	meshList[GEO_BACKGROUND] = MeshBuilder::GenerateQuad("background", Color(1, 1, 1), 2);
	meshList[GEO_BACKGROUND]->textureID = LoadTGA("Image//GAMESTATES//castle_background.tga");
	meshList[GEO_TITLE] = MeshBuilder::GenerateQuad("title", Color(1, 1, 1), 2);
	meshList[GEO_TITLE]->textureID = LoadTGA("Image//GAMESTATES//game_title.tga");
	meshList[GEO_CONTROLS] = MeshBuilder::GenerateQuad("controls", Color(1, 1, 1), 2);
	meshList[GEO_CONTROLS]->textureID = LoadTGA("Image//GAMESTATES//controls.tga");
	meshList[GEO_CREDITS] = MeshBuilder::GenerateQuad("credits", Color(1, 1, 1), 2);
	meshList[GEO_CREDITS]->textureID = LoadTGA("Image//GAMESTATES//credits.tga");

	// SCENE GUI
	meshList[GUI_PAUSE] = MeshBuilder::GenerateQuad("pauseScreen", Color(1, 1, 1));
	meshList[GUI_PAUSE]->textureID = LoadTGA("Image/GUI/PauseScreen.tga");
	meshList[GUI_BORDER] = MeshBuilder::GenerateQuad("Border", Color(1, 1, 1));
	meshList[GUI_BORDER]->textureID = LoadTGA("Image/GUI/border.tga");
	meshList[GUI_HEART] = MeshBuilder::GenerateQuad("Hearts_sprite", Color(1, 1, 1));
	meshList[GUI_HEART]->textureID = LoadTGA("Image/GUI/Hearts_Icon.tga");
	meshList[GUI_ENERGY] = MeshBuilder::GenerateQuad("Energy_Sprite", Color(1, 1, 1));
	meshList[GUI_ENERGY]->textureID = LoadTGA("Image//GUI//Energy_Icon.tga");
	meshList[GUI_CELLS] = MeshBuilder::GenerateQuad("UI_CELLS_Sprite", Color(1, 1, 1));
	meshList[GUI_CELLS]->textureID = LoadTGA("Image//GUI//normal_Cells.tga");
	meshList[GUI_ENERGYBAR] = MeshBuilder::GenerateQuad("healthbar",Color(0.0f,0.7f,0.7f));
	meshList[GUI_HEALTHBAR] = MeshBuilder::GenerateQuad("energybar",Color(0.7f,0.0f,0.0f));
	meshList[GUI_STATS_BG] = MeshBuilder::GenerateQuad("stats_bg", Color(1, 1, 1));
	meshList[GUI_STATS_BG]->textureID = LoadTGA("Image//GUI//Stats_background.tga");
	meshList[GUI_ATK_ICON] = MeshBuilder::GenerateQuad("atkicon", Color(1, 1, 1));
	meshList[GUI_ATK_ICON]->textureID = LoadTGA("Image//GUI//AtkIcon.tga");

	// TILE
	//meshList[PASSIVE_TILE] = MeshBuilder::GenerateQuad("passivetile", Color(1, 1, 1));
	//meshList[PASSIVE_TILE]->textureID = LoadTGA("Image//TILE//Stone_Brick_Tile.tga");

	meshList[GEO_STONEBRICK] = MeshBuilder::GenerateQuad("stonebrick", Color(1, 1, 1));
	meshList[GEO_STONEBRICK]->textureID = LoadTGA("Image//TILE//Stone_Brick_Tile.tga");
	meshList[GEO_BRICK] = MeshBuilder::GenerateQuad("brick", Color(1, 1, 1));
	meshList[GEO_BRICK]->textureID = LoadTGA("Image//TILE//Brick_Tile.tga");
	meshList[GEO_SPIKE] = MeshBuilder::GenerateQuad("SPIKE", Color(1, 1, 1));
	meshList[GEO_SPIKE]->textureID = LoadTGA("Image//TILE//Spikes_Tile.tga");
	meshList[GEO_PLAYER] = MeshBuilder::GenerateQuad("Player", Color(1, 1, 1));
	meshList[GEO_PLAYER]->textureID = LoadTGA("Image//Player//player.tga");

	//Weapons
	meshList[GEO_BOW] = MeshBuilder::GenerateQuad("bow", Color(1, 1, 1));
	meshList[GEO_BOW]->textureID = LoadTGA("Image//WEAPONS//bow.tga");
	meshList[GEO_STAFF] = MeshBuilder::GenerateQuad("staff", Color(1, 1, 1));
	meshList[GEO_STAFF]->textureID = LoadTGA("Image//WEAPONS//staff_blue.tga");
	meshList[GEO_PORTALGUN] = MeshBuilder::GenerateQuad("portal gun", Color(1, 1, 1));
	meshList[GEO_PORTALGUN]->textureID = LoadTGA("Image//WEAPONS//portal_gun.tga");

	//Interactables
	meshList[GEO_WEAPON_STATION] = MeshBuilder::GenerateQuad("Stone Pedastal", Color(1, 1, 1));
	meshList[GEO_WEAPON_STATION]->textureID = LoadTGA("Image//InteractiveBlocks//WeaponStation.tga");

	// Enemy
	meshList[GEO_ZOMBIE] = MeshBuilder::GenerateQuad("Zombie", Color(1, 1, 1));
	meshList[GEO_ZOMBIE]->textureID = LoadTGA("Image//Enemy//Zombie.tga");
	meshList[GEO_SKELETONARCHER] = MeshBuilder::GenerateQuad("skeleton archer", Color(1, 1, 1));
	meshList[GEO_SKELETONARCHER]->textureID = LoadTGA("Image//Enemy//skeleton.tga");
	meshList[GEO_SPIDER] = MeshBuilder::GenerateQuad("Spider", Color(1, 1, 1));
	meshList[GEO_SPIDER]->textureID = LoadTGA("Image//Enemy//spider.tga");
	meshList[GEO_NYMPH] = MeshBuilder::GenerateQuad("Nymph", Color(1, 1, 1));
	meshList[GEO_NYMPH]->textureID = LoadTGA("Image//Enemy//nymph.tga");
	meshList[GEO_TURRET] = MeshBuilder::GenerateQuad("turret", Color(1, 1, 1));
	meshList[GEO_TURRET]->textureID = LoadTGA("Image//Enemy//turret.tga");
	meshList[GEO_BOOMER] = MeshBuilder::GenerateQuad("boomer", Color(1, 1, 1));
	meshList[GEO_BOOMER]->textureID = LoadTGA("Image//Enemy//boomer.tga");

	//Weapons
	meshList[GEO_ARROW] = MeshBuilder::GenerateQuad("arrow", Color(1, 1, 1));
	meshList[GEO_ARROW]->textureID = LoadTGA("Image//PROJECTILES//arrow.tga");
	meshList[GEO_MAGICBALL] = MeshBuilder::GenerateQuad("magicball", Color(1, 1, 1));
	meshList[GEO_MAGICBALL]->textureID = LoadTGA("Image//PROJECTILES//energy_ball.tga");
	meshList[GEO_PORTAL] = MeshBuilder::GenerateQuad("portal", Color(1, 1, 1));
	meshList[GEO_PORTAL]->textureID = LoadTGA("Image//PROJECTILES//portal.tga");

	//enemy projectiles
	meshList[GEO_TURRETBULLET] = MeshBuilder::GenerateQuad("turret bullet", Color(1, 1, 1));
	meshList[GEO_TURRETBULLET]->textureID = LoadTGA("Image//PROJECTILES//turret_bullet.tga");
	

	bLightEnabled = true;
}

bool SceneBase::Update(double dt)
{
	//Keyboard Section
	if(Application::IsKeyPressed('1'))
		glEnable(GL_CULL_FACE);
	if(Application::IsKeyPressed('2'))
		glDisable(GL_CULL_FACE);
	if(Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if(Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	fps = (float)(1.f / dt);

	return true;
}

void SceneBase::RenderText(Mesh* mesh, std::string text, Color color)
{
	if(!mesh || mesh->textureID <= 0)
		return;
	
	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for(unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	
		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void SceneBase::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if(!mesh || mesh->textureID <= 0)
		return;

	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	modelStack.Translate(x, y, 0);
	modelStack.Scale(size, size, size);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);

	float accumulator = 0;
	for(unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(0.5f + accumulator, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
		accumulator += textWidth[text[i]] / 64.f;
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	modelStack.PopMatrix();
	viewStack.PopMatrix();
	projectionStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void SceneBase::RenderMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;
	
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	if(enableLight && bLightEnabled)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView = viewStack.Top() * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView.a[0]);
		
		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{	
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	if(mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render();
	if(mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void SceneBase::RenderMeshOnScreen(Mesh* mesh, float x, float y, float sizex, float sizey)
{
	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	//to do: scale and translate accordingly
	modelStack.Translate(x, y, 1);
	modelStack.Scale(sizex, sizey, 1);
	RenderMesh(mesh, false); //UI should not have light
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void SceneBase::RenderGO(GameObject* go)
{
	switch (go->type)
	{
	case GameObject::GO_BALL:
		//Exercise 4: render a sphere using scale and pos
		modelStack.PushMatrix();
		{
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z+zOffset);
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
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z + zOffset);
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
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z + zOffset);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
			SceneBase::ChangeMat(SceneBase::GEO_CYLINDER, Color(1.f, 0.f, 0.5f), 1.f, 0.6f, 0.3f, 1.f);
			RenderMesh(meshList[SceneBase::GEO_CYLINDER], true);
		}
		modelStack.PopMatrix();
		break;
	case GameObject::GO_FLIPPER:
		modelStack.PushMatrix();
		{
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z + zOffset);
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
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z + zOffset);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
			SceneBase::ChangeMat(SceneBase::GEO_CYLINDER, Color(1.f, 0.5f, 0.05f), 1.f, 0.6f, 0.3f, 1.f);
			RenderMesh(meshList[SceneBase::GEO_CYLINDER], true);
		}
		modelStack.PopMatrix();
		break;

	case GameObject::STONE_BRICK_TILE:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z + zOffset);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_STONEBRICK], false);
		modelStack.PopMatrix();
		break;


	case GameObject::BRICK_TILE:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z + zOffset);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_BRICK], false);
		modelStack.PopMatrix();
		break;
	case GameObject::SPIKE_TILE:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z + zOffset);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_SPIKE], false);
		modelStack.PopMatrix();
		break;

	case GameObject::GO_ARROW:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z + zOffset);
		modelStack.Rotate(Math::RadianToDegree(atan2f(go->normal.y, go->normal.x)), 0, 0, 1);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_ARROW], false);
		modelStack.PopMatrix();
		break;
	case GameObject::GO_MAGICBALL:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z + zOffset);
		modelStack.Rotate(Math::RadianToDegree(atan2f(go->normal.y, go->normal.x)), 0, 0, 1);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_MAGICBALL], false);
		modelStack.PopMatrix();
		break;

	case GameObject::GO_PORTAL:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z + zOffset);
		modelStack.Rotate(Math::RadianToDegree(atan2f(go->normal.y, go->normal.x)), 0, 0, 1);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_PORTAL], false);
		modelStack.PopMatrix();
		break;

	case GameObject::GO_TURRETBULLET:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y+0.7, go->pos.z + zOffset);
		modelStack.Rotate(Math::RadianToDegree(atan2f(go->normal.y, go->normal.x)), 0, 0, 1);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_TURRETBULLET], false);
		modelStack.PopMatrix();
		break;

	case GameObject::ROCK_TILE:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z + zOffset);
		modelStack.Rotate(Math::RadianToDegree((go->normal.y, go->normal.x)), 0, 0, 1);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		ChangeMat(GEO_CUBE, Color(0.7f, 0.7f, 0.7f), 1.f, 0.6f, 0.3f, 1.f);
		RenderMesh(meshList[GEO_CUBE], false);
		modelStack.PopMatrix();
		break;

	case GameObject::SOIL_TILE:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z + zOffset);
		modelStack.Rotate(Math::RadianToDegree((go->normal.y, go->normal.x)), 0, 0, 1);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		ChangeMat(GEO_CUBE, Color(1.f, 0.4f, 0.4f), 1.f, 0.6f, 0.3f, 1.f);
		RenderMesh(meshList[GEO_CUBE], false);
		modelStack.PopMatrix();
		break;

	case GameObject::GRASS_SOIL_TILE:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z + zOffset);
		modelStack.Rotate(Math::RadianToDegree(atan2f(go->normal.y, go->normal.x)), 0, 0, 1);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		ChangeMat(GEO_CUBE, Color(0.7f, 1.f, 0.f), 1.f, 0.6f, 0.3f, 1.f);
		RenderMesh(meshList[GEO_CUBE], false);
		modelStack.PopMatrix();
		break;

	case GameObject::GRASS_SOIL_FLOWERS_TILE:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z + zOffset);
		modelStack.Rotate(Math::RadianToDegree(atan2f(go->normal.y, go->normal.x)), 0, 0, 1);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		ChangeMat(GEO_CUBE, Color(0.7f, 1.f, 0.f), 1.f, 0.6f, 0.3f, 1.f);
		RenderMesh(meshList[GEO_CUBE], false);
		modelStack.PopMatrix();
		break;

	case GameObject::GO_ZOMBIE:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z + zOffset);
		if(go->vel.x < 0)
			modelStack.Rotate(180, 0, 1, 0);
		else
			modelStack.Rotate(0, 0, 1, 0);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_ZOMBIE], false);
		modelStack.PopMatrix();
		break;
	case GameObject::GO_TURRET:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z + zOffset);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_TURRET], false);
		modelStack.PopMatrix();
		break;
	}
	zOffset += 0.001f;
}

void SceneBase::ChangeMat(int idx, Color color, float ambient, float diffuse, float specular, float Shiny)
{
	meshList[idx]->material.kAmbient.Set(ambient * color.r, ambient * color.g, ambient * color.b);
	meshList[idx]->material.kDiffuse.Set(diffuse * color.r, diffuse * color.g, diffuse * color.b);
	meshList[idx]->material.kSpecular.Set(specular * color.r, specular * color.g, specular * color.b);
	meshList[idx]->material.kShininess = Shiny;
}

void SceneBase::FontLoader(std::string file_path)
{
	std::ifstream file;
	file.open(file_path);
	if (!file.is_open()) { //If file cannot be opened
		std::cout << "File can not be opened" << std::endl;
		return;
	}
	else {
		int count = 0;
		while (!file.eof()) {
			char line[256];
			file.getline(line, 256);
			sscanf_s(line, "%d", &textWidth[count++]);
		}
	}
}

void SceneBase::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Pass light
	if (lights[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(lights[0].position.x, lights[0].position.y, lights[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
}

void SceneBase::Exit()
{
	// Cleanup VBO
	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if(meshList[i])
			delete meshList[i];
	}
	glDeleteProgram(m_programID);
	glDeleteVertexArrays(1, &m_vertexArrayID);
}
