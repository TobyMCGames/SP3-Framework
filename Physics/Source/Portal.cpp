#include "Portal.h"
#include "GameLevelManager.h"

Portal::Portal()
{
	Default_Speed = 50.f;
	scale.Set(5, 5, 1);
}

Portal::~Portal()
{
}



int Portal::getIndex(AdvanceGO* K)
{
	auto portalVector = find(GameLevelManager::GetInstance()->getcurrentLevel()->getInteractableList()->begin(), GameLevelManager::GetInstance()->getcurrentLevel()->getInteractableList()->end(), K);
	// If element was found
	if (portalVector != GameLevelManager::GetInstance()->getcurrentLevel()->getInteractableList()->end())
	{
		int index = portalVector - GameLevelManager::GetInstance()->getcurrentLevel()->getInteractableList()->begin();
		return index;
	}
	else 
	{
		cout << "portal gate not inside vector" << endl;
	}
}

void Portal::Update(double dt, float m_speed)
{
	pos += vel * dt * m_speed;
}

void Portal::Response(GameObject* go)
{
	if ((go->type > GameObject::PASSIVE_TILE_START &&
		go->type < GameObject::PASSIVE_TILE_END))
	{
		this->active = false;
		Vector3 PGateNormal;
		Vector3 PGatePos;
		if (GamePhysics::GetInstance()->GetCollidePos() == UP)
		{
			PGateNormal.Set(0, 1, 0);
			PGatePos.Set(go->pos.x, pos.y);
		}
		else if (GamePhysics::GetInstance()->GetCollidePos() == DOWN)
		{
			PGateNormal.Set(0, -1, 0);
			PGatePos.Set(go->pos.x, pos.y);
		}
		else if (GamePhysics::GetInstance()->GetCollidePos() == LEFT)
		{
			PGateNormal.Set(-1, 0, 0);
			PGatePos.Set(pos.x, go->pos.y);
		}
		else if (GamePhysics::GetInstance()->GetCollidePos() == RIGHT)
		{
			PGateNormal.Set(1, 0, 0);
			PGatePos.Set(pos.x, go->pos.y);
		}

		if (go->type != BRICK_TILE && go->type != LAVA_TILE)
		{
			if (Player::GetInstance()->portalCounter < 2)
			{
				AdvanceGO* go = InteractableFactory::GetInstance()->produceInteractable(
					InteractableFactory::PTYPE_PORTAL_ENTRANCE, PGatePos, Vector3(4.5f, 4.5f, 1.f), PGateNormal);
				GameLevelManager::GetInstance()->getcurrentLevel()->getInteractableList()->push_back(go);
				Player::GetInstance()->portalCounter++;
			}
			else
			{
				AdvanceGO* go = InteractableFactory::GetInstance()->produceInteractable(
					InteractableFactory::PTYPE_PORTAL_ENTRANCE, PGatePos, Vector3(4.5f, 4.5f, 1.f), PGateNormal);
				GameLevelManager::GetInstance()->getcurrentLevel()->getInteractableList()->push_back(go);
				for (int i = 0; i < GameLevelManager::GetInstance()->getcurrentLevel()->getInteractableList()->size(); i++)
				{
					if (GameLevelManager::GetInstance()->getcurrentLevel()->getInteractableList()->at(i)->type == PORTAL_GATE_ENTRANCE)
					{
						if (GameLevelManager::GetInstance()->getcurrentLevel()->getInteractableList()->at(i)->active == false)
						{
							continue;
						}
						GameLevelManager::GetInstance()->getcurrentLevel()->getInteractableList()->at(i)->active = false;
						break;
					}
				}
			}
		}
	}
}

void Portal::Render()
{
}


