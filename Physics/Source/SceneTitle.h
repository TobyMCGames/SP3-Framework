#ifndef SCENE_TITLE_H
#define SCENE_TITLE_H

#include "GameObject.h"
#include <vector>
#include "SceneBase.h"

class SceneTitle : public SceneBase
{

public:
	SceneTitle();
	~SceneTitle();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();


protected:

	float m_worldWidth;
	float m_worldHeight;

	Color PlayButton;
	Color HTPButton;
	Color QuitButton;
};

#endif