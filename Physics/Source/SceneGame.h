#ifndef SCENE_GAME_H
#define SCENE_GAME_H

#include "GameObject.h"
#include <vector>
#include "SceneBase.h"

class SceneGame : public SceneBase
{

public:
	SceneGame();
	~SceneGame();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();


protected:

};

#endif