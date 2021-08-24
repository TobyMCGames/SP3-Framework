#include "GameLevelBase.h"
#include <fstream>
#include "Application.h"
#include "TileFactory.h"
#include "EntityFactory.h"
#include "InteractableFactory.h"

GameLevelBase::GameLevelBase()
{
	zOffset = 0;
	m_speed = GAMESPEED;
	m_worldWidth = 0;
	m_worldHeight = 0;
	player = nullptr;
	cloned = false;
	playerincontrol = true;
	clonedeleted = false;
}

GameLevelBase::~GameLevelBase()
{

}

void GameLevelBase::RenderPlayer()
{
	modelStack->PushMatrix();
	{
		modelStack->Translate(player->pos.x, player->pos.y, player->pos.z + zOffset);
		zOffset += 0.001f;
		modelStack->PushMatrix();
		{
			if (player->CheckCurDirection() == Entity::LEFT)
				modelStack->Rotate(180, 0, 1, 0);

			modelStack->Scale(player->scale.x, player->scale.y, player->scale.z);
			//RenderMesh(meshList[GEO_PLAYER], false);
			player->Render();
		}
		modelStack->PopMatrix();
		modelStack->PushMatrix();
		{
			modelStack->Translate(0, 0, 0.001f);
			zOffset += 0.001f;
			if (player->normal.x >= 0)
				modelStack->Rotate(Math::RadianToDegree(atan2f(player->normal.y, player->normal.x)), 0, 0, 1);
			else
			{
				modelStack->Rotate(180, 0, 1, 0);
				modelStack->Rotate(Math::RadianToDegree(atan2f(player->normal.y, -player->normal.x)), 0, 0, 1);
			}
			modelStack->PushMatrix();
			{
				modelStack->Translate(3, 0, 0);
				modelStack->Scale(player->scale.x, player->scale.y, player->scale.z);
				if (player->getcurWeapon() == Player::BOW)
					meshRender->RenderMesh(centralMesh->GetMeshID(CentralMesh::GEO_BOW), false);
				else if (player->getcurWeapon() == Player::STAFF)
					meshRender->RenderMesh(centralMesh->GetMeshID(CentralMesh::GEO_STAFF), false);
				else if (player->getcurWeapon() == Player::PORTALGUN)
					meshRender->RenderMesh(centralMesh->GetMeshID(CentralMesh::GEO_PORTALGUN), false);
			}
			modelStack->PopMatrix();
		}
		modelStack->PopMatrix();
	}
	modelStack->PopMatrix();
	if (cloned == true)
	{
		RenderPlayerClone();
	}
}

void GameLevelBase::RenderPlayerClone()
{
	modelStack->PushMatrix();
	{
		modelStack->Translate(player->getClone()->getpos().x, player->getClone()->getpos().y, player->getClone()->getpos().z + zOffset);
		zOffset += 0.001f;
		modelStack->PushMatrix();
		{
			if (player->getClone()->CheckCurDirection() == Entity::LEFT)
				modelStack->Rotate(180, 0, 1, 0);

			modelStack->Scale(player->getClone()->getscale().x, player->getClone()->getscale().y, player->getClone()->getscale().z);
			//RenderMesh(meshList[GEO_PLAYER], false);
			player->getClone()->Render();
		}
		modelStack->PopMatrix();
		modelStack->PushMatrix();
		{
			modelStack->Translate(0, 0, 0.001f);
			zOffset += 0.001f;
			if (player->getClone()->getnormal().x >= 0)
				modelStack->Rotate(Math::RadianToDegree(atan2f(player->getClone()->getnormal().y, player->getClone()->getnormal().x)), 0, 0, 1);
			else
			{
				modelStack->Rotate(180, 0, 1, 0);
				modelStack->Rotate(Math::RadianToDegree(atan2f(player->getClone()->getnormal().y, -player->getClone()->getnormal().x)), 0, 0, 1);
			}
			modelStack->PushMatrix();
			{
				modelStack->Translate(3, 0, 0);
				modelStack->Scale(player->getClone()->getscale().x, player->getClone()->getscale().y, player->getClone()->getscale().z);
				if (player->getClone()->getcurWeapon() == Player::BOW)
					meshRender->RenderMesh(centralMesh->GetMeshID(CentralMesh::GEO_BOW), false);
				else if (player->getClone()->getcurWeapon() == Player::STAFF)
					meshRender->RenderMesh(centralMesh->GetMeshID(CentralMesh::GEO_STAFF), false);
				else if (player->getClone()->getcurWeapon() == Player::PORTALGUN)
					meshRender->RenderMesh(centralMesh->GetMeshID(CentralMesh::GEO_PORTALGUN), false);
			}
			modelStack->PopMatrix();
		}
		modelStack->PopMatrix();
	}
	modelStack->PopMatrix();
	zOffset += 0.001f;
}


void GameLevelBase::mapinitPlayer(Vector3 pos, Vector3 vel, Vector3 scale, Vector3 normal)
{
	player = Player::GetInstance();
	player->pos = pos;
	player->vel = vel;
	player->scale = scale;
	player->normal = normal;
	player->active = true;
	player->type = GameObject::GO_PLAYER;
	EntityList.push_back(player);
	map.push_back(nullptr);
}

bool GameLevelBase::getcloned()
{
	return cloned;
}

void GameLevelBase::setcloned(bool cloned)
{
	this->cloned = cloned;
}

void GameLevelBase::setcloneDeleted(bool clonedeleted)
{
	this->clonedeleted = clonedeleted;
}

void GameLevelBase::swapcontrols()
{
	if (player->isControl() == true)
	{
		player->setControl(false);
		player->getClone()->setControl(true);
		player->getClone()->setvel(Vector3(0, 0, 0));
		player->vel = Vector3(0, 0, 0);
		//player->getClone()->getAnimation()->Reset();
		//player->getClone()->getAnimation()->PlayAnimation("Idle", -1, 1);
	}
	else if (player->isControl() == false)
	{
		player->setControl(true);
		player->getClone()->setControl(false);
		player->getClone()->setvel(Vector3(0, 0, 0));
		player->vel = Vector3(0, 0, 0);
		//player->getAnimation()->Reset();
		//player->getAnimation()->PlayAnimation("Idle", -1, 1);
	}

}

void GameLevelBase::entityPush(Entity* entity)
{
	EntityList.push_back(entity);
}


bool GameLevelBase::loadMap(std::string file_path)
{
	ifstream file;
	file.open(file_path);
	if (!file.is_open()) {
		cout << "File can not be opened" << endl;
		return false;
	}
	std::vector<std::string> linesinreverse;
	int commacounter = 0;
	int highestcol = 0;
	Vector3 pos = Vector3(0, 0, 0);
	Vector3 vel = Vector3(0, 0, 0);
	Vector3 scale = Vector3(TILEWIDTH, TILEHEIGHT, 1);
	Vector3	normal = Vector3(1, 0,0);
	GameObject* temp = nullptr;
	Entity* tempEntity = nullptr;
	Interactables* tempInteract = nullptr;
	while (!file.eof()) 
	{
		char line[256];
		file.getline(line, 256);
		if (!file.eof())
			linesinreverse.push_back(line);
	}
	float xOffset = 0, yOffset = 0;
	std::string key = "";

	for (int row = linesinreverse.size()-1; row >= 0; row--)
	{
		for (int col = 0; col < linesinreverse[row].size(); col++)
		{
			scale.Set(TILEWIDTH, TILEHEIGHT, 1);
			pos.Set(xOffset + scale.x / 2, yOffset + scale.y / 2, 0);
			vel.SetZero();
			temp = nullptr;
			tempEntity = nullptr;
			tempInteract = nullptr;
			if ((linesinreverse[row][col] == ',') || (col == linesinreverse[row].size() - 1))
			{
				if (col == linesinreverse[row].size() - 1)
				{
					key += linesinreverse[row][col];
				}
				if (key == "0")
				{

				}
				else if (key == "1") // brick
				{
					temp = TileFactory::getObject(TileFactory::BRICK, pos, vel, scale);
				}
				else if (key == "2") // stonebrick
				{
					temp = TileFactory::getObject(TileFactory::STONEBRICK, pos, vel, scale);
				}
				else if (key == "3") // spike
				{
					temp = TileFactory::getObject(TileFactory::SPIKE, pos, vel, scale);
				}
				else if (key == "4") // zombie
				{
					tempEntity = EntityFactory::GetInstance()->produceEntity(EntityFactory::ZOMBIE, pos, vel, scale);
				}
				else if (key == "5") // skelearcher
				{
					tempEntity = EntityFactory::GetInstance()->produceEntity(EntityFactory::SKELE_ARCHER, pos, vel, scale);
				}
				else if (key == "6") // spider
				{
					tempEntity = EntityFactory::GetInstance()->produceEntity(EntityFactory::SPIDER, pos, vel, scale);
				}
				else if (key == "7") //nymph
				{
					tempEntity = EntityFactory::GetInstance()->produceEntity(EntityFactory::NYMPH, pos, vel, scale);
				}
				else if (key == "8") //turret
				{
					tempEntity = EntityFactory::GetInstance()->produceEntity(EntityFactory::TURRET, pos, vel, scale);
				}
				else if (key == "9") // boomer
				{
					tempEntity = EntityFactory::GetInstance()->produceEntity(EntityFactory::BOOMER, pos, vel, scale);
				}
				else if (key == "10")// demon lord
				{
					tempEntity = EntityFactory::GetInstance()->produceEntity(EntityFactory::DEMON_LORD, pos, vel, scale);
				}
				else if (key == "P")//player
				{
					scale.Set(TILEWIDTH - 0.5, TILEHEIGHT - 0.5, 1);
					mapinitPlayer(pos, vel, scale, normal);
					xOffset += getTileWidth();
					key = "";
					commacounter++;
					continue;
				}
				else if (key == "WB") // Weapon Station Bow
				{
					tempInteract = InteractableFactory::GetInstance()->produceInteractable(InteractableFactory::PTYPE_BOW_STATION, pos, scale);
				}
				else if (key == "WS") // Weapon Station Staff
				{
					tempInteract = InteractableFactory::GetInstance()->produceInteractable(InteractableFactory::PTYPE_STAFF_STATION, pos, scale);
				}
				else if (key == "WP") // Weapon Station Portal
				{
					tempInteract = InteractableFactory::GetInstance()->produceInteractable(InteractableFactory::PTYPE_PORTAL_STATION, pos, scale);
				}

				if (tempEntity != nullptr)
				{
					EntityList.push_back(tempEntity);
				}
				else if (tempInteract != nullptr)
				{
					InteractableList.push_back(tempInteract);
				}

				map.push_back(temp);
				xOffset += getTileWidth();

				key = "";
				commacounter++;
			}
			else
				key += linesinreverse[row][col];
			if ((commacounter) > highestcol)
				highestcol = commacounter;
		}
		xOffset = 0;
		yOffset += getTileHeight();
		commacounter = 0;
	}
	m_worldWidth = (highestcol * getTileWidth());
	m_worldHeight = (linesinreverse.size())* getTileHeight();
	return true;
}


float GameLevelBase::getworldWidth()
{
	return m_worldWidth;
}

float GameLevelBase::getworldHeight()
{
	return m_worldHeight;
}

float GameLevelBase::getTileWidth()
{
	return TILEWIDTH + offset;
}

float GameLevelBase::getTileHeight()
{
	return TILEHEIGHT + offset;
}



void GameLevelBase::cleanupList(std::vector<int>* indexlist) // NOTE
{
	for (int j = 0; j < indexlist->size(); j++)
	{
		projectileList.erase(projectileList.begin() + indexlist->at(j) - j);
	}
	indexlist->clear();
}

// with cleanuplists function, takes 3 parameters which controls what is deleted
// clearAll checks whether everything is deleted from the particular list
// the function takes in 2 type of lists with their default being nullptr
// this function is used to clear lists 1 at a time. 
// e.g cleanupLists(false,nullptr,&map) to delete map
// e.g cleanupLists(false,&projectileList)  to delete projectilelist

void GameLevelBase::cleanupLists(bool clearAll, std::vector<AdvanceGO*>* advobjlist, std::vector<GameObject*>* golist)
{
	int previndex = 0;
	if (advobjlist != nullptr && golist != nullptr)
	{
		std::cout << "ambiguous which objlist to delete" << std::endl;
		return;
	}
	else if (advobjlist == nullptr && golist == nullptr)
	{
		std::cout << "theres no GOs to delete" << std::endl;
		return;
	}
	if (advobjlist != nullptr)
	{
		if (clearAll == true)
		{
			for (int i = 0; i < advobjlist->size(); i++)
			{
				delete advobjlist->at(i);
				advobjlist->at(i) = nullptr;
			}
			advobjlist->clear();
		}
		else
		{
			for (int i = previndex; i < advobjlist->size(); i++)
			{
				if (advobjlist->at(i) == nullptr)
				{
					advobjlist->erase(advobjlist->begin() + i);
					previndex = i;
					break;
				}
				else if (advobjlist->at(i)->active == false)
				{
					delete advobjlist->at(i);
					advobjlist->at(i) = nullptr;
					advobjlist->erase(advobjlist->begin() + i);
					previndex = i;
					break;
				}
			}
		}
	}
	else if (golist != nullptr)
	{
		if (clearAll == true)
		{
			for (int i = 0; i < golist->size(); i++)
			{
				delete golist->at(i);
				golist->at(i) = nullptr;
			}
			golist->clear();
		}
		else
		{
			for (int i = previndex; i < golist->size(); i++)
			{
				if (golist->at(i) == nullptr)
				{
					golist->erase(golist->begin() + i);
					previndex = i;
					break;
				}
				else if (golist->at(i)->active == false)
				{
					delete golist->at(i);
					golist->at(i) = nullptr;
					golist->erase(golist->begin() + i);
					previndex = i;
					break;
				}
			}
		}
	}
}

bool GameLevelBase::CheckWithinScreen(GameObject* go)
{
	if (go->pos.x + go->scale.x / 2 < camera->position.x ||
		go->pos.x - go->scale.x / 2 > camera->position.x + XTILE_SCREEN *getTileWidth()||
		go->pos.y + go->scale.y / 2 < camera->position.y ||
		go->pos.y - go->scale.y / 2 > camera->position.y + YTILE_SCREEN * getTileHeight())
	{
		return false;
	}
	return true;
}

void GameLevelBase::CollisionChecks(double dt, float m_speed)
{
	int XTilesInWorld = getworldWidth() / (getTileWidth());
	int YTilesInWorld = getworldHeight() / (getTileHeight());

	float LP = 0.f;
	int XnumTiles = 0;
	int XTilesAround = 0;
	float BP = 0.f;
	int YnumTiles = 0;
	int YTilesAround = 0;
	/////////////////////////////////////////////////////////////

	for (int i = 0; i < EntityList.size(); i++)
	{
		AdvanceGO* mob1 = EntityList[i];
		if (mob1 == nullptr)
		{
			cout << "There was a null entity1" << endl;
			continue;
		}
		if (!CheckWithinScreen(mob1))
			continue;
	
		Vector3 FuturePos = mob1->pos + mob1->vel * dt * m_speed;
		//Find how many tiles mob is away from left side
		LP = FuturePos.x - mob1->scale.x / 2;
		XnumTiles = (LP - fmod(LP, getTileWidth())) / getTileWidth();
		if (XnumTiles > 0)
		{
			XnumTiles -= 1;
		}
		XTilesAround = (mob1->scale.x - fmod(mob1->scale.x, getTileWidth())) / getTileWidth();
		if (fmod(mob1->scale.x, getTileWidth()) > 0)
			XTilesAround += 3;
		else
			XTilesAround += 2;

		//Find how many tiles screen is away from bottom
		BP = FuturePos.y - mob1->scale.y /2;
		YnumTiles = (BP - fmod(BP, getTileHeight())) / getTileHeight();
		if (YnumTiles > 0)
		{
			YnumTiles -= 1;
		}
		YTilesAround = (mob1->scale.y - fmod(mob1->scale.y, getTileHeight())) / getTileHeight();
		if (fmod(mob1->scale.y, getTileHeight()) > 0)
			YTilesAround += 3;
		else
			YTilesAround += 2;

		for (int j = XnumTiles; j < XnumTiles + XTilesAround; j++)
		{
			if (j >= XTilesInWorld || j < 0)
				continue;
			for (int k = YnumTiles; k < YnumTiles + YTilesAround; k++)
			{
				if (k >= YTilesInWorld || k < 0)
					continue;

				int TileSpace = k * XTilesInWorld + j;
				if (map[TileSpace] == nullptr)
					continue;

				if ((mob1->type == GameObject::GO_PLAYER || mob1->type == GameObject::GO_PLAYERCLONE))
				{
					if (GamePhysics::GetInstance()->CheckCollision(mob1, map[TileSpace], dt, GAMESPEED))
					{
						GamePhysics::GetInstance()->CheckCollisionResponse(mob1, map[TileSpace], dt, GAMESPEED);
						//cout << "Collided" << endl;
						break;
					}
				}
				else
				{
					if (GamePhysics::GetInstance()->CheckCollision(mob1, map[TileSpace], dt, m_speed))
					{
						GamePhysics::GetInstance()->CheckCollisionResponse(mob1, map[TileSpace], dt, m_speed);
						//cout << "Collided" << endl;
						break;
					}
				}
			}
		}
		//std::vector<int> cleanUpVector;
		for (int j = 0; j < projectileList.size(); j++)
		{
			AdvanceGO* projectile;
			projectile = projectileList[j];
			if (projectile == nullptr)
			{
				cout << "projectile was null in projectile list" << endl;
				continue;
			}
			if (projectile->active == false)
			{
				delete projectile;
				projectileList[j] = nullptr;
				//cleanUpVector.push_back(j);
				continue;
			}
							
			if (CheckWithinScreen(projectile))
			{
				if (projectile->type == GameObject::GO_ARROW ||
					projectile->type == GameObject::GO_MAGICBALL ||
					projectile->type == GameObject::GO_PORTAL)
				{
					if (GamePhysics::GetInstance()->CheckCollision(mob1, projectile, dt, GAMESPEED))
					{
						GamePhysics::GetInstance()->CheckCollisionResponse(mob1, projectile, dt, GAMESPEED);
					}
				}
				else
				{
					if (GamePhysics::GetInstance()->CheckCollision(mob1, projectile, dt, m_speed))
					{
						GamePhysics::GetInstance()->CheckCollisionResponse(mob1, projectile, dt, m_speed);
					}
				}
			}
			else // delete projectile if they are no longer on screen
			{
				delete projectile;
				projectileList[j] = nullptr;
				//cleanUpVector.push_back(j);
			}
		}
		// projectile cleanup
		//if (cleanUpVector.size() != 0)
		//	cleanupList(&cleanUpVector);
		if (projectileList.size() != 0)
			cleanupLists(false, &projectileList);

		///////  Only player or clone  can collide with
		if (mob1->type != GameObject::GO_PLAYER && mob1->type != GameObject::GO_PLAYERCLONE)
			continue;
		for (int j = 0; j < InteractableList.size(); j++)
		{
			if (InteractableList[j] == nullptr)
			{
				cout << "There was a null interactable" << endl;
				continue;
			}
			if (!CheckWithinScreen(InteractableList[j]) || InteractableList[j]->active == false)
				continue;
			if (GamePhysics::GetInstance()->CheckCollision(mob1, InteractableList[j], dt, m_speed))
			{
				GamePhysics::GetInstance()->CheckCollisionResponse(mob1, InteractableList[j], dt, m_speed);
			}
		}
	}
	if (EntityList.size() > 0)
		cleanupLists(false, &EntityList);

	//std::vector<int> cleanUpVector;
	for (int j = 0; j < projectileList.size(); j++)
	{
		AdvanceGO* projectile;
		projectile = projectileList[j];
		if (projectile != nullptr)
		{
			if (projectile->active == false)
			{
				delete projectile;
				projectileList[j] = nullptr;
			//	cleanUpVector.push_back(j);
				continue;
			}

			if (CheckWithinScreen(projectile))
			{

				Vector3 FuturePos = projectile->pos + projectile->vel * dt * m_speed;
				Vector3 FutureN = projectile->vel + GamePhysics::GetInstance()->gravity * dt * m_speed;
				float angle = atan2f(FutureN.y, FutureN.y);
				//Find how many tiles mob is away from left side
				LP = FuturePos.x - (projectile->scale.x * cos(angle) + projectile->scale.y * sin(angle)) / 2;
				XnumTiles = (LP - fmod(LP, getTileWidth())) / getTileWidth();
				if (XnumTiles > 0)
				{
					XnumTiles -= 1;
				}
				XTilesAround = (projectile->scale.x - fmod(projectile->scale.x, getTileWidth())) / getTileWidth();
				if (fmod(projectile->scale.x, getTileWidth()) > 0)
					XTilesAround += 3;
				else
					XTilesAround += 2;

				//Find how many tiles screen is away from bottom
				BP = FuturePos.y - (projectile->scale.x * sin(angle) + projectile->scale.y * cos(angle)) / 2;
				YnumTiles = (BP - fmod(BP, getTileHeight())) / getTileHeight();
				if (YnumTiles > 0)
				{
					YnumTiles -= 1;
				}
				YTilesAround = (projectile->scale.y - fmod(projectile->scale.y, getTileHeight())) / getTileHeight();
				if (fmod(projectile->scale.y, getTileHeight()) > 0)
					YTilesAround += 3;
				else
					YTilesAround += 2;

				for (int j = XnumTiles; j < XnumTiles + XTilesAround; j++)
				{
					if (j >= XTilesInWorld || j < 0)
						continue;
					for (int k = YnumTiles; k < YnumTiles + YTilesAround; k++)
					{
						if (k >= YTilesInWorld || k < 0)
							continue;
						int TileSpace = k * XTilesInWorld + j;
						if (map[TileSpace] == nullptr)
							continue;

						if (projectile->type == GameObject::GO_ARROW ||
							projectile->type == GameObject::GO_MAGICBALL ||
							projectile->type == GameObject::GO_PORTAL)
						{
							if (GamePhysics::GetInstance()->CheckCollision(projectile, map[TileSpace], dt, GAMESPEED))
							{
								GamePhysics::GetInstance()->CheckCollisionResponse(projectile, map[TileSpace], dt, GAMESPEED);
							}
						}
						else
						{
							if (GamePhysics::GetInstance()->CheckCollision(projectile, map[TileSpace], dt, m_speed))
							{
								GamePhysics::GetInstance()->CheckCollisionResponse(projectile, map[TileSpace], dt, m_speed);
							}
						}

					}
				}
			}
			else // delete projectile if they are no longer on screen
			{
				delete projectile;
				projectileList[j] = nullptr;
				//cleanUpVector.push_back(j);
			}
		}
		else
		{
			cout << "projectile was null in projectile list" << endl;
		}
	}
	// clean up was here
//	if (cleanUpVector.size() != 0)
		//cleanupList(&cleanUpVector);
	cleanupLists(false, &projectileList);
}

std::vector<AdvanceGO*>* GameLevelBase::getProjectileList()
{
	return &projectileList;
}

void GameLevelBase::Exit()
{
	for (int i = 0; i < map.size(); i++)
	{
		if (map[i] != nullptr)
		{
			delete map[i];
			map[i] = nullptr;
		}
	}
	map.clear();
	for (int i = 0; i < EntityList.size(); i++)
	{
		if (EntityList[i]->type == GameObject::GO_PLAYER)
			player->DestroyInstance();
		else
			delete EntityList[i];
		EntityList[i] = nullptr;
	}
	EntityList.clear();
	for (int i = 0; i < projectileList.size(); i++)
	{
		delete projectileList[i];
		projectileList[i] = nullptr;
	}
	projectileList.clear();
	for (int i = 0; i < InteractableList.size(); i++)
	{
		delete InteractableList[i];
		InteractableList[i] = nullptr;
	}
	InteractableList.clear();
}