#ifndef SCENE_GUI_H
#define SCENE_GUI_H

#include "GameObject.h"
#include <vector>
#include "SceneBase.h"
#include "SceneGame.h"
#include "Player.h"
#include "GameLevelManager.h"
#include "Text.h"

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
	bool getRenderPause();
	void setRenderPause(bool RenderPause);
	bool getRenderRetry();
	void setRenderRetry(bool RenderPause);

protected:
	SceneGUI();
	~SceneGUI();

	float m_worldWidth;
	float m_worldHeight;
	Color ContButton;
	Color RetryButton;
	Color MenuButton;
	Color QuitButton;
	SpriteAnimation* Timetravel;
	Dialogue GameDialogues;
	bool RenderPause;
	bool RenderRetry;
};

#endif