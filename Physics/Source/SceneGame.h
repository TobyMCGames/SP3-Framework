#ifndef SCENE_GAME_H
#define SCENE_GAME_H

#include "GameObject.h"
#include <vector>
#include "SceneBase.h"
#include "SceneGUI.h"


class SceneGame : public SceneBase, public SingletonPattern<SceneGame>
{
	friend SingletonPattern<SceneGame>;
public:

	virtual void Init();
	virtual bool Update(double dt);
	virtual void Render();
	virtual void Destroy();
	virtual void Exit();
	void setisPaused(bool ispaused);
	bool getisPaused();

protected:
	SceneGame();
	~SceneGame();
	bool ispaused;
};

#endif