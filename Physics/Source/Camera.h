#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"
#include "Player.h"
class Camera
{
private:
	const int CAMERA_SPEED = 1;

public:
	Vector3 position;
	Vector3 target;
	Vector3 up;
	Vector3 view;
	Vector3 right;
	Vector3 CameraCenter;
	float offsetX;
	float offsetY;
	Camera();
	~Camera();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up,float offsetX,float offsetY);
	virtual void Reset();
	virtual void Update(double dt,Player* player = nullptr);
	void setPlayer(float playerposx,float playerposy);
};

#endif