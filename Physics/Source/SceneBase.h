#ifndef SCENE_BASE_H
#define SCENE_BASE_H

#include "Scene.h"
#include "MatrixStack.h"
#include "GameObject.h"
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
	virtual void Destroy();
	virtual void Exit();

	void RenderGO(GameObject *go);

	Camera* camera;
	CKeyboardController* cKeyboardController;
	MeshRender* meshRender;
	CentralMesh* centralMesh;

protected:
	MS* modelStack;
	MS* viewStack;
	MS* projectionStack;

	float fps;
	float zOffset;
};

#endif