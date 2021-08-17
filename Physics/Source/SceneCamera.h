#ifndef SCENECAMERA_H
#define SCENECAMERA_H

#include "Vector3.h"
#include "SingletonPattern.h"
#include "Camera.h"

class SceneCamera :public Camera
{
public:
	Vector3 position;
	Vector3 target;
	Vector3 up;
	Vector3 view;
	Vector3 right;
	Vector3 CameraCenter;
	Vector3 maxpoint;

	SceneCamera();
	~SceneCamera();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up,float worldwidth,float worldheight);
	virtual void Reset();
	virtual void Update(double dt);
};

#endif