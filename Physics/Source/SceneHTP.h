#ifndef SCENE_HTP_H
#define SCENE_HTP_H

#include "GameObject.h"
#include <vector>
#include "SceneBase.h"
#include "SingletonPattern.h"

class SceneHTP : public SceneBase, public SingletonPattern<SceneHTP>
{
	friend SingletonPattern<SceneHTP>;
public:

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();


protected:
	SceneHTP();
	~SceneHTP();

	float m_worldWidth;
	float m_worldHeight;

	Color BackButton;
};

#endif