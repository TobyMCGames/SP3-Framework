#include "Camera.h"
#include "Application.h"
#include "Mtx44.h"

Camera::Camera()
{
	Reset();
}

Camera::~Camera()
{
}

void Camera::Init(const Vector3& pos, const Vector3& target, const Vector3& up,float worldwidth,float worldheight,
	float offsetX,float offsetY)
{
	this->position = pos;
	this->target = target;
	this->up = up;
	this->view = (target - pos).Normalized();
	this->right = view.Cross(up);


	this->maxpoint = Vector3(worldwidth, worldheight, 0);
	unsigned int W = Application::GetWindowWidth();
	unsigned int H = Application::GetWindowHeight();
	this->CameraCenter.x = offsetX;
	this->CameraCenter.y = offsetY;
	this->offsetX = offsetX;
	this->offsetY = offsetY;
}

void Camera::Reset()
{
	position.Set(1, 0, 0);
	target.Set(0, 0, 0);
	up.Set(0, 1, 0);
}

void Camera::Update(double dt)
{
	if (Application::IsKeyPressed('A'))
	{
		if (CameraCenter.x > offsetX)
		{
			position -= right.Normalize();
			target -= right.Normalize();
			CameraCenter -= right.Normalize();
		}
	}
	if (Application::IsKeyPressed('D'))
	{
		if (CameraCenter.x < maxpoint.x - offsetX)
		{
			position += right.Normalize();
			target += right.Normalize();
			CameraCenter += right.Normalize();
		}

	}

	if (Application::IsKeyPressed('W'))
	{
		if (CameraCenter.y < maxpoint.y - offsetY)
		{
			position += up.Normalize();
			target += up.Normalize();
			up += up.Normalize();
			CameraCenter += up.Normalize();
		}

	}
	if (Application::IsKeyPressed('S'))
	{
		if (CameraCenter.y > offsetY)
		{
			position -= up.Normalize();
			target -= up.Normalize();
			CameraCenter -= up.Normalize();
		}
	}
}