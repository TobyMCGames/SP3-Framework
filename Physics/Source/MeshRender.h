#ifndef MESH_RENDER_H
#define MESH_RENDER_H

#include "Mtx44.h"
#include "Camera.h"
#include "MatrixStack.h"
#include "CentralMesh.h"
#include "Light.h"
#include <vector>
#include "SingletonPattern.h"


class MeshRender : public SingletonPattern<MeshRender>
{
	friend SingletonPattern<MeshRender>;
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

	MeshRender();
	~MeshRender();
public:

	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderAnimation(Mesh* mesh, unsigned offset, unsigned count, unsigned int numRow, unsigned int numCol, bool enableLight);
	void RenderMeshOnScreen(Mesh* mesh, float x, float y, float sizex, float sizey);

	MS* GetModelStack();
	MS* GetViewStack();
	MS* GetProjectionStack();

	Camera* GetCamera();

	Camera camera;
	CKeyboardController* cKeyboardController;

protected:
	unsigned m_vertexArrayID;
	CentralMesh* centralMesh;
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	MS modelStack;
	MS viewStack;
	MS projectionStack;

	Light lights[1];


	bool bLightEnabled;

	//float zOffset;
};

#endif