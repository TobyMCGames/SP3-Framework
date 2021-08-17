#ifndef SCENE_GUI_H
#define SCENE_GUI_H

#include "GameObject.h"
#include <vector>
#include "SceneBase.h"
#include "SingletonPattern.h"
#include "SceneGame.h"

class SceneGUI : public SceneBase, public SingletonPattern<SceneGUI>
{
	friend SingletonPattern<SceneGUI>;
public:

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	void renderGUI();
	bool RenderPause;

protected:
	SceneGUI();
	~SceneGUI();

	float m_worldWidth;
	float m_worldHeight;
	Color ContButton;
	Color MenuButton;
	Color QuitButton;
};

#endif