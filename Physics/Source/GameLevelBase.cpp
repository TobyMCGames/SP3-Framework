#include "GameLevelBase.h"
#include <fstream>
#include "Application.h"
#include "TileFactory.h"
#include "EntityFactory.h"

GameLevelBase::GameLevelBase()
{
	zOffset = 0;
	m_speed = GAMESPEED;
}

GameLevelBase::~GameLevelBase()
{

}

void GameLevelBase::RenderPlayer()
{
	modelStack.PushMatrix();
	{
		modelStack.Translate(player->pos.x, player->pos.y, player->pos.z + zOffset);
		modelStack.Scale(player->scale.x,player->scale.y,player->scale.z);
		RenderMesh(meshList[GEO_PLAYER], false);
		modelStack.PushMatrix();
		{
			modelStack.Translate(0, 0, 1);
			if (player->normal.x >= 0)
				modelStack.Rotate(Math::RadianToDegree(atan2f(player->normal.y,player->normal.x)), 0, 0, 1);
			else
			{
				//if plan to flip player, remove this line below
				modelStack.Rotate(180, 0, 1, 0);
				modelStack.Rotate(Math::RadianToDegree(atan2f(player->normal.y, -player->normal.x)), 0, 0, 1);
			}
			modelStack.PushMatrix();
			{
				modelStack.Translate(0.5, 0, 0);
				if (player->GetCurrentWeapon() == Player::BOW)
					RenderMesh(meshList[GEO_BOW], false);
				else if (player->GetCurrentWeapon() == Player::STAFF)
					RenderMesh(meshList[GEO_STAFF], false);
				else if (player->GetCurrentWeapon() == Player::PORTALGUN)
					RenderMesh(meshList[GEO_PORTALGUN], false);
			}
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
	}
	modelStack.PopMatrix();
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
	Vector3 scale = Vector3(TILEWIDTH * 1.f, TILEHEIGHT*1.f, 1);
	while (!file.eof()) {
		char line[256];
		file.getline(line, 256);
		if (!file.eof())
			linesinreverse.push_back(line);
	}
	float xOffset = 0, yOffset = 0;
	GameObject* temp = nullptr;
	Entity* tempEntity = nullptr;
	bool isEntity = false;
	for (int row = linesinreverse.size() - 1; row >= 0; row--)
	{
		for (int col = 0; col < 256; col++)
		{
			scale = Vector3(TILEWIDTH, TILEHEIGHT, 1);
			vel = Vector3(0, 0, 0);
			
			temp = nullptr;
			tempEntity = nullptr;
			isEntity = false;
			switch (linesinreverse[row][col])
			{
			case ',':
				commacounter++;
				continue;
			case '0':
				xOffset += TILEWIDTH;
				if (col - commacounter > highestcol)
					highestcol = col;
				map.push_back(temp);
				continue;
			case '1': // brick 
				pos.Set(xOffset + scale.x / 2, yOffset + scale.y / 2 , 0);
				temp = TileFactory::getObject(TileFactory::TILE_LIST::BRICK,pos,vel,scale);
				break;
			case '2': // stone brick
				pos.Set(xOffset + scale.x / 2, yOffset + scale.y / 2 , 0);
				temp = TileFactory::getObject(TileFactory::TILE_LIST::STONEBRICK,pos,vel,scale);
				break;
			case '3': // spike 
				pos.Set(xOffset  + scale.x / 2, yOffset + scale.y / 2, 0);
				temp = TileFactory::getObject(TileFactory::TILE_LIST::SPIKE, pos, vel, scale);
				break;
			case '4': // zombie
				pos.Set(xOffset + scale.x / 2, yOffset + scale.y / 2, 0);
				tempEntity = EntityFactory::GetInstance()->produceEntity(EntityFactory::ZOMBIE, pos, vel, scale);
				temp = tempEntity;
				isEntity = true;
				break;
			case '5': // Skeleton Archer
				pos.Set(xOffset + scale.x / 2, yOffset + scale.y / 2, 0);
				tempEntity = EntityFactory::GetInstance()->produceEntity(EntityFactory::SKELE_ARCHER, pos, vel, scale);
				temp = tempEntity;
				isEntity = true;
				break;
			case '6': // Spider
				pos.Set(xOffset + scale.x / 2, yOffset + scale.y / 2, 0);
				tempEntity = EntityFactory::GetInstance()->produceEntity(EntityFactory::SPIDER, pos, vel, scale);
				temp = tempEntity;
				isEntity = true;
				break;
			case '7': // Nymph
				pos.Set(xOffset + scale.x / 2, yOffset + scale.y / 2, 0);
				tempEntity = EntityFactory::GetInstance()->produceEntity(EntityFactory::NYMPH, pos, vel, scale);
				temp = tempEntity;
				isEntity = true;
				break;
			case '8': // Turret
				pos.Set(xOffset + scale.x / 2, yOffset + scale.y / 2, 0);
				tempEntity = EntityFactory::GetInstance()->produceEntity(EntityFactory::TURRET, pos, vel, scale);
				temp = tempEntity;
				isEntity = true;
				break;
			case '9': // Boomer
				pos.Set(xOffset + scale.x / 2, yOffset + scale.y / 2, 0);
				tempEntity = EntityFactory::GetInstance()->produceEntity(EntityFactory::BOOMER, pos, vel, scale);
				temp = tempEntity;
				isEntity = true;
				break;
			case '10': // Demon Lord
				pos.Set(xOffset + scale.x / 2, yOffset + scale.y / 2, 0);
				tempEntity = EntityFactory::GetInstance()->produceEntity(EntityFactory::DEMON_LORD, pos, vel, scale);
				temp = tempEntity;
				isEntity = true;
				break;
				
			case 'P':
				player->GetInstance();
				player->pos.Set((col - commacounter) * TILEWIDTH + (TILEWIDTH / 2.f), ((linesinreverse.size() -row) * TILEHEIGHT - (TILEHEIGHT / 2.f)), 0.1f);
				player->vel.SetZero();
				tempEntity = player;
				isEntity = true;
				break;
			}
			xOffset += TILEWIDTH;
			if ((col-commacounter) > highestcol)
				highestcol = col - commacounter;
			if (temp != nullptr && isEntity == false) 
			{
				temp->active = true;
				map.push_back(temp);
			}
			else if (isEntity == true)
			{
				map.push_back(nullptr);
				tempEntity->active = true;
				EntityList.push_back(tempEntity);
			
			}	
			else
				break;
		}
		xOffset = 0;
		yOffset += TILEHEIGHT;
		commacounter = 0;
	}
	m_worldWidth = (highestcol * TILEWIDTH);
	m_worldHeight = (linesinreverse.size())*TILEHEIGHT;
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
	return TILEWIDTH;
}

float GameLevelBase::getTileHeight()
{
	return TILEHEIGHT;
}

void GameLevelBase::cleanupList(std::vector<int>* indexlist)
{
	for (int j = 0; j < indexlist->size(); j++)
	{
		projectileList.erase(projectileList.begin() + indexlist->at(j) - j);
	}
	indexlist->clear();
}

bool GameLevelBase::CheckWithinScreen(GameObject* go)
{
	if (go->pos.x + go->scale.x / 2 < camera.position.x ||
		go->pos.x - go->scale.x / 2 > camera.position.x + XTILE_SCREEN * TILEWIDTH ||
		go->pos.y + go->scale.y / 2 < camera.position.y ||
		go->pos.y - go->scale.y / 2 > camera.position.y + YTILE_SCREEN * TILEHEIGHT)
	{
		return false;
	}
	return true;
}

void GameLevelBase::CollisionChecks(double dt, float m_speed)
{

	int XTilesInWorld = getworldWidth() / getTileWidth();
	int YTilesInWorld = getworldHeight() / getTileHeight();

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
		if (mob1 != nullptr)
		{
			if (CheckWithinScreen(mob1))
			{
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
				if (XnumTiles <= 0)
				{
					XTilesAround -= 1;
				}

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
				if (YnumTiles <= 0)
				{
					YTilesAround -= 1;
				}

				for (int j = XnumTiles; j < XnumTiles + XTilesAround; j++)
				{
					if (j > XTilesInWorld || j < 0)
						continue;
					for (int k = YnumTiles; k < YnumTiles + YTilesAround; k++)
					{
						if (k > YTilesInWorld || k < 0)
							continue;

						int TileSpace = k * XTilesInWorld + j;
						if (map[TileSpace] == nullptr)
							continue;
						
						if (mob1->type == GameObject::GO_PLAYER)
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
							else
							{
								//cout << "Im Falling" << endl;
							}
						}
						
					}
				}
				std::vector<int> cleanUpVector;
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
							cleanUpVector.push_back(j);
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

							FuturePos = projectile->pos + projectile->vel * dt * m_speed;
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
							if (XnumTiles <= 0)
							{
								XTilesAround -= 1;
							}

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
							if (YnumTiles <= 0)
							{
								YTilesAround -= 1;
							}

							for (int j = XnumTiles; j < XnumTiles + XTilesAround; j++)
							{
								if (j > XTilesInWorld || j < 0)
									continue;
								for (int k = YnumTiles; k < YnumTiles + YTilesAround; k++)
								{
									if (k > YTilesInWorld || k < 0)
										continue;
									int TileSpace = k * XTilesInWorld + j;
									if (map[TileSpace] == nullptr)
										continue;

									if (projectile->type == GameObject::GO_ARROW ||
										projectile->type == GameObject::GO_MAGICBALL ||
										projectile->type == GameObject::GO_PORTAL)
									{
										if (GamePhysics::GetInstance()->CheckCollision(projectile, map[TileSpace] ,dt, GAMESPEED))
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
							cleanUpVector.push_back(j);
						}
					}
					else
					{
						cout << "projectile was null in projectile list" << endl;
					}
				}
					// clean up was here
				if (cleanUpVector.size() != 0)
					cleanupList(&cleanUpVector);
			}
		}
		else
		{
			cout << "There was a null entity1" << endl;
		}
	}
}

std::vector<AdvanceGO*>* GameLevelBase::getProjectileList()
{
	return &projectileList;
}
