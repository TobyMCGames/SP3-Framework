#ifndef SCENE_BASE_H
#define SCENE_BASE_H

#include "Scene.h"
#include "Mtx44.h"
#include "Camera.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "GameObject.h"
#include <vector>
#include "SingletonPattern.h"
#include "KeyboardController.h"

class SceneBase : public Scene
{
public:
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHTENABLED,
		U_NUMLIGHTS,
		U_LIGHT0_TYPE,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};

	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_TEXT,
		GEO_BALL,
		GEO_CUBE,
		GEO_CYLINDER,
		GEO_BACKGROUND,
		GEO_TITLE,
		GUI_BORDER,
		GUI_PAUSE,
		GUI_HEART,
		GUI_CELLS,
		GUI_ENERGY,
		GUI_HEALTHBAR,
		GUI_ENERGYBAR,
		GUI_STATS_BG,
		GUI_ATK_ICON,
		GEO_CONTROLS,
		GEO_CREDITS,
		//PASSIVE_TILE,
		GEO_BRICK,
		GEO_PLAYER,
		GEO_STONEBRICK,
		GEO_SPIKE,

		//weapons
		GEO_BOW,
		GEO_STAFF,
		GEO_PORTALGUN,

		// Enemy
		GEO_ZOMBIE,
		GEO_SKELETONARCHER,
		GEO_SPIDER,
		GEO_BOOMER,
		GEO_NYMPH,
		GEO_TURRET,
		GEO_DEMONLORD,

		//projectiles
		GEO_ARROW,
		GEO_MAGICBALL,
		GEO_PORTAL,

		NUM_GEOMETRY,
	};
public:
	SceneBase();
	~SceneBase();

	virtual void Init();
	virtual bool Update(double dt);
	virtual void Render();
	virtual void Exit();

	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderMeshOnScreen(Mesh* mesh, float x, float y, float sizex, float sizey);
	void RenderGO(GameObject *go);
	void ChangeMat(int idx, Color color, float ambient, float diffuse, float specular, float Shiny);
	void FontLoader(std::string file_path);

	Camera camera;
	CKeyboardController* cKeyboardController;

protected:
	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	int textWidth[256];

	MS modelStack;
	MS viewStack;
	MS projectionStack;

	Light lights[1];


	bool bLightEnabled;

	float fps;
};

#endif