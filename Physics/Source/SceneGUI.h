#ifndef SCENE_GUI_H
#define SCENE_GUI_H

#include "GameObject.h"
#include <vector>
#include "SceneBase.h"

class SceneGUI : public SceneBase
{

public:
	SceneGUI();
	~SceneGUI();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	void renderGUI();

protected:

	float m_worldWidth;
	float m_worldHeight;
	Color PlayButton;
};

#endif