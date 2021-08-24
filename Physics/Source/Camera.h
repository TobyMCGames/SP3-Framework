#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"
#include "Player.h"
class Camera
{
private:
	const int CAMERA_SPEED = 1;
	const int PANNING_SPEED = 5.f;
	// if !panningMode panningMode == trackingmode --> use update 
	bool PanningMode;
	bool debugMode;
	GameObject* panTarget;
	Vector3 position;
	Vector3 target;
	Vector3 up;
	Vector3 view;
	Vector3 right;
	Vector3 maxpoint;
	float offsetX;
	float offsetY;
	
public:
	Camera();
	~Camera();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up,float offsetX,float offsetY, float worldwidth, float worldheight);
	virtual void Reset();
	virtual void Update(double dt);
	void panToTarget(double dt,float m_speed); 
	bool getPanningMode();
	void setPanning(bool PanningMode);
	Vector3 getPosition();
	Vector3 getTarget();
	Vector3 getUp();
	GameObject* getpanTarget();
	void setpanTarget(GameObject* panTarget=nullptr);
	void setDebugMode();
};

#endif