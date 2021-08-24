#include "Camera.h"
#include "Application.h"
#include "Mtx44.h"
#include "GameLevelManager.h"

Camera::Camera()
	:
	debugMode(false),
	PanningMode(false),
	position(Vector3(0,0,0)),
	target(Vector3(0,1,0)),
	up(Vector3(0,2,0)),
	right(Vector3(1,0,0)),
	maxpoint(Vector3(0,0,0)),
	offsetX(0),
	offsetY(0)
{
	Reset();
	
}

Camera::~Camera()
{
}

void Camera::Init(const Vector3& pos, const Vector3& target, const Vector3& up,
	float offsetX,float offsetY,float worldwidth, float worldheight)
{
	this->position = pos;
	this->target = target;
	this->up = up;
	this->view = (target - pos).Normalized();
	this->right = view.Cross(up);
	this->offsetX = offsetX;
	this->offsetY = offsetY;
	maxpoint.Set(worldwidth, worldheight, pos.z - 0.1);
}

void Camera::Reset()
{
	position.Set(1, 0, 0);
	target.Set(0, 0, 0);
	up.Set(0, 1, 0);
}

void Camera::Update(double dt)
{
	if (debugMode == true)
	{
		if (Application::IsKeyPressed(VK_UP))// up
		{
			position.y += 1.f;
			target.y += 1.f;
		}

		if (Application::IsKeyPressed(VK_DOWN)) // down
		{
			position.y -= 1.f;
			target.y -= 1.f;
		}
		if (Application::IsKeyPressed(VK_LEFT)) // left
		{
			position.x -= 1.f;
			target.x -= 1.f;
		}
		if (Application::IsKeyPressed(VK_RIGHT)) // right
		{
			position.x += 1.f;
			target.x += 1.f;
		}
		return;
	}
	/*
	if (player == nullptr)
		return;
	
	static Vector3 maxpoint = Vector3(GameLevelManager::GetInstance()->getcurrentLevel()->getworldWidth(),
		GameLevelManager::GetInstance()->getcurrentLevel()->getworldHeight(),
		player->pos.z);

	if ((player->pos.x > offsetX) && (player->pos.x <maxpoint.x - offsetX)) 
	{
		position.x = player->pos.x - offsetX;
		target.x = player->pos.x - offsetX;
	}
	else if (player->pos.x <= offsetX)
	{
		position.x = 0;
		target.x = 0;
	}
	else if (player->pos.x >= offsetX)
	{
		position.x = maxpoint.x - offsetX*2;
		target.x = maxpoint.x - offsetX*2;
	}

	if ((player->pos.y > offsetY) && (player->pos.y < (maxpoint.y - offsetY)))
	{
		position.y = player->pos.y - offsetY;
		target.y = player->pos.y - offsetY;
	}
	else if (player->pos.y <= offsetY)
	{
		position.y = 0;
		target.y = 0;
	}
	else if (player->pos.y >= offsetY)
	{
		position.y = maxpoint.y - offsetY*2;
		target.y = maxpoint.y - offsetY *2;
	}*/

	if (panTarget == nullptr)
		return;

	if ((panTarget->pos.x > offsetX) && (panTarget->pos.x < maxpoint.x - offsetX))
	{
		position.x = panTarget->pos.x - offsetX;
		target.x = panTarget->pos.x - offsetX;
	}
	else if (panTarget->pos.x <= offsetX)
	{
		position.x = 0;
		target.x = 0;
	}
	else if (panTarget->pos.x >= offsetX)
	{
		position.x = maxpoint.x - offsetX * 2;
		target.x = maxpoint.x - offsetX * 2;
	}

	if ((panTarget->pos.y > offsetY) && (panTarget->pos.y < (maxpoint.y - offsetY)))
	{
		position.y = panTarget->pos.y - offsetY;
		target.y = panTarget->pos.y - offsetY;
	}
	else if (panTarget->pos.y <= offsetY)
	{
		position.y = 0;
		target.y = 0;
	}
	else if (panTarget->pos.y >= offsetY)
	{
		position.y = maxpoint.y - offsetY * 2;
		target.y = maxpoint.y - offsetY * 2;
	}
}

void Camera::panToTarget(double dt,float m_speed)
{
	if (panTarget == nullptr)
		return;
	
	if (PanningMode == false)
		return;

	Vector3 camtoObj = panTarget->pos - position;
	camtoObj.z = 0;
	if (camtoObj != Vector3(0, 0, 0))
	{
		position += camtoObj.Normalized() *CAMERA_SPEED;
		target += camtoObj.Normalized() * CAMERA_SPEED;
	}
}

bool Camera::getPanningMode()
{
	return this->PanningMode;
}

void Camera::setPanning(bool PanningMode)
{
	this->PanningMode = PanningMode;
}

Vector3 Camera::getPosition()
{
	return position;
}

Vector3 Camera::getTarget()
{
	return target;
}

Vector3 Camera::getUp()
{
	return up;
}

GameObject* Camera::getpanTarget()
{
	return panTarget;
}

void Camera::setpanTarget(GameObject* panTarget)
{
	this->panTarget = panTarget;
}

void Camera::setDebugMode()
{
	debugMode = true;
}
