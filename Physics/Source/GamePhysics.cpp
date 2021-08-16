#include "GamePhysics.h"

GamePhysics::GamePhysics()
	: gravity(Vector3(0, -9.8, 0))
{
}

GamePhysics::~GamePhysics()
{
}

void GamePhysics::Update(GameObject* go, double dt)
{
	go->pos += go->vel * dt;
	go->vel += gravity * dt;
}

bool GamePhysics::CheckCollision(GameObject* go1, GameObject* go2, double dt)
{
	if (go1->type == GameObject::GO_BALL && go2->type == GameObject::GO_BALL)
	{
		if ((go1->pos - go2->pos).LengthSquared() <= (go1->scale.x + go2->scale.x) * (go1->scale.x + go2->scale.x))
		{
			Vector3 collisionNormal = go2->pos - go1->pos;
			Vector3 DiffVel = go1->vel - go2->vel;
			if (DiffVel.Dot(collisionNormal) > 0)
				return true;
		}
	}
	else if ((go1->type == GameObject::GO_BALL && go2->type == GameObject::GO_WALL))
	{
		Vector3 N = go2->normal;
		//Flip if needed
		if ((go2->pos - go1->pos).Dot(N) < 0)
			N = -N;

		if (go2->type != GameObject::GO_FLIPPER)
		{
			if (N.Dot(go1->vel) < 0)
				return false;
		}

		Vector3 NP = Vector3(-N.y, N.x, 0);
		Vector3 w0_b1 = go2->pos - go1->pos;
		float r = go1->scale.x;
		float h_2 = go2->scale.x;
		float l_2 = go2->scale.y;

		if ((abs((w0_b1).Dot(N)) < r + h_2) &&
			abs((w0_b1).Dot(NP)) < l_2)
		{
			// collided
			std::cout << "Ball hit wall" << std::endl;
			return true;
		}
	}
	else if ((go1->type == GameObject::GO_BALL && go2->type == GameObject::GO_PILLAR))
	{
		if ((go1->pos - go2->pos).LengthSquared() <= (go1->scale.x + go2->scale.x) * (go1->scale.x + go2->scale.x))
		{
			Vector3 collisionNormal = go2->pos - go1->pos;
			if (go1->vel.Dot(collisionNormal) > 0)
				return true;
		}
	}
	else if (go1->type == GameObject::GO_BALL && go2->type == GameObject::GO_FLIPPER)
	{
		Vector3 N = go2->normal;
		//Flip if needed
		if ((go2->pos - go1->pos).Dot(N) < 0)
			N = -N;

		Vector3 NP = Vector3(-N.y, N.x, 0);
		Vector3 w0_b1 = go2->pos - go1->pos;
		float r = go1->scale.x;
		float h_2 = go2->scale.x;
		float l_2 = go2->scale.y;

		if ((abs((w0_b1).Dot(N)) < r + h_2) &&
			abs((w0_b1).Dot(NP)) < l_2)
		{
			float period = (2 * Math::PI) / Math::DegreeToRadian(go2->angularVelocity);
			float distance;
			if ((go2->pos - go2->pivot).LengthSquared() == 0)
				distance = 0;
			else
				distance = (go1->pos - go2->pivot).Dot((go2->pos - go2->pivot).Normalized());
			float speed = (2 * Math::PI * distance) / period;
			Vector3 NormalVelocity = go2->normal * speed;

			Vector3 FlipperVel_BallDir = NormalVelocity.Dot(go1->vel.Normalized()) * go1->vel.Normalized();

			Vector3 difSpeed = go1->vel - FlipperVel_BallDir;
			if (difSpeed.Length() > 0)
			{
				// collided
				std::cout << "Ball inside goal" << std::endl;
				return true;
			}
		}
	}
	else if (go1->type == GameObject::GO_BALL && go2->type == GameObject::GO_FLIPPER_PILLAR)
	{
		//Vector3 PillarNewPos = go2->pos.Rotated(go2->angularVelocity * dt * m_speed);
		//Vector3 NewBallPos = go1->pos + (go1->vel - Vector3(0, -9.8, 0) * dt * m_speed) * dt * m_speed;
		if ((go1->pos - go2->pos).LengthSquared() <= (go1->scale.x + go2->scale.x) * (go1->scale.x + go2->scale.x))
		{
			Vector3 collisionNormal = go2->pos - go1->pos;

			float period = (2 * Math::PI) / Math::DegreeToRadian(go2->angularVelocity);
			float distance = (go1->pos - go2->pivot).Dot((go2->pos - go2->pivot).Normalized());
			float speed = (2 * Math::PI * distance) / period;
			Vector3 NormalVelocity = go2->normal * speed;

			Vector3 DiffVel = go1->vel - NormalVelocity;

			if (DiffVel.Dot(collisionNormal) > 0)
				return true;

		}
	}
	return false;
}

void GamePhysics::CheckCollisionResponse(GameObject* go1, GameObject* go2, double dt)
{
	if (go1->type == GameObject::GO_BALL && go2->type == GameObject::GO_BALL)
	{
		u1 = go1->vel;
		u2 = go2->vel;
		m1 = go1->mass;
		m2 = go2->mass;

		Vector3 collisionNormal = go1->pos - go2->pos;
		float distSq = collisionNormal.LengthSquared();
		float dp = (u1 - u2).Dot(go1->pos - go2->pos);
		v1 = u1 - ((2 * m2) / (m1 + m2)) * (dp / distSq) * collisionNormal;
		v2 = u2 - ((2 * m1) / (m1 + m2)) * (dp / distSq) * -collisionNormal;

		go1->vel = v1;
		go2->vel = v2;
		std::cout << "ball & ball clashed" << std::endl;
	}
	else if ((go1->type == GameObject::GO_BALL && go2->type == GameObject::GO_WALL))
	{
		go1->vel -= 2 * go1->vel.Dot(go2->normal) * go2->normal;
	}
	else if (go1->type == GameObject::GO_BALL && go2->type == GameObject::GO_PILLAR)
	{
		Vector3 normal = (go1->pos - go2->pos).Normalized();
		go1->vel -= 2 * go1->vel.Dot(normal) * normal;
	}
	else if (go1->type == GameObject::GO_BALL && go2->type == GameObject::GO_FLIPPER)
	{
		float period = (2 * Math::PI) / Math::DegreeToRadian(go2->angularVelocity);

		float distance;
		if ((go2->pos - go2->pivot).LengthSquared() == 0)
			distance = 0;
		else
			distance = (go1->pos - go2->pivot).Dot((go2->pos - go2->pivot).Normalized());
		float speed = (2 * Math::PI * distance) / period;
		Vector3 NormalVelocity = go2->normal * speed;
		Vector3 difSpeed;
		Vector3 N = go2->normal;
		if ((go1->pos - go2->pos).Dot(go2->normal) > 0)
		{
			N = -N;
			Vector3 FlipperVel_BallDir = NormalVelocity.Dot(go1->vel.Normalized()) * go1->vel.Normalized();
			difSpeed = go1->vel - FlipperVel_BallDir;
		}
		else
		{
			difSpeed = go1->vel - NormalVelocity;
		}

		go1->vel -= 2 * difSpeed.Dot(N) * N;
	}
	else if (go1->type == GameObject::GO_BALL && go2->type == GameObject::GO_FLIPPER_PILLAR)
	{
		float period = (2 * Math::PI) / Math::DegreeToRadian(go2->angularVelocity);
		float distance = (go2->pos - go2->pivot).Length();
		float speed = (2 * Math::PI * distance) / period;
		Vector3 NormalVelocity = go2->normal * speed;
		Vector3 CollisionNormal = (go1->pos - go2->pos).Normalized();


		Vector3 FlipperVel_BallDir = NormalVelocity.Dot(CollisionNormal) * CollisionNormal;
		Vector3 difSpeed = go1->vel - FlipperVel_BallDir;

		go1->vel -= 2 * difSpeed.Dot(CollisionNormal) * CollisionNormal;

	}
	return;
}
