#include "Camera.h"
#include "Application.h"
#include "Mtx44.h"
#include "GameLevelManager.h"

Camera::Camera()
{
	Reset();
}

Camera::~Camera()
{
}

void Camera::Init(const Vector3& pos, const Vector3& target, const Vector3& up,
	float offsetX,float offsetY)
{
	this->position = pos;
	this->target = target;
	this->up = up;
	this->view = (target - pos).Normalized();
	this->right = view.Cross(up);
	this->offsetX = offsetX;
	this->offsetY = offsetY;
}

void Camera::Reset()
{
	position.Set(1, 0, 0);
	target.Set(0, 0, 0);
	up.Set(0, 1, 0);
}

void Camera::Update(double dt, Player* player)
{
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
	}
}
