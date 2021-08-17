#include "Camera.h"
#include "Application.h"
#include "Mtx44.h"
#include "Player.h"

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

	if ((player->pos.x > offsetX) && (player->pos.x < player->getmaxpoint().x - offsetX))
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
		position.x = player->getmaxpoint().x - offsetX*2;
		target.x = player->getmaxpoint().x - offsetX*2;
	}

	if ((player->pos.y > offsetY) && (player->pos.y < (player->getmaxpoint().y - offsetY)))
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
		position.y = player->getmaxpoint().y - offsetY*2;
		target.y = player->getmaxpoint().y - offsetY *2;
	}
		


	/*if (player->pos.x < maxpoint.x - offsetX)
	{
		position += right.Normalize() * CAMERA_SPEED;
		target += right.Normalize() * CAMERA_SPEED;
	//	CameraCenter += right.Normalize() * CAMERA_SPEED;
	}


	if (player->pos.y < maxpoint.y - offsetY)
	{
		position += up.Normalize() * CAMERA_SPEED;
		target += up.Normalize() * CAMERA_SPEED;
		up += up.Normalize() *CAMERA_SPEED;
		//CameraCenter += up.Normalize() * CAMERA_SPEED;
	}


	if (player->pos.y > offsetY)
	{
		position -= up.Normalize() * CAMERA_SPEED;
		target -= up.Normalize() * CAMERA_SPEED;
		//CameraCenter -= up.Normalize() * CAMERA_SPEED;
	}
	
	*/

	/*if (player->pos.x > offsetX) // left 
	{
		float diff = player->pos.x - offsetX;
		position -= player->pos.x;
		target -= right.Normalize() * CAMERA_SPEED;
		//CameraCenter -= right.Normalize() * CAMERA_SPEED;
	}

	if (player->pos.x < maxpoint.x - offsetX) // right
	{
		float diff = (maxpoint.x - offsetX) - player->pos.x;
		position += right.Normalize() * CAMERA_SPEED;
		target += right.Normalize() * CAMERA_SPEED;
	}


	if (player->pos.y < maxpoint.y - offsetY) // up
	{
		float diff = (maxpoint.y - offsetY) - player->pos.y;
		position = player->pos.y;
		target += up.Normalize() * CAMERA_SPEED;
		up += up.Normalize() * CAMERA_SPEED;
	}


	if (player->pos.y > offsetY) // down
	{
		float diff = player->pos.y - offsetY;
		position = player->pos.y;
		target -= up.Normalize() * CAMERA_SPEED;
	}*/
}

void Camera::setPlayer(float playerposx, float playerposy)
{
	CameraCenter.Set(playerposx, playerposy, 0);
}
