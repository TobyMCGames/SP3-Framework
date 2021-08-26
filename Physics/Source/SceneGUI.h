#ifndef SCENE_GUI_H
#define SCENE_GUI_H

#include "GameObject.h"
#include <vector>
#include "SceneBase.h"
#include "SceneGame.h"
#include "Player.h"
#include "GameLevelManager.h"
#include "Dialogue.h"

class SceneGUI : public SceneBase, public SingletonPattern<SceneGUI>
{
	friend SingletonPattern<SceneGUI>;
public:

	virtual void Init();
	virtual bool Update(double dt);
	virtual void Render();
	virtual void Destroy();
	virtual void Exit();
	void renderDialogue();
	void renderGUI();
	bool RenderPause;
	bool RenderRetry;
	bool InDialogue;
	

protected:
	SceneGUI();
	~SceneGUI();

	float m_worldWidth;
	float m_worldHeight;
	Color ContButton;
	Color RetryButton;
	Color MenuButton;
	Color QuitButton;
	Dialogue GameDialogues;
};

#endif