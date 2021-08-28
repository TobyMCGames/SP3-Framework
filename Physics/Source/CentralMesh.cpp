#include "CentralMesh.h"
#include "GL\glew.h"

#include "Utility.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"
#include <fstream>
#include <sstream>

void CentralMesh::ChangeMat(int idx, Color color, float ambient, float diffuse, float specular, float Shiny)
{
	meshList[idx]->material.kAmbient.Set(ambient * color.r, ambient * color.g, ambient * color.b);
	meshList[idx]->material.kDiffuse.Set(diffuse * color.r, diffuse * color.g, diffuse * color.b);
	meshList[idx]->material.kSpecular.Set(specular * color.r, specular * color.g, specular * color.b);
	meshList[idx]->material.kShininess = Shiny;
}

void CentralMesh::FontLoader(std::string file_path)
{
	std::ifstream file;
	file.open(file_path);
	if (!file.is_open()) { //If file cannot be opened
		std::cout << "File can not be opened" << std::endl;
		return;
	}
	else {
		int count = 0;
		while (!file.eof()) {
			char line[256];
			file.getline(line, 256);
			sscanf_s(line, "%d", &textWidth[count++]);
		}
	}
}

Mesh* CentralMesh::GetMeshID(GEOMETRY_TYPE ID)
{
	return meshList[ID];
}

int CentralMesh::GetTextWidth(int ID)
{
	return textWidth[ID];
}


CentralMesh::CentralMesh()
{
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	meshList[GEO_BALL] = MeshBuilder::GenerateSphere("ball", Color(1, 1, 1), 10, 10, 1.f);
	meshList[GEO_CYLINDER] = MeshBuilder::GenerateCylinder("cylinder", Color(1, 1, 1), 20, 1.f, 1.f);
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(1,1,1), 2.f);
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("Quad", Color(1, 0, 0));
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_TEXT]->material.kAmbient.Set(1, 0, 0);

	//GAMESTATE PAGES
	meshList[GEO_BACKGROUND] = MeshBuilder::GenerateQuad("background", Color(1, 1, 1), 2);
	meshList[GEO_BACKGROUND]->textureID = LoadTGA("Image//GAMESTATES//castle_background.tga");
	meshList[GEO_TITLE] = MeshBuilder::GenerateQuad("title", Color(1, 1, 1), 2);
	meshList[GEO_TITLE]->textureID = LoadTGA("Image//GAMESTATES//game_title.tga");
	meshList[GEO_CONTROLS] = MeshBuilder::GenerateQuad("controls", Color(1, 1, 1), 2);
	meshList[GEO_CONTROLS]->textureID = LoadTGA("Image//GAMESTATES//controls.tga");
	meshList[GEO_CREDITS] = MeshBuilder::GenerateQuad("credits", Color(1, 1, 1), 2);
	meshList[GEO_CREDITS]->textureID = LoadTGA("Image//GAMESTATES//credits.tga");

	// SCENE GUI
	meshList[GUI_PAUSE] = MeshBuilder::GenerateQuad("pauseScreen", Color(1, 1, 1));
	meshList[GUI_PAUSE]->textureID = LoadTGA("Image/GUI/PauseScreen.tga");
	meshList[GUI_RETRY] = MeshBuilder::GenerateQuad("pauseScreen", Color(0.2, 0.2, 0.2));
	meshList[GUI_BORDER] = MeshBuilder::GenerateQuad("Border", Color(1, 1, 1));
	meshList[GUI_BORDER]->textureID = LoadTGA("Image/GUI/border.tga");
	meshList[GUI_HEART] = MeshBuilder::GenerateQuad("Hearts_sprite", Color(1, 1, 1));
	meshList[GUI_HEART]->textureID = LoadTGA("Image/GUI/Hearts_Icon.tga");
	meshList[GUI_ENERGY] = MeshBuilder::GenerateQuad("Energy_Sprite", Color(1, 1, 1));
	meshList[GUI_ENERGY]->textureID = LoadTGA("Image//GUI//Energy_Icon.tga");
	meshList[GUI_CELLS] = MeshBuilder::GenerateQuad("UI_CELLS_Sprite", Color(1, 1, 1));
	meshList[GUI_CELLS]->textureID = LoadTGA("Image//GUI//normal_Cells.tga");
	meshList[GUI_ENERGYBAR] = MeshBuilder::GenerateQuad("healthbar", Color(0.0f, 0.7f, 0.7f));
	meshList[GUI_HEALTHBAR] = MeshBuilder::GenerateQuad("energybar", Color(0.7f, 0.0f, 0.0f));
	meshList[GUI_STATS_BG] = MeshBuilder::GenerateQuad("stats_bg", Color(1, 1, 1));
	meshList[GUI_STATS_BG]->textureID = LoadTGA("Image//GUI//Stats_background.tga");
	meshList[GUI_ATK_ICON] = MeshBuilder::GenerateQuad("atkicon", Color(1, 1, 1));
	meshList[GUI_ATK_ICON]->textureID = LoadTGA("Image//GUI//AtkIcon.tga");
	meshList[TEXT_BOX] = MeshBuilder::GenerateQuad("Textbox",Color(1,1,1));
	meshList[TEXT_BOX]->textureID = LoadTGA("Image//GUI//Dialogue_Text_Box.tga");
	meshList[GEO_DEMONLORD_HEALTHBAR] = MeshBuilder::GenerateQuad("demon healthbar", Color(1, 1, 1));
	meshList[GEO_DEMONLORD_HEALTHBAR]->textureID = LoadTGA("Image//GUI//DemonLord_HealthBar.tga");


	// TILE
	//meshList[PASSIVE_TILE] = MeshBuilder::GenerateQuad("passivetile", Color(1, 1, 1));
	//meshList[PASSIVE_TILE]->textureID = LoadTGA("Image//TILE//Stone_Brick_Tile.tga");

	meshList[GEO_STONEBRICK] = MeshBuilder::GenerateQuad("stonebrick", Color(1, 1, 1));
	meshList[GEO_STONEBRICK]->textureID = LoadTGA("Image//TILE//Stone_Brick_Tile_2.tga");
	meshList[GEO_BRICK] = MeshBuilder::GenerateQuad("brick", Color(1, 1, 1));
	meshList[GEO_BRICK]->textureID = LoadTGA("Image//TILE//Brick_Tile_2.tga");

	meshList[GEO_SOIL_TILE] = MeshBuilder::GenerateQuad("soil", Color(1, 1, 1));
	meshList[GEO_SOIL_TILE]->textureID = LoadTGA("Image//TILE//Soil_Tile.tga");
	meshList[GEO_GRASS_SOIL_TILE] = MeshBuilder::GenerateQuad("soil", Color(1, 1, 1));
	meshList[GEO_GRASS_SOIL_TILE]->textureID = LoadTGA("Image//TILE//Grass_Soil_Tile.tga");
	meshList[GEO_CAVE_TILE] = MeshBuilder::GenerateQuad("cave_tile", Color(1, 1, 1));
	meshList[GEO_CAVE_TILE]->textureID = LoadTGA("Image//TILE//Cave_Tile.tga");
	meshList[GEO_FRAGILE_CAVE_TILE] = MeshBuilder::GenerateQuad("fragile_cave_tile", Color(1, 1, 1));
	meshList[GEO_FRAGILE_CAVE_TILE]->textureID = LoadTGA("Image//TILE//Fragile_Rock.tga");
	meshList[GEO_LAVA_TILE] = MeshBuilder::GenerateQuad("lava_tile", Color(1, 1, 1));
	meshList[GEO_LAVA_TILE]->textureID = LoadTGA("Image//TILE//Lava_Tile.tga");
	meshList[GEO_STONE_WATERFALL_TILE] = MeshBuilder::GenerateQuad("stone_waterfall_tile", Color(1, 1, 1));
	meshList[GEO_STONE_WATERFALL_TILE]->textureID = LoadTGA("Image//TILE//Stone_Waterfall_Tile.tga");
	meshList[GEO_DOOR_1] = MeshBuilder::GenerateQuad("door1", Color(1, 1, 1));
	meshList[GEO_DOOR_1]->textureID = LoadTGA("Image//TILE//Door1.tga");
	meshList[GEO_DOOR_2] = MeshBuilder::GenerateQuad("door2", Color(1, 1, 1));
	meshList[GEO_DOOR_2]->textureID = LoadTGA("Image//TILE//Door2.tga");
	meshList[GEO_DOOR_3] = MeshBuilder::GenerateQuad("door3", Color(1, 1, 1));
	meshList[GEO_DOOR_3]->textureID = LoadTGA("Image//TILE//Door3.tga");
	meshList[GEO_DOOR_4] = MeshBuilder::GenerateQuad("door4", Color(1, 1, 1));
	meshList[GEO_DOOR_4]->textureID = LoadTGA("Image//TILE//Door4.tga");
	meshList[GEO_DOOR_5] = MeshBuilder::GenerateQuad("door5", Color(1, 1, 1));
	meshList[GEO_DOOR_5]->textureID = LoadTGA("Image//TILE//Door5.tga");
	meshList[GEO_DARK_FOREST_GRASS] = MeshBuilder::GenerateQuad("door5", Color(1, 1, 1));
	meshList[GEO_DARK_FOREST_GRASS]->textureID = LoadTGA("Image//TILE//Dark_Forest_Grass.tga");
	meshList[GEO_DARK_FOREST_GROUND] = MeshBuilder::GenerateQuad("door5", Color(1, 1, 1));
	meshList[GEO_DARK_FOREST_GROUND]->textureID = LoadTGA("Image//TILE//Dark_Forest_Ground.tga");
	meshList[GEO_TREE_TILE] = MeshBuilder::GenerateQuad("tree", Color(1, 1, 1));
	meshList[GEO_TREE_TILE]->textureID = LoadTGA("Image//TILE//Tree_Tile.tga");
	meshList[GEO_CASTLE_PLATFORM] = MeshBuilder::GenerateQuad("castle platform", Color(1, 1, 1));
	meshList[GEO_CASTLE_PLATFORM]->textureID = LoadTGA("Image//TILE//Castle_Platform.tga");
	meshList[GEO_LARGESTONE2] = MeshBuilder::GenerateQuad("largestone2", Color(1, 1, 1));
	meshList[GEO_LARGESTONE2]->textureID = LoadTGA("Image//TILE//LargeStone2.tga");
	meshList[GEO_WOOD_LOG] = MeshBuilder::GenerateQuad("wood_log", Color(1, 1, 1));
	meshList[GEO_WOOD_LOG]->textureID = LoadTGA("Image//TILE//Wood_Log.tga");

	meshList[GEO_SPIKE] = MeshBuilder::GenerateQuad("SPIKE", Color(1, 1, 1));
	meshList[GEO_SPIKE]->textureID = LoadTGA("Image//TILE//Spikes_Tile.tga");
	meshList[GEO_WARP_GATE_TILE] = MeshBuilder::GenerateQuad("warpgate", Color(1, 1, 1));
	meshList[GEO_WARP_GATE_TILE]->textureID = LoadTGA("Image//TILE//Warp_Gate_Tile.tga");
	meshList[GEO_BOMB_CRATE] = MeshBuilder::GenerateQuad("bomb crate", Color(1, 1, 1));
	meshList[GEO_BOMB_CRATE]->textureID = LoadTGA("Image//InteractiveBlocks//bombcrate.tga");
	meshList[GEO_TREE_SEEDS] = MeshBuilder::GenerateQuad("tree seeds", Color(1, 1, 1));
	meshList[GEO_TREE_SEEDS]->textureID = LoadTGA("Image//InteractiveBlocks//treeSapling.tga");
	meshList[GEO_VINE_SEEDS] = MeshBuilder::GenerateQuad("vine seeds", Color(1, 1, 1));
	meshList[GEO_VINE_SEEDS]->textureID = LoadTGA("Image//InteractiveBlocks//smallVine.tga");
	meshList[GEO_PLAYER] = MeshBuilder::GenerateSpriteAnimation("Player", Color(1, 1, 1), 2, 6, 1.f);
	meshList[GEO_PLAYER]->textureID = LoadTGA("Image//Player//playerAnimation.tga");
	meshList[GEO_TIMETRAVEL] = MeshBuilder::GenerateSpriteAnimation("time_travel", Color(1.f, 1.f, 1.f), 2, 6, 1.f);
	meshList[GEO_TIMETRAVEL]->textureID = LoadTGA("Image/Player/TimeTravel_animation.tga");

	//Weapons
	meshList[GEO_BOW] = MeshBuilder::GenerateQuad("bow", Color(1, 1, 1));
	meshList[GEO_BOW]->textureID = LoadTGA("Image//WEAPONS//bow.tga");
	meshList[GEO_STAFF] = MeshBuilder::GenerateQuad("staff", Color(1, 1, 1));
	meshList[GEO_STAFF]->textureID = LoadTGA("Image//WEAPONS//staff_blue.tga");
	meshList[GEO_PORTALGUN] = MeshBuilder::GenerateQuad("portal gun", Color(1, 1, 1));
	meshList[GEO_PORTALGUN]->textureID = LoadTGA("Image//WEAPONS//portal_gun.tga");
	meshList[GEO_BOMB] = MeshBuilder::GenerateSpriteAnimation("Bomb_animation", Color(1, 1, 1), 3,3);
	meshList[GEO_BOMB]->textureID = LoadTGA("Image//WEAPONS//Bomb_Animation.tga");

	//Interactables
	meshList[GEO_WEAPON_STATION] = MeshBuilder::GenerateQuad("Stone Pedastal", Color(1, 1, 1));
	meshList[GEO_WEAPON_STATION]->textureID = LoadTGA("Image//InteractiveBlocks//WeaponStation.tga");
	meshList[GEO_PORTAL_GATE_ENTRANCE] = MeshBuilder::GenerateQuad("Portal gate", Color(1, 1, 1));
	meshList[GEO_PORTAL_GATE_ENTRANCE]->textureID = LoadTGA("Image//InteractiveBlocks//PortalGate_1.tga");
	meshList[GEO_PORTAL_GATE_EXIT] = MeshBuilder::GenerateQuad("Portal gate 2", Color(1, 1, 1));
	meshList[GEO_PORTAL_GATE_EXIT]->textureID = LoadTGA("Image//InteractiveBlocks//PortalGate_2.tga");
	meshList[GEO_COIN] = MeshBuilder::GenerateQuad("coin", Color(1, 1, 1));
	meshList[GEO_COIN]->textureID = LoadTGA("Image//InteractiveBlocks//coin.tga");
	meshList[GEO_HEALTHPOTION] = MeshBuilder::GenerateQuad("health", Color(1, 1, 1));
	meshList[GEO_HEALTHPOTION]->textureID = LoadTGA("Image//InteractiveBlocks//Health_Potion.tga");

	// Enemy
	meshList[GEO_ZOMBIE] = MeshBuilder::GenerateSpriteAnimation("Zombie", Color(1, 1, 1), 2, 4 ,1.f);
	meshList[GEO_ZOMBIE]->textureID = LoadTGA("Image//Enemy//ZombieAnimation.tga");
	meshList[GEO_SKELETONARCHER] = MeshBuilder::GenerateSpriteAnimation("skeleton archer", Color(1, 1, 1), 2 , 3 ,1.f);
	meshList[GEO_SKELETONARCHER]->textureID = LoadTGA("Image//Enemy//SkeletonAnimation2.tga");
	meshList[GEO_HEAVYSKELEARCHER] = MeshBuilder::GenerateSpriteAnimation("heavy skeleton archer", Color(1, 1, 1), 2, 3, 1.f);
	meshList[GEO_HEAVYSKELEARCHER]->textureID = LoadTGA("Image//Enemy//HeavySkeleArcherAnimation.tga");
	meshList[GEO_SPIDER] = MeshBuilder::GenerateSpriteAnimation("Spider", Color(1, 1, 1), 3, 6,1.f);
	meshList[GEO_SPIDER]->textureID = LoadTGA("Image//Enemy//SpiderAnimation.tga");
	meshList[GEO_NYMPH] = MeshBuilder::GenerateQuad("Nymph", Color(1, 1, 1));
	meshList[GEO_NYMPH]->textureID = LoadTGA("Image//Enemy//nymph.tga");
	meshList[GEO_TURRET] = MeshBuilder::GenerateSpriteAnimation("turret", Color(1, 1, 1), 2, 3,1.f);
	meshList[GEO_TURRET]->textureID = LoadTGA("Image//Enemy//TurretAnimation.tga");
	meshList[GEO_BOOMER] = MeshBuilder::GenerateSpriteAnimation("boomer", Color(1, 1, 1), 5, 6, 1.f);
	meshList[GEO_BOOMER]->textureID = LoadTGA("Image//Enemy//BoomerAnimation2.tga");
	meshList[GEO_DEMONLORD] = MeshBuilder::GenerateSpriteAnimation("demonlord", Color(1, 1, 1), 1, 3, 1.f);
	meshList[GEO_DEMONLORD]->textureID = LoadTGA("Image//Enemy//DemonLord_animation.tga");
	meshList[GEO_DEMONLORD_PORTAL] = MeshBuilder::GenerateQuad("demonlord portal", Color(1, 1, 1), 1);
	meshList[GEO_DEMONLORD_PORTAL]->textureID = LoadTGA("Image//Enemy//DemonLord_Portal.tga");

	//Weapons
	meshList[GEO_ARROW] = MeshBuilder::GenerateQuad("arrow", Color(1, 1, 1));
	meshList[GEO_ARROW]->textureID = LoadTGA("Image//PROJECTILES//arrow_hitbox.tga");
	meshList[GEO_MAGICBALL] = MeshBuilder::GenerateSpriteAnimation("magicball", Color(1, 1, 1), 2, 3, 1.f);
	meshList[GEO_MAGICBALL]->textureID = LoadTGA("Image//PROJECTILES//energy_ball_animation_hitbox.tga");
	meshList[GEO_PORTAL] = MeshBuilder::GenerateQuad("portal", Color(1, 1, 1));
	meshList[GEO_PORTAL]->textureID = LoadTGA("Image//PROJECTILES//portal_hitbox.tga");

	//enemy projectiles
	meshList[GEO_TURRETBULLET] = MeshBuilder::GenerateQuad("turret bullet", Color(1, 1, 1));
	meshList[GEO_TURRETBULLET]->textureID = LoadTGA("Image//PROJECTILES//turret_bullet.tga");
	meshList[GEO_SKELEARROW] = MeshBuilder::GenerateQuad("arrow", Color(1, 1, 1));
	meshList[GEO_SKELEARROW]->textureID = LoadTGA("Image//PROJECTILES//arrow.tga");
	meshList[GEO_SPIDERWEB] = MeshBuilder::GenerateQuad("spiderweb", Color(1, 1, 1));
	meshList[GEO_SPIDERWEB]->textureID = LoadTGA("Image//PROJECTILES//Cobweb.tga");
	meshList[GEO_DEMONBALL_CHARGE] = MeshBuilder::GenerateSpriteAnimation("charge demonball", Color(1, 1, 1), 3, 3, 1.f);
	meshList[GEO_DEMONBALL_CHARGE]->textureID = LoadTGA("Image//PROJECTILES//DemonBall_Charging_animation.tga");
	meshList[GEO_DEMONBALL] = MeshBuilder::GenerateQuad("demonball", Color(1, 1, 1), 1.f);
	meshList[GEO_DEMONBALL]->textureID = LoadTGA("Image//PROJECTILES//DemonBall.tga");

	// BACKGROUND
	meshList[GO_BACKGROUND_1] = MeshBuilder::GenerateQuad("background 1", Color(1, 1, 1));
	meshList[GO_BACKGROUND_1]->textureID = LoadTGA("Image//BACKGROUND//Test_background.tga");
	meshList[GO_BACKGROUND_CAVE] = MeshBuilder::GenerateQuad("background cave", Color(1, 1, 1));
	meshList[GO_BACKGROUND_CAVE]->textureID = LoadTGA("Image//BACKGROUND//Cave_background.tga");
	meshList[GO_BACKGROUND_DARK_FOREST] = MeshBuilder::GenerateQuad("background dark forest", Color(1, 1, 1));
	meshList[GO_BACKGROUND_DARK_FOREST]->textureID = LoadTGA("Image//BACKGROUND//Dark_Forest_Background.tga");
	meshList[GO_BACKGROUND_DARK_FOREST_MISTY] = MeshBuilder::GenerateQuad("background dark forest", Color(1, 1, 1));
	meshList[GO_BACKGROUND_DARK_FOREST_MISTY]->textureID = LoadTGA("Image//BACKGROUND//Dark_Forest_Background_Misty.tga");
}

CentralMesh::~CentralMesh()
{
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if (meshList[i])
		{
			delete meshList[i];
			meshList[i] = nullptr;
		}
	}
}
