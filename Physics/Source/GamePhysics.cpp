#include "GamePhysics.h"

GamePhysics::GamePhysics()
	: gravity(Vector3(0.f, -9.8f, 0.f)),
	  collidepos(NOTHING)
{
}

GamePhysics::~GamePhysics()
{
}

void GamePhysics::Update(GameObject* go, double dt, float m_speed)
{
	go->pos += go->vel * dt * m_speed;
	go->vel += gravity * dt * m_speed;
}

bool GamePhysics::CheckCollision(GameObject* go1, GameObject* go2, double dt, float m_speed)
{
	if ((go1->active == false) || (go2->active == false))
		return false;
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
	else if ((go1->type == GameObject::GO_PLAYER  || (go1->type == GameObject::GO_PLAYERCLONE))&& (go2->type > GameObject::ENTITY_START && go2->type < GameObject::ENTITY_END))
	{
		Vector3 go1NewPos = go1->pos + go1->vel * dt * m_speed;
		//Vector3 go2NewPos = go2->pos + go2->vel * dt;
		Vector3 Check_Corner;

		// Check Bottom Right of player
		Vector3 Newbot_R = go1NewPos + Vector3(go1->scale.x / 2, -go1->scale.y / 2, 0);
		// If Move Down collides
		Check_Corner.Set(go1->pos.x + go1->scale.x / 2, Newbot_R.y, 0);
		if (abs((Check_Corner - go2->pos).Dot(Vector3(1.f, 0.f, 0.f))) < go2->scale.x / 2)
		{
			if (abs((Check_Corner - go2->pos).Dot(Vector3(0.f, 1.f, 0.f))) < go2->scale.y / 2)
			{
				go1->vel.y *= -0.05;
				if (go1->vel.y < 0.1)
				{
					go1->vel.y = 0;
				}
				return true;
			}
		}
		// If Move right collides
		Check_Corner.Set(Newbot_R.x, go1->pos.y - go1->scale.y / 2, 0);
		if (abs((Check_Corner - go2->pos).Dot(Vector3(1.f, 0.f, 0.f))) < go2->scale.x / 2)
		{
			if (abs((Check_Corner - go2->pos).Dot(Vector3(0.f, 1.f, 0.f))) < go2->scale.y / 2)
			{
				//collidepos = RIGHT;
				go1->vel.x *= -0.1;
				if (go1->vel.x < 0.1)
				{
					go1->vel.x = 0;
				}
				return true;
			}
		}
		// Check Bottom Left of player
		Vector3 Newbot_L = go1NewPos + Vector3(-go1->scale.x / 2, -go1->scale.y / 2, 0);
		// If Move Down collides
		Check_Corner.Set(go1->pos.x - go1->scale.x / 2, Newbot_L.y, 0);
		if (abs((Check_Corner - go2->pos).Dot(Vector3(1.f, 0.f, 0.f))) < go2->scale.x / 2)
		{
			if (abs((Check_Corner - go2->pos).Dot(Vector3(0.f, 1.f, 0.f))) < go2->scale.y / 2)
			{
				go1->vel.y *= -0.05;
				if (go1->vel.y < 0.1)
				{
					go1->vel.y = 0;
				}
				return true;
			}
		}
		// If Move Left collides
		Check_Corner.Set(Newbot_L.x, go1->pos.y - go1->scale.y / 2, 0);
		if (abs((Check_Corner - go2->pos).Dot(Vector3(1.f, 0.f, 0.f))) < go2->scale.x / 2)
		{
			if (abs((Check_Corner - go2->pos).Dot(Vector3(0.f, 1.f, 0.f))) < go2->scale.y / 2)
			{
				//collidepos = LEFT;
				go1->vel.x *= -0.1;
				if (go1->vel.x > -0.1)
				{
					go1->vel.x = 0;
				}
				return true;
			}
		}

		// Check Top Right of player
		Vector3 Newtop_R = go1NewPos + Vector3(go1->scale.x / 2, go1->scale.y / 2, 0);
		// If Move right collides
		Check_Corner.Set(Newtop_R.x, go1->pos.y + go1->scale.y / 2, 0);
		if (abs((Check_Corner - go2->pos).Dot(Vector3(1.f, 0.f, 0.f))) < go2->scale.x / 2)
		{
			if (abs((Check_Corner - go2->pos).Dot(Vector3(0.f, 1.f, 0.f))) < go2->scale.y / 2)
			{
				go1->vel.x *= -0.1;
				if (go1->vel.x < 0.1)
				{
					go1->vel.x = 0;
				}
				return true;
			}
		}
		// If Move Up collides
		Check_Corner.Set(go1->pos.x + go1->scale.x / 2, Newtop_R.y, 0);
		if (abs((Check_Corner - go2->pos).Dot(Vector3(1.f, 0.f, 0.f))) < go2->scale.x / 2)
		{
			if (abs((Check_Corner - go2->pos).Dot(Vector3(0.f, 1.f, 0.f))) < go2->scale.y / 2)
			{
				go1->vel.y *= 0.1;
				return true;
			}
		}

		// Check Top Left of player
		Vector3 Newtop_L = go1NewPos + Vector3(-go1->scale.x / 2, go1->scale.y / 2, 0);
		// If Move Left collides
		Check_Corner.Set(Newtop_L.x, go1->pos.y + go1->scale.y / 2, 0);
		if (abs((Check_Corner - go2->pos).Dot(Vector3(1.f, 0.f, 0.f))) < go2->scale.x / 2)
		{
			if (abs((Check_Corner - go2->pos).Dot(Vector3(0.f, 1.f, 0.f))) < go2->scale.y / 2)
			{
				//collidepos = LEFT;
				go1->vel.x *= -0.1;
				if (go1->vel.x > -0.1)
				{
					go1->vel.x = 0;
				}
				return true;
			}
		}
		// If Move Up collides
		Check_Corner.Set(go1->pos.x - go1->scale.x / 2, Newtop_L.y, 0);
		if (abs((Check_Corner - go2->pos).Dot(Vector3(1.f, 0.f, 0.f))) < go2->scale.x / 2)
		{
			if (abs((Check_Corner - go2->pos).Dot(Vector3(0.f, 1.f, 0.f))) < go2->scale.y / 2)
			{
				go1->vel.y *= 0.1;
				return true;
			}
		}
	}

	else if ((go1->type > GameObject::ENTITY_START && go1->type < GameObject::ENTITY_END) && (go2->type > GameObject::PASSIVE_TILE_START && go2->type < GameObject::PASSIVE_TILE_END))
	{
		return CheckCorner(go1, go2, dt * m_speed);
	}

	if ((go1->type > GameObject::ENTITY_START && go1->type < GameObject::ENTITY_END)&&
		(go2->type > GameObject::PROJECTILE_START && go2->type < GameObject::PROJECTILE_END))
	{

		if (AABB(go1, go2))
		{
			return true;
		}
	}
	else if ((go1->type > GameObject::PROJECTILE_START && go1->type < GameObject::PROJECTILE_END) &&
		(go2->type > GameObject::PASSIVE_TILE_START && go2->type < GameObject::PASSIVE_TILE_END))
		{
			if (DistanceCheck(go1, go2) == true)
			{
				if (AABB(go1, go2) == true)
				{
					/*GameObject* temp1 = go1;
					temp1->pos -= temp1->vel;
					GameObject* temp2 = go1;
					temp2->pos -= temp2->vel;*/
					return CheckCorner(go1,go2, dt);
				}
				else
					return false;
			}
			else
				return false;
		}
	else if ((go1->type == GameObject::GO_PLAYER || go1->type == GameObject::GO_PLAYERCLONE) &&
		(go2->type > GameObject::INTERACTABLE_START && go2->type < GameObject::INTERACTABLE_END))
	{
		if (AABB(go1, go2))
		{
			return true;
		}
	}
	else if ((go1->type > GameObject::PROJECTILE_START && go1->type < GameObject::PROJECTILE_END) &&
		(go2->type > GameObject::INTERACTABLE_START && go2->type < GameObject::INTERACTABLE_END))
	{
		if (AABB(go1, go2))
		{
			return true;
		}
	}
	return false;
}

void GamePhysics::CheckCollisionResponse(GameObject* go1, GameObject* go2, double dt, float m_speed)
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

	else if ((go1->type > GameObject::ENTITY_START && go1->type < GameObject::ENTITY_END) && (go2->type > GameObject::PASSIVE_TILE_START && go2->type < GameObject::PASSIVE_TILE_END))
	{
		go1->Response(go2);
	}
	else if ((go1->type > GameObject::ENTITY_START && go1->type < GameObject::ENTITY_END) && (go2->type > GameObject::PROJECTILE_START && go2->type < GameObject::PROJECTILE_END))
	{
		go1->Response(go2); // take damage;
		go2->Response(go1); // deactivate projectile
	}
	else if ((go1->type > GameObject::ENTITY_START && go1->type < GameObject::ENTITY_END)
		&& (go2->type > GameObject::PASSIVE_TILE_START && go2->type < GameObject::PASSIVE_TILE_END))
	{
		go1->Response(go2);
		go2->Response(go1);
	}
	// projectile -> tile
	else if ((go1->type > GameObject::PROJECTILE_START && go1->type < GameObject::PROJECTILE_END)
		&& (go2->type > GameObject::PASSIVE_TILE_START && go2->type < GameObject::PASSIVE_TILE_END))
	{
		go1->Response(go2);
	}
	else if ((go1->type == GameObject::GO_PLAYER || go1->type == GameObject::GO_PLAYERCLONE)
		&& (go2->type > GameObject::INTERACTABLE_START && go2->type < GameObject::INTERACTABLE_END))
	{
		go1->Response(go2);
		go2->Response(go1);
	}
}

bool GamePhysics::CheckCorner(GameObject* go1, GameObject* go2, double dt)
{
	Vector3 go1NewPos = go1->pos + go1->vel * dt;
	//Vector3 go2NewPos = go2->pos + go2->vel * dt;
	Vector3 Check_Corner;

	// Check Bottom Right of player
	Vector3 Newbot_R = go1NewPos + Vector3(go1->scale.x / 2, -go1->scale.y / 2, 0);
	// If Move Down collides
	Check_Corner.Set(go1->pos.x + go1->scale.x / 2, Newbot_R.y, 0);
	if (abs((Check_Corner - go2->pos).Dot(Vector3(1.f, 0.f, 0.f))) <= go2->scale.x / 2)
	{
		if (abs((Check_Corner - go2->pos).Dot(Vector3(0.f, 1.f, 0.f))) <= go2->scale.y / 2)
		{
			collidepos = DOWN;
			go1->vel.y *= -0.05;
			if (go1->vel.y < 0.1)
			{
				go1->vel.y = 0;
				go1->pos.y = go2->pos.y + ((go2->scale.y + go1->scale.y) / 2 + 0.003f);
			}
			return true;
		}
	}
	// If Move right collides
	Check_Corner.Set(Newbot_R.x, go1->pos.y - go1->scale.y / 2, 0);
	if (abs((Check_Corner - go2->pos).Dot(Vector3(1.f, 0.f, 0.f))) <= go2->scale.x / 2)
	{
		if (abs((Check_Corner - go2->pos).Dot(Vector3(0.f, 1.f, 0.f))) <= go2->scale.y / 2)
		{
			collidepos = RIGHT;
			go1->vel.x *= -0.1;
			if (go1->vel.x < 0.1)
			{
				go1->vel.x = 0;
				go1->pos.x = go2->pos.x - ((go2->scale.x + go1->scale.x) / 2 + 0.003f);
			}
			return true;
		}
	}

	// Check Bottom Left of player
	Vector3 Newbot_L = go1NewPos + Vector3(-go1->scale.x / 2, -go1->scale.y / 2, 0);
	// If Move Down collides
	Check_Corner.Set(go1->pos.x - go1->scale.x / 2, Newbot_L.y, 0);
	if (abs((Check_Corner - go2->pos).Dot(Vector3(1.f, 0.f, 0.f))) <= go2->scale.x / 2)
	{
		if (abs((Check_Corner - go2->pos).Dot(Vector3(0.f, 1.f, 0.f))) <= go2->scale.y / 2)
		{
			collidepos = DOWN;
			go1->vel.y *= -0.05;
			if (go1->vel.y < 0.1)
			{
				go1->vel.y = 0;
				go1->pos.y = go2->pos.y + ((go2->scale.y + go1->scale.y) / 2 + 0.003f);
			}
			return true;
		}
	}
	// If Move Left collides
	Check_Corner.Set(Newbot_L.x, go1->pos.y - go1->scale.y / 2, 0);
	if (abs((Check_Corner - go2->pos).Dot(Vector3(1.f, 0.f, 0.f))) <= go2->scale.x / 2)
	{
		if (abs((Check_Corner - go2->pos).Dot(Vector3(0.f, 1.f, 0.f))) <= go2->scale.y / 2)
		{
			collidepos = LEFT;
			go1->vel.x *= -0.1;
			if (go1->vel.x > -0.1)
			{
				go1->vel.x = 0;
				go1->pos.x = go2->pos.x + ((go2->scale.x + go1->scale.x) / 2 + 0.003f);
			}
			return true;
		}
	}

	// Check Top Right of player
	Vector3 Newtop_R = go1NewPos + Vector3(go1->scale.x / 2, go1->scale.y / 2, 0);
	// If Move Up collides
	Check_Corner.Set(go1->pos.x + go1->scale.x / 2, Newtop_R.y, 0);
	if (abs((Check_Corner - go2->pos).Dot(Vector3(1.f, 0.f, 0.f))) <= go2->scale.x / 2)
	{
		if (abs((Check_Corner - go2->pos).Dot(Vector3(0.f, 1.f, 0.f))) <= go2->scale.y / 2)
		{
			collidepos = UP;
			go1->vel.y *= -0.1;
			go1->pos.y = go2->pos.y - ((go2->scale.y + go1->scale.y) / 2 + 0.003f);
			return true;
		}
	}
	// If Move right collides
	Check_Corner.Set(Newtop_R.x, go1->pos.y + go1->scale.y / 2, 0);
	if (abs((Check_Corner - go2->pos).Dot(Vector3(1.f, 0.f, 0.f))) <= go2->scale.x / 2)
	{
		if (abs((Check_Corner - go2->pos).Dot(Vector3(0.f, 1.f, 0.f))) <= go2->scale.y / 2)
		{
			collidepos = RIGHT;
			float test = go1->pos.y - (go1->vel.y - gravity.y * dt);
			go1->vel.x *= -0.1;
			if (go1->vel.x < 0.1)
			{
				go1->vel.x = 0;
				go1->pos.x = go2->pos.x - ((go2->scale.x + go1->scale.x) / 2 + 0.003f);
			}
			return true;
		}
	}

	// Check Top Left of player
	Vector3 Newtop_L = go1NewPos + Vector3(-go1->scale.x / 2, go1->scale.y / 2, 0);
	Check_Corner.Set(go1->pos.x - go1->scale.x / 2, Newtop_L.y, 0);
	if (abs((Check_Corner - go2->pos).Dot(Vector3(1.f, 0.f, 0.f))) <= go2->scale.x / 2)
	{
		if (abs((Check_Corner - go2->pos).Dot(Vector3(0.f, 1.f, 0.f))) <= go2->scale.y / 2)
		{
			collidepos = UP;
			go1->vel.y *= -0.1;
			go1->pos.y = go2->pos.y - ((go2->scale.y + go1->scale.y) / 2 + 0.003f);
			return true;
		}
	}
	// If Move Left collides
	Check_Corner.Set(Newtop_L.x, go1->pos.y + go1->scale.y / 2, 0);
	if (abs((Check_Corner - go2->pos).Dot(Vector3(1.f, 0.f, 0.f))) <= go2->scale.x / 2)
	{
		if (abs((Check_Corner - go2->pos).Dot(Vector3(0.f, 1.f, 0.f))) <= go2->scale.y / 2)
		{
			collidepos = LEFT;
			go1->vel.x *= -0.1;
			if (go1->vel.x > -0.1)
			{
				go1->vel.x = 0;
				go1->pos.x = go2->pos.x + ((go2->scale.x + go1->scale.x) / 2 + 0.003f);
			}
			return true;
		}
	}
	return false;
}

GamePhysics::COLLIDEPOS GamePhysics::GetCollidePos()
{
	return collidepos;
}

bool GamePhysics::AABB(GameObject* go1, GameObject* go2)
{
	Vector3 go1min, go1max, go2min, go2max;

	go1min = go1->pos;
	go1max = go1->pos;
	go2min = go2->pos;
	go2max = go2->pos;

	go1min.x -= go1->scale.x * 0.5;
	go1min.y -= go1->scale.y * 0.5;
	go1max.x += go1->scale.x * 0.5;
	go1max.y += go1->scale.y * 0.5;
								  		  
	go2min.x -= go2->scale.x * 0.5;
	go2min.y -= go2->scale.y * 0.5;
	go2max.x += go2->scale.x * 0.5;
	go2max.y += go2->scale.y * 0.5;

	bool collisionX = go1min.x <= go2max.x && go1max.x >= go2min.x;
	bool collisionY = go1min.y <= go2max.y && go1max.y >= go2min.y;
	if (collisionX && collisionY)
	{
		std::cout << "collision happened" << std::endl;
		return true;
	}
	else
		return false;
}

bool GamePhysics::DistanceCheck(GameObject* go1, GameObject* go2)
{
	Vector3 go1_go2 = go2->pos - go1->pos; 
	if (go1_go2.LengthSquared() <= (go1->scale.x * go1->scale.x) + (go2->scale.x * go2->scale.x))
		return true;
	else
		return false;
}

// this function always checks relative to go1

GamePhysics::COLLIDEPOS GamePhysics::checkCollidePos(GameObject* go1, GameObject* go2)
{
	if (go2->pos.x >= go1->pos.x + go1->scale.x * 0.5)// right of go1 
	{
		if (go2->pos.y >= go1->pos.y + go1->scale.y * 0.5) // top right of go1
			return TOP_RIGHT;
		else if (go2->pos.y <= go1->pos.y - go1->scale.y * 0.5) // bottom right of go1
			return BOTTOM_RIGHT;
		else
			return RIGHT;
	}
	else if (go2->pos.x <= go1->pos.x - go1->scale.x * 0.5) // LEFT of go1
	{
		if (go2->pos.y >= go1->pos.y + go2->scale.y * 0.5) // top left of go1
			return TOP_LEFT;
		else if (go2->pos.y <= go1->pos.y - go1->scale.y * 0.5) // bottom left of go1
			return BOTTOM_LEFT;
		else
			return LEFT;
	}
	else if (go2->pos.y >= go1->pos.y + go1->scale.y / 2) // top of go1
		return UP;
	else if (go2->pos.y <= go1->pos.y - go1->scale.y / 2) // down of go1
		return DOWN;
}		
