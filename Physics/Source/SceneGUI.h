#ifndef SCENE_GUI_H
#define SCENE_GUI_H

#include "GameObject.h"
#include <vector>
#include "SceneBase.h"
#include "SingletonPattern.h"

class SceneGUI : public SceneBase, public SingletonPattern<SceneGUI>
{
	friend SingletonPattern<SceneGUI>;
public:

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	void renderGUI();

protected:
	SceneGUI();
	~SceneGUI();

	float m_worldWidth;
	float m_worldHeight;
	Color PlayButton;
};

#endif