#ifndef SCENE_GAME_H
#define SCENE_GAME_H

#include "GameObject.h"
#include <vector>
#include "SceneBase.h"
#include "SceneGUI.h"
#include "SingletonPattern.h"
#include "SceneGUI.h"

class SceneGame : public SceneBase, public SingletonPattern<SceneGame>
{
	friend SingletonPattern<SceneGame>;
public:

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	bool ispaused;

protected:
	SceneGame();
	~SceneGame();
};

#endif