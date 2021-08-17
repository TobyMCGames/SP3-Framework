#ifndef SCENE_TITLE_H
#define SCENE_TITLE_H

#include "GameObject.h"
#include <vector>
#include "SceneBase.h"

class SceneTitle : public SceneBase, public SingletonPattern<SceneTitle>
{
	friend SingletonPattern<SceneTitle>;
public:

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

protected:
	SceneTitle();
	~SceneTitle();

	float m_worldWidth;
	float m_worldHeight;

	Color PlayButton;
	Color HTPButton;
	Color CreditsButton;
	Color QuitButton;
};

#endif