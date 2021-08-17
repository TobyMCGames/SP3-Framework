#include "SceneCamera.h"
#include "Application.h"
#include "Mtx44.h"

SceneCamera::SceneCamera()
{
	Reset();
}

SceneCamera::~SceneCamera()
{
}

void SceneCamera::Init(const Vector3& pos, const Vector3& target, const Vector3& up, float worldwidth, float worldheight)
{
	this->position = pos;
	this->target = target;
	this->up = up;
	this->view = (target - pos).Normalized();
	this->right = view.Cross(up);


	this->maxpoint = Vector3(worldwidth, worldheight, 0);
	unsigned int W = Application::GetWindowWidth();
	unsigned int H = Application::GetWindowHeight();
	this->CameraCenter.x = 80;
	this->CameraCenter.y = 45;
	
}

void SceneCamera::Reset()
{
	position.Set(5,5,5);
	target.Set(0, 0,0);
	up.Set(0, 1, 0);
}

void SceneCamera::Update(double dt)
{
	std::cout << position << std::endl;
	std::cout << CameraCenter << std::endl;
	if (Application::IsKeyPressed('A'))
	{
		if (CameraCenter.x > 80)
		{
			position -= right.Normalize();
			target -= right.Normalize();
			CameraCenter -= right.Normalize();
		}
	}
	if (Application::IsKeyPressed('D'))
	{
		if (CameraCenter.x < maxpoint.x-80)
		{
			position += right.Normalize();
			target += right.Normalize();
			CameraCenter += right.Normalize();
		}
		
	}

	if (Application::IsKeyPressed('W'))
	{
		if (CameraCenter.y < maxpoint.y-45)
		{
			position += up.Normalize();
			target += up.Normalize();
			up += up.Normalize();
			CameraCenter += up.Normalize();
		}
		
	}
	if (Application::IsKeyPressed('S'))
	{
		if (CameraCenter.y > 45)
		{
			position -= up.Normalize();
			target -= up.Normalize();
			CameraCenter -= up.Normalize();
		}
	}
	
}