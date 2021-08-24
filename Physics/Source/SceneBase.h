#ifndef SCENE_BASE_H
#define SCENE_BASE_H

#include "Scene.h"
//#include "Mtx44.h"
//#include "Camera.h"
//#include "Mesh.h"
#include "MatrixStack.h"
//#include "Light.h"
#include "GameObject.h"
//#include <vector>
#include "SingletonPattern.h"
#include "KeyboardController.h"
#include "MeshRender.h"


class SceneBase : public Scene
{

public:
	
	SceneBase();
	~SceneBase();

	virtual void Init();
	virtual bool Update(double dt);
	virtual void Render();
	virtual void Exit();

	void RenderGO(GameObject *go);

	Camera* camera;
	CKeyboardController* cKeyboardController;
	MeshRender* meshRender;
	CentralMesh* centralMesh;

protected:
	//unsigned m_vertexArrayID;
	//Mesh* meshList[NUM_GEOMETRY];
	//unsigned m_programID;
	//unsigned m_parameters[U_TOTAL];
	//
	//int textWidth[256];
	//
	MS* modelStack;
	MS* viewStack;
	MS* projectionStack;
	//
	//Light lights[1];
	//
	//
	//bool bLightEnabled;

	float fps;
	float zOffset;
};

#endif