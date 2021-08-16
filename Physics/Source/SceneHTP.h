#ifndef SCENE_HTP_H
#define SCENE_HTP_H

#include "GameObject.h"
#include <vector>
#include "SceneBase.h"

class SceneHTP : public SceneBase
{

public:
	SceneHTP();
	~SceneHTP();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();


protected:

	float m_worldWidth;
	float m_worldHeight;

	Color BackButton;
};

#endif