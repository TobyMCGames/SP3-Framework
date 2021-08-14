#include "SceneCollision.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>

SceneCollision::SceneCollision() :
shape(NULL),
start(NULL),
ball(NULL),
levelCompleted(false)
{
}

SceneCollision::~SceneCollision()
{
}

void SceneCollision::Init()
{
	SceneBase::Init();

	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	//Physics code here
	m_speed = 2.7f;

	m_objectCount = 0;

	//Player Here
	player.SetCapacity(500);

	Math::InitRNG();

	//Exercise 1: initialize m_objectCount

	m_ghost = new GameObject(GameObject::GO_BALL);
	m_ghost->active = false;

	level1();
}

GameObject* SceneCollision::FetchGO()
{
	//Exercise 2a: implement FetchGO()
	for (std::vector<GameObject*>::iterator it = m_goList.begin(); it != m_goList.end(); it++)
	{
		GameObject* go = (GameObject*)*it;
		if (go->active == false)
		{
			go->active = true;
			//Exercise 2b: increase object count every time an object is set to active
			m_objectCount++;
			return go;
		}
	}
	for (int i = 0; i < 10; i++)
	{
		m_goList.push_back(new GameObject(GameObject::GO_BALL));
	}
	//Exercise 2b: increase object count every time an object is set to active
	m_goList.back()->active = true;
	m_objectCount++;
	return m_goList.back();
}

void SceneCollision::ReturnGO(GameObject *go)
{
	//Exercise 3: implement ReturnGO()
	go->active = false;
	m_objectCount--;
}

bool SceneCollision::CheckCollision(GameObject* go1, GameObject* go2, float dt)
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
	else if ((go1->type == GameObject::GO_BALL && go2->type == GameObject::GO_WALL) ||
		(go1->type == GameObject::GO_BALL && go2->type == GameObject::GO_NONELASTIC_WALL) ||
		(go1->type == GameObject::GO_BALL && go2->type == GameObject::GO_DISPENSER))
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
	else if ((go1->type == GameObject::GO_BALL && go2->type == GameObject::GO_PILLAR) ||
		(go1->type == GameObject::GO_BALL && go2->type == GameObject::GO_NONELASTIC_PILLAR) ||
		(go1->type == GameObject::GO_BALL && go2->type == GameObject::GO_BOUNCER))
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
	else if (go1->type == GameObject::GO_BALL && go2->type == GameObject::GO_GOAL)
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

		if ((abs((w0_b1).Dot(N)) < h_2 - r) &&
			abs((w0_b1).Dot(NP)) < l_2)
		{
			// collided
			std::cout << "Ball inside goal" << std::endl;
			return true;
		}
	}
	return false;
}

void SceneCollision::CheckCollisionResponse(GameObject* go1, GameObject* go2, float dt)
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
	else if ((go1->type == GameObject::GO_BALL && go2->type == GameObject::GO_WALL) ||
		(go1->type == GameObject::GO_BALL && go2->type == GameObject::GO_DISPENSER))
	{
		go1->vel -= 2 * go1->vel.Dot(go2->normal) * go2->normal;
	}
	else if (go1->type == GameObject::GO_BALL && go2->type == GameObject::GO_PILLAR)
	{
		Vector3 normal = (go1->pos - go2->pos).Normalized();
		go1->vel -= 2 * go1->vel.Dot(normal) * normal;
	}
	else if (go1->type == GameObject::GO_BALL && go2->type == GameObject::GO_NONELASTIC_WALL)
	{
		go1->vel -= 2 * go1->vel.Dot(go2->normal) * go2->normal;
		go1->vel *= 0.8;
	}
	else if (go1->type == GameObject::GO_BALL && go2->type == GameObject::GO_NONELASTIC_PILLAR)
	{
		Vector3 normal = (go1->pos - go2->pos).Normalized();
		go1->vel -= 2 * go1->vel.Dot(normal) * normal;
		go1->vel *= 0.8;
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
	else if (go1->type == GameObject::GO_BALL && go2->type == GameObject::GO_BOUNCER)
	{
		Vector3 normal = (go1->pos - go2->pos).Normalized();
		go1->vel -= 2 * go1->vel.Dot(normal) * normal;
		go1->vel *= 1.3;
	}
	else if (go1->type == GameObject::GO_BALL && go2->type == GameObject::GO_GOAL)
	{
		std::cout << "You Win" << std::endl;
		levelCompleted = true;
	}
	return;
}

void SceneCollision::MakePillar(float x, float y, float thickness, GameObject::GAMEOBJECT_TYPE type)
{
	GameObject* go = FetchGO();
	go->type = type;
	go->active = true;
	go->pos.Set(x, y, 0);
	go->scale.Set(thickness, thickness, thickness);
	if (shape != NULL)
		shape->push_back(go);
}

void SceneCollision::MakeThinWall(float x, float y, float angleDeg, float thickness, float height)
{
	GameObject* go = FetchGO();
	go->type = GameObject::GO_NONELASTIC_WALL;
	go->active = true;
	go->pos.Set(x, y, 0);
	go->normal.Set(cosf(Math::DegreeToRadian(angleDeg)), sinf(Math::DegreeToRadian(angleDeg)), 0);
	go->scale.Set(thickness, height, 1.f);

	MakePillar(
		go->pos.x - height * sinf(Math::DegreeToRadian(angleDeg)),
		go->pos.y + height * cosf(Math::DegreeToRadian(angleDeg)),
		thickness,
		GameObject::GO_NONELASTIC_PILLAR);

	MakePillar(
		go->pos.x + height * sinf(Math::DegreeToRadian(angleDeg)),
		go->pos.y - height * cosf(Math::DegreeToRadian(angleDeg)),
		thickness,
		GameObject::GO_NONELASTIC_PILLAR);
}

void SceneCollision::MakeThickWall(float x, float y, float angleDeg, float thickness, float height)
{
	angleDeg = Math::DegreeToRadian(angleDeg);

	GameObject* go = FetchGO();
	go->type = GameObject::GO_NONELASTIC_WALL;
	go->active = true;
	go->pos.Set(x, y);
	go->normal.Set(cosf(angleDeg), sinf(angleDeg), 0);
	go->scale.Set(thickness, height, 1.f);

	GameObject* go2 = FetchGO();
	go2->type = GameObject::GO_NONELASTIC_WALL;
	go2->active = true;
	go2->pos.Set(x, y);
	go2->normal.Set(sinf(-angleDeg), cosf(-angleDeg), 0);
	go2->scale.Set(height, thickness, 1.f);

	MakePillar(x + (thickness - 0.0005f) * cosf(angleDeg) - (height + 0.0005f) * sinf(angleDeg),
		y + (height - 0.0005f) * cosf(angleDeg) + (thickness + 0.0005f) * sinf(angleDeg),
		0.1f,
		GameObject::GO_NONELASTIC_PILLAR);
	MakePillar(x + (-thickness + 0.0005f) * cosf(angleDeg) - (height + 0.0005f) * sinf(angleDeg),
		y + (height - 0.0005f) * cosf(angleDeg) + (-thickness - 0.0005f) * sinf(angleDeg),
		0.1f,
		GameObject::GO_NONELASTIC_PILLAR);
	MakePillar(x + (thickness - 0.0005f) * cosf(angleDeg) - (-height - 0.0005f) * sinf(angleDeg),
		y + (-height + 0.0005f) * cosf(angleDeg) + (thickness - 0.0005f) * sinf(angleDeg),
		0.1f,
		GameObject::GO_NONELASTIC_PILLAR);
	MakePillar(x + (-thickness + 0.0005f) * cosf(angleDeg) - (-height + 0.0005f) * sinf(angleDeg),
		y + (-height + 0.0005f) * cosf(angleDeg) + (-thickness + 0.0005f) * sinf(angleDeg),
		0.1f,
		GameObject::GO_NONELASTIC_PILLAR);
}

void SceneCollision::MakeFlipper(float x, float y,Vector3 pivotPos, float defaultAngle, float angleSpeed, float thickness, float height)
{
	GameObject* go = FetchGO();
	go->type = GameObject::GO_FLIPPER;
	go->pivot = pivotPos;
	go->scale.Set(thickness, height, thickness);
	go->normal = Vector3(0, 1, 0).Rotate(defaultAngle);
	go->angularVelocity = angleSpeed;
	
	Vector3 PivToPos = Vector3(x, y, 0) - pivotPos;
	float angle = Math::DegreeToRadian(defaultAngle);
	go->pos.Set(
		x,
		y,
		0
	);

	go = FetchGO();
	go->type = GameObject::GO_FLIPPER_PILLAR;
	go->pivot = pivotPos;
	go->scale.Set(thickness, thickness, thickness);
	go->normal = Vector3(0, 1, 0).Rotate(defaultAngle);
	go->angularVelocity = angleSpeed;
	go->pos.Set(
		x + height * cos(angle),
		y + height * sin(angle),
		0
	);

	go = FetchGO();
	go->type = GameObject::GO_FLIPPER_PILLAR;
	go->pivot = pivotPos;
	go->scale.Set(thickness, thickness, thickness);
	go->normal = Vector3(0, 1, 0).Rotate(defaultAngle);
	go->angularVelocity = angleSpeed;
	go->pos.Set(
		x + -height * cos(angle),
		y + -height * sin(angle),
		0
	);
}

void SceneCollision::Update(double dt)
{
	SceneBase::Update(dt);
	
	if (!levelCompleted)
	{
		if (Application::IsKeyPressed('9'))
		{
			m_speed = Math::Max(0.f, m_speed - 0.1f);
		}
		if (Application::IsKeyPressed('0'))
		{
			m_speed += 0.1f;
		}
		if (Application::IsKeyPressed('R'))
		{
			if (shape_list.size() > 0)
			{
				int listSize = shape_list.size();
				for (int i = 0; i < listSize; i++)
				{
					std::vector<GameObject*>* last_Shape = shape_list.back();
					int size = last_Shape->size();
					for (int j = 0; j < size; j++)
					{
						GameObject* go = last_Shape->back();
						go->active = false;
						last_Shape->back() = NULL;
						last_Shape->pop_back();
						m_objectCount--;
					}
					shape_list.back() = NULL;
					shape_list.pop_back();
					ShapeCount--;
					player.CleanInk(LastInkCost.back());
					LastInkCost.pop_back();
				}
			}
			player.SetCapacity(500);
			if (ball != NULL)
			{
				ball->active = false;
				ball = NULL;
			}
		}
		//Changing Material
		static bool EbuttonState = false;
		if (Application::IsKeyPressed('E') && !EbuttonState)
		{
			EbuttonState = true;
			player.ChangeMat(1);
		}
		else if (!Application::IsKeyPressed('E') && EbuttonState)
		{
			EbuttonState = false;
		}
		//Mouse Section
		double x, y;
		Application::GetCursorPos(&x, &y);
		unsigned w = Application::GetWindowWidth();
		unsigned h = Application::GetWindowHeight();
		double PosX = (x / w) * m_worldWidth;
		double PosY = m_worldHeight - (y / h) * m_worldHeight;
		static bool bLButtonState = false;
		if (!bLButtonState && Application::IsMousePressed(0))
		{
			bLButtonState = true;
			std::cout << "LBUTTON DOWN" << std::endl;

			m_ghost->active = true;
			m_ghost->type = GameObject::GO_BALL;
			m_ghost->pos.x = PosX;
			m_ghost->pos.y = PosY;
			m_ghost->scale.Set(2, 2, 2);
		}
		else if (bLButtonState && !Application::IsMousePressed(0))
		{
			bLButtonState = false;
			std::cout << "LBUTTON UP" << std::endl;

			//Exercise 6: spawn small GO_BALL
			m_ghost->active = false;
			GameObject* go = FetchGO();
			go->type = GameObject::GO_BALL;
			go->pos = m_ghost->pos;
			go->vel = m_ghost->pos - Vector3(PosX, PosY, 0);
			go->scale = m_ghost->scale;
			go->mass = go->scale.x * go->scale.x * go->scale.x;
		}
		static bool bRButtonState = false;
		if (Application::IsMousePressed(1))
		{
			if (!bRButtonState) {
				bRButtonState = true;
				std::cout << "RBUTTON DOWN" << std::endl;
				start.x = PosX;
				start.y = PosY;
				if (shape == NULL)
				{
					shape = new std::vector<GameObject*>;
				}
			}
			if (!m_ghost->active)
			{
				if (player.GetInkAmount() > 0)
				{
					if ((Vector3(PosX, PosY, 0) - start).LengthSquared() > Math::Square(MIN_LINE_LENGTH))
					{
						//shape = new std::vector<GameObject*>;

						switch (player.GetCurrentMat())
						{
						case PlayerA2::ELASTIC:
						case PlayerA2::NON_ELASTIC:
							if (player.UseInk(player.GetInkCost()))
							{
								if (player.GetCurrentMat() == PlayerA2::ELASTIC)
								{
									MakePillar(
										start.x,
										start.y,
										LINE_THICKNESS,
										GameObject::GO_PILLAR);
									m_ghost->type = GameObject::GO_WALL;
								}
								else
								{
									MakePillar(
										start.x,
										start.y,
										LINE_THICKNESS,
										GameObject::GO_NONELASTIC_PILLAR);
									m_ghost->type = GameObject::GO_NONELASTIC_WALL;
								}
								CurInkCost += player.GetInkCost();
							}
							m_ghost->active = true;
							break;
						}
					}
				}
			}
			else
			{
				Vector3 line = Vector3(PosX, PosY, 0) - start;
				if (player.GetCurrentMat() == PlayerA2::ELASTIC || player.GetCurrentMat() == PlayerA2::NON_ELASTIC)
				{
					m_ghost->normal = (line.Cross(Vector3(0, 0, 1))).Normalized();
					if (player.GetInkAmount() >= (line.Length() / LINE_THICKNESS))
					{
						m_ghost->scale.Set(LINE_THICKNESS, line.Length() / 2, 1);
						m_ghost->pos.x = start.x + line.x / 2;
						m_ghost->pos.y = start.y + line.y / 2;
					}
					else
					{
						m_ghost->scale.Set(LINE_THICKNESS, player.GetInkAmount() * LINE_THICKNESS, 1);
						line.Normalize();
						line *= player.GetInkAmount() * LINE_THICKNESS;
						m_ghost->pos.x = start.x + line.x / 2;
						m_ghost->pos.y = start.y + line.y / 2;
					}

					if ((Vector3(PosX, PosY, 0) - m_ghost->pos).LengthSquared() > Math::Square(MAX_LINE_LENGTH))
					{
						if (player.UseInk(m_ghost->scale.y * player.GetInkCost()))
						{
							GameObject* go = FetchGO();
							go->active = true;
							go->type = m_ghost->type;
							go->pos = m_ghost->pos;
							go->scale = m_ghost->scale;
							go->normal = m_ghost->normal;
							go->mass = go->scale.x * go->scale.y * go->scale.z;
							shape->push_back(go);

							CurInkCost += m_ghost->scale.y * player.GetInkCost();
						}

						//Reset m_ghost position
						m_ghost->active = false;
						start.Set(PosX, PosY, 0);
					}
				}
			}

		}
		else if (bRButtonState && !Application::IsMousePressed(1))
		{
			bRButtonState = false;
			std::cout << "RBUTTON UP" << std::endl;

			if (m_ghost->active)
			{
				if (player.GetCurrentMat() == PlayerA2::ELASTIC || player.GetCurrentMat() == PlayerA2::NON_ELASTIC)
				{
					if (player.UseInk(m_ghost->scale.y * player.GetInkCost()))
					{
						m_ghost->active = false;
						GameObject* go = FetchGO();
						go->active = true;
						go->type = m_ghost->type;
						go->pos = m_ghost->pos;
						go->scale = m_ghost->scale;
						go->normal = m_ghost->normal;
						go->mass = go->scale.x * go->scale.y * go->scale.z;
						shape->push_back(go);

						CurInkCost += m_ghost->scale.y * player.GetInkCost();
					}
					if (player.UseInk(player.GetInkCost()))
					{
						if (player.GetCurrentMat() == PlayerA2::ELASTIC)
						{
							MakePillar(
								PosX,
								PosY,
								LINE_THICKNESS,
								GameObject::GO_PILLAR);
						}
						else
						{
							MakePillar(
								PosX,
								PosY,
								LINE_THICKNESS,
								GameObject::GO_NONELASTIC_PILLAR);
						}
						CurInkCost += player.GetInkCost();
					}
				}
			}
			else
			{
				if (player.GetCurrentMat() == PlayerA2::ELASTIC || player.GetCurrentMat() == PlayerA2::NON_ELASTIC)
				{
					if (player.UseInk(player.GetInkCost()))
					{
						if (player.GetCurrentMat() == PlayerA2::ELASTIC)
						{
							MakePillar(
								start.x,
								start.y,
								LINE_THICKNESS,
								GameObject::GO_PILLAR);
						}
						else
						{
							MakePillar(
								start.x,
								start.y,
								LINE_THICKNESS,
								GameObject::GO_NONELASTIC_PILLAR);
						}
						CurInkCost += player.GetInkCost();
					}
				}
			}
			shape_list.push_back(shape);
			shape = NULL;
			ShapeCount++;
			LastInkCost.push_back(CurInkCost);
			CurInkCost = 0;
		}

		// ball Spawn
		if (Application::IsKeyPressed(VK_SPACE))
		{
			if (ball == NULL)
			{
				ball = FetchGO();
				ball->type = GameObject::GO_BALL;
				ball->vel.SetZero();
				ball->vel += spawner->normal.Rotated(-90) * DISPENSER_FORCE;
				ball->pos = spawner->pos;
				ball->scale.Set(2, 2, 2);
			}
		}

		// Erase Last Shape
		static bool RButtonState = false;
		if (Application::IsKeyPressed('Q') && !RButtonState)
		{
			RButtonState = true;
			if (shape_list.size() > 0)
			{
				std::vector<GameObject*>* last_Shape = shape_list.back();
				int size = last_Shape->size();
				for (int i = 0; i < size; i++)
				{
					GameObject* go = last_Shape->back();
					go->active = false;
					last_Shape->back() = NULL;
					last_Shape->pop_back();
					m_objectCount--;
				}
				shape_list.back() = NULL;
				shape_list.pop_back();
				ShapeCount--;
				player.CleanInk(LastInkCost.back());
				LastInkCost.pop_back();
			}
		}
		else if (!Application::IsKeyPressed('Q') && RButtonState)
		{
			RButtonState = false;
		}

		//Physics Simulation Section

		for (std::vector<GameObject*>::iterator it = m_goList.begin(); it != m_goList.end(); it++)
		{
			GameObject* go = (GameObject*)*it;
			if (go->active)
			{
				//Exercise 7: handle out of bound game objects
				if (go->pos.x < 0 || go->pos.x > m_worldWidth ||
					go->pos.y < 0 || go->pos.y > m_worldHeight)
				{
					ReturnGO(go);
					if (go == ball)
					{
						ball = NULL;
					}
					continue;
				}
				//Exercise 8a: handle collision between GO_BALL and GO_BALL using velocity swap
				for (std::vector<GameObject*>::iterator it2 = it + 1; it2 != m_goList.end(); it2++)
				{
					GameObject* go2 = (GameObject*)*it2;
					if (go == go2)
					{
						continue;
					}
					if (go2->active)
					{
						GameObject* ball = go;
						GameObject* other = go2;
						if (ball->type != GameObject::GO_BALL) {
							ball = go2;
							other = go;
						}
						if (CheckCollision(ball, other, dt) == true) {
							CheckCollisionResponse(ball, other, dt);
						}
					}
				}


				//Exercise 8b: store values in auditing variables

				//Exercise 10: handle collision using momentum swap instead

				//Exercise 12: improve inner loop to prevent double collision

				//Exercise 13: improve collision detection algorithm [solution to be given later] 

				if (go->type == GameObject::GO_BALL)
				{
					go->pos += go->vel * dt * m_speed;
					go->vel.y -= 9.8f * dt * m_speed;
					go->vel -= go->vel * 5 / 100 * dt * m_speed;
				}
				else if (go->type == GameObject::GO_FLIPPER || go->type == GameObject::GO_FLIPPER_PILLAR)
				{
					float angle = go->angularVelocity * dt * m_speed;
					Vector3 PivToPos = go->pos - go->pivot;
					PivToPos.Rotate(angle);
					go->pos.Set(
						go->pivot.x + PivToPos.x,
						go->pivot.y + PivToPos.y,
						0
					);

					go->normal.Rotate(angle);
				}
			}
		}
	}
	else
	{
		if (Application::IsKeyPressed(VK_RETURN))
		{
			levelCompleted = false;
			curLevel++;
			if (shape_list.size() > 0)
			{
				int listSize = shape_list.size();
				for (int i = 0; i < listSize; i++)
				{
					std::vector<GameObject*>* last_Shape = shape_list.back();
					int size = last_Shape->size();
					for (int j = 0; j < size; j++)
					{
						GameObject* go = last_Shape->back();
						go->active = false;
						last_Shape->back() = NULL;
						last_Shape->pop_back();
						m_objectCount--;
					}
					shape_list.back() = NULL;
					shape_list.pop_back();
					ShapeCount--;
					player.CleanInk(LastInkCost.back());
					LastInkCost.pop_back();
				}
			}
			player.SetCapacity(500);
			if (ball != NULL)
			{
				ball->active = false;
				ball = NULL;
			}
			ResetList();
			switch (curLevel)
			{
			case 1:
				level1();
				break;
			case 2:
				level2();
				break;
			case 3:
				level3();
				break;
			}
		}
	}
}


void SceneCollision::RenderGO(GameObject *go)
{
	switch(go->type)
	{
	case GameObject::GO_BALL:
		//Exercise 4: render a sphere using scale and pos
		modelStack.PushMatrix();
		{
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
			SceneBase::ChangeMat(SceneBase::GEO_BALL, Color(1, 1, 1), 1, 0.6, 0.3, 1);
			RenderMesh(meshList[SceneBase::GEO_BALL], true);
		}
		modelStack.PopMatrix();
		//Exercise 11: think of a way to give balls different colors
		break;
	case GameObject::GO_WALL:
		modelStack.PushMatrix();
		{
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Rotate(Math::RadianToDegree(atan2f(go->normal.y, go->normal.x)), 0, 0, 1);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
			SceneBase::ChangeMat(SceneBase::GEO_CUBE, Color(1, 0, 0.5), 1, 0.6, 0.3, 1);
			RenderMesh(meshList[SceneBase::GEO_CUBE], true);
		}
		modelStack.PopMatrix();
		break;
	case GameObject::GO_PILLAR:
		modelStack.PushMatrix();
		{
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
			SceneBase::ChangeMat(SceneBase::GEO_CYLINDER, Color(1, 0, 0.5), 1, 0.6, 0.3, 1);
			RenderMesh(meshList[SceneBase::GEO_CYLINDER], true);
		}
		modelStack.PopMatrix();
		break;
	case GameObject::GO_NONELASTIC_WALL:
		modelStack.PushMatrix();
		{
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Rotate(Math::RadianToDegree(atan2f(go->normal.y, go->normal.x)), 0, 0, 1);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
			SceneBase::ChangeMat(SceneBase::GEO_CUBE, Color(1, 1, 1), 1, 0.6, 0.3, 1);
			RenderMesh(meshList[SceneBase::GEO_CUBE], true);
		}
		modelStack.PopMatrix();
		break;
	case GameObject::GO_NONELASTIC_PILLAR:
		modelStack.PushMatrix();
		{
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
			SceneBase::ChangeMat(SceneBase::GEO_CYLINDER, Color(1, 1, 1), 1, 0.6, 0.3, 1);
			RenderMesh(meshList[SceneBase::GEO_CYLINDER], true);
		}
		modelStack.PopMatrix();
		break;
	case GameObject::GO_FLIPPER:
		modelStack.PushMatrix();
		{
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Rotate(Math::RadianToDegree(atan2f(go->normal.y, go->normal.x)), 0, 0, 1);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
			SceneBase::ChangeMat(SceneBase::GEO_CUBE, Color(1, 0.5, 0.05), 1, 0.6, 0.3, 1);
			RenderMesh(meshList[SceneBase::GEO_CUBE], true);
		}
		modelStack.PopMatrix();
		break;
	case GameObject::GO_FLIPPER_PILLAR:
		modelStack.PushMatrix();
		{
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
			SceneBase::ChangeMat(SceneBase::GEO_CYLINDER, Color(1, 0.5, 0.05), 1, 0.6, 0.3, 1);
			RenderMesh(meshList[SceneBase::GEO_CYLINDER], true);
		}
		modelStack.PopMatrix();
		break;
	case GameObject::GO_BOUNCER:
		modelStack.PushMatrix();
		{
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
			SceneBase::ChangeMat(SceneBase::GEO_CYLINDER, Color(1, 1, 0), 1, 0.6, 0.3, 1);
			RenderMesh(meshList[SceneBase::GEO_CYLINDER], true);
		}
		modelStack.PopMatrix();
		break;
	case GameObject::GO_DISPENSER:
		modelStack.PushMatrix();
		{
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Rotate(Math::RadianToDegree(atan2f(go->normal.y, go->normal.x)), 0, 0, 1);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
			SceneBase::ChangeMat(SceneBase::GEO_CUBE, Color(0.7, 0.7, 0.7), 1, 0.6, 0.3, 1);
			RenderMesh(meshList[SceneBase::GEO_CUBE], true);
		}
		modelStack.PopMatrix();
		break;
	case GameObject::GO_GOAL:
		modelStack.PushMatrix();
		{
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Rotate(Math::RadianToDegree(atan2f(go->normal.y, go->normal.x)), 0, 0, 1);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
			
			SceneBase::ChangeMat(SceneBase::GEO_CUBE, Color(0.5, 0.5, 1), 1, 0.6, 0.3, 1);
			RenderMesh(meshList[SceneBase::GEO_CUBE], true);
		}
		modelStack.PopMatrix();
		break;
	}
}

void SceneCollision::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	// Projection matrix : Orthographic Projection
	Mtx44 projection;
	projection.SetToOrtho(0, m_worldWidth, 0, m_worldHeight, -10, 10);
	projectionStack.LoadMatrix(projection);
	
	// Camera matrix
	viewStack.LoadIdentity();
	viewStack.LookAt(
						camera.position.x, camera.position.y, camera.position.z,
						camera.target.x, camera.target.y, camera.target.z,
						camera.up.x, camera.up.y, camera.up.z
					);
	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();
	
	//Pass light
	if (lights[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(lights[0].position.x, lights[0].position.y, lights[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
	RenderMesh(meshList[GEO_AXES], false);
	if (m_ghost->active)
	{
		RenderGO(m_ghost);
	}

	for(std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if(go->active)
		{
			RenderGO(go);
		}
	}

	//On screen text

	std::ostringstream ss;
	//Exercise 5: Render m_objectCount
	ss << "GameObject Count: " << m_objectCount;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 12);

	ss.str("");
	ss.precision(5);
	ss << "Ink Amount: " << player.GetInkAmount();
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 21);
	
	ss.str("");
	ss.precision(5);
	ss << "FPS: " << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 3);
	
	RenderTextOnScreen(meshList[GEO_TEXT], "Collision", Color(0, 1, 0), 3, 0, 0);

	if (levelCompleted)
	{
		ss.str("");
		ss << "Level Completed";
		RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 10, 15, 30);

		if (curLevel == num_levels)
		{
			ss.str("");
			ss << "You completed all levels";
			RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 5, 20, 10);
		}
		else
		{
			ss.str("");
			ss << "'Enter' to next level";
			RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 5, 20, 10);
		}
	}
}

void SceneCollision::Exit()
{
	SceneBase::Exit();
	//Cleanup GameObjects
	while(m_goList.size() > 0)
	{
		GameObject *go = m_goList.back();
		delete go;
		m_goList.pop_back();
	}
	if(m_ghost)
	{
		delete m_ghost;
		m_ghost = NULL;
	}
}

void SceneCollision::ResetList(void)
{
	for (int i = 0; i < m_goList.size(); i++)
	{
		if (m_goList[i]->active == true)
		{
			m_goList[i]->active = false;
			m_objectCount--;
		}
	}
}

void SceneCollision::level1()
{
	spawner = FetchGO();
	spawner->type = GameObject::GO_DISPENSER;
	spawner->normal.Set(1, 0, 0);
	spawner->pos.Set(20, m_worldHeight - 5, 0);
	spawner->scale.Set(10, 5, 10);

	goal = FetchGO();
	goal->type = GameObject::GO_GOAL;
	goal->pos.Set(40, 20, 0);
	goal->normal.Set(1, 0, 0);
	goal->scale.Set(15, 10, 1);

	float offset = 44.5f;
	float wallThickness = 4.f;
	float wallHeight = m_worldHeight / 2 - wallThickness;
	float angleInterval = Math::PI;
	for (int i = 0; i < 2; i++) {
		MakeThinWall(
			m_worldWidth / 2 + (m_worldWidth / 2 - wallThickness) * cosf(angleInterval * i),
			m_worldHeight / 2 + (m_worldHeight / 2 - wallThickness) * sinf(angleInterval * i),
			Math::RadianToDegree(angleInterval) * i,
			wallThickness,
			wallHeight);
	}

	MakeThickWall(40, 50, 90, 5, 32);
}

void SceneCollision::level2()
{
	spawner = FetchGO();
	spawner->type = GameObject::GO_DISPENSER;
	spawner->normal.Set(1, 0, 0);
	spawner->pos.Set(20, m_worldHeight - 5, 0);
	spawner->scale.Set(10, 5, 10);

	goal = FetchGO();
	goal->type = GameObject::GO_GOAL;
	goal->pos.Set(m_worldWidth - 40, 10, 0);
	goal->normal.Set(1, 0, 0);
	goal->scale.Set(15, 10, 1);

	float offset = 44.5f;
	float wallThickness = 4.f;
	float wallHeight = m_worldHeight / 2 - wallThickness;
	float angleInterval = Math::PI;
	for (int i = 0; i < 2; i++) {
		MakeThinWall(
			m_worldWidth / 2 + (m_worldWidth / 2 - wallThickness) * cosf(angleInterval * i),
			m_worldHeight / 2 + (m_worldHeight / 2 - wallThickness) * sinf(angleInterval * i),
			Math::RadianToDegree(angleInterval) * i,
			wallThickness,
			wallHeight);
	}

	MakeThickWall(28, 35, 90, 5, 20);
	MakeThickWall(95, 85, 90, 15, 30);

	MakeFlipper(
		50, 38,
		Vector3(47.5, 35.5, 0),
		45,
		0,
		1.5f, 15.f);

	MakeFlipper(
		70, 70,
		Vector3(70, 75, 0),
		-90,
		-120,
		1.5f, 15.f);
}

void SceneCollision::level3()
{
	spawner = FetchGO();
	spawner->type = GameObject::GO_DISPENSER;
	spawner->normal.Set(1, 0, 0);
	spawner->pos.Set(20, m_worldHeight - 5, 0);
	spawner->scale.Set(10, 5, 10);

	goal = FetchGO();
	goal->type = GameObject::GO_GOAL;
	goal->pos.Set(m_worldWidth - 13, m_worldHeight / 2, 0);
	goal->normal.Set(1, 0, 0);
	goal->scale.Set(5, 20, 1);

	float offset = 44.5f;
	float wallThickness = 4.f;
	float wallHeight = m_worldHeight / 2 - wallThickness;
	float angleInterval = Math::PI;
	for (int i = 0; i < 2; i++) {
		MakeThinWall(
			m_worldWidth / 2 + (m_worldWidth / 2 - wallThickness) * cosf(angleInterval * i),
			m_worldHeight / 2 + (m_worldHeight / 2 - wallThickness) * sinf(angleInterval * i),
			Math::RadianToDegree(angleInterval) * i,
			wallThickness,
			wallHeight);
	}

	MakeThickWall(m_worldWidth - 20.5, 17.5, 90, 17.5, 2.5);
	MakeThickWall(m_worldWidth - 20.5, 82.5, 90, 17.5, 2.5);

	GameObject* go = FetchGO();
	go->active = true;
	go->type = GameObject::GO_BOUNCER;
	go->pos.Set(18, 30, 0);
	go->scale.Set(6, 6, 6);

	go = FetchGO();
	go->active = true;
	go->type = GameObject::GO_BOUNCER;
	go->pos.Set(58, 30, 0);
	go->scale.Set(6, 6, 6);

	go = FetchGO();
	go->active = true;
	go->type = GameObject::GO_BOUNCER;
	go->pos.Set(98, 30, 0);
	go->scale.Set(6, 6, 6);
}
