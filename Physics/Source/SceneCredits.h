#ifndef SCENE_CREDITS_H
#define SCENE_CREDITS_H

#include "GameObject.h"
#include <vector>
#include "SceneBase.h"

class SceneCredits : public SceneBase
{

public:
	SceneCredits();
	~SceneCredits();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();


protected:

	float m_worldWidth;
	float m_worldHeight;

	Color PlayButton;
};

#endif