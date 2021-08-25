#ifndef CENTRALMESH_H
#define CENTRALMESH_H

#include "SingletonPattern.h"
#include "Mesh.h"
#include "Vertex.h"

class CentralMesh : public SingletonPattern<CentralMesh>
{
	friend SingletonPattern<CentralMesh>;
public:
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_TEXT,
		GEO_BALL,
		GEO_CUBE,
		GEO_QUAD,
		GEO_CYLINDER,
		GEO_BACKGROUND,
		GEO_TITLE,
		GUI_BORDER,
		GUI_PAUSE,
		GUI_RETRY,
		GUI_HEART,
		GUI_CELLS,
		GUI_ENERGY,
		GUI_HEALTHBAR,
		GUI_ENERGYBAR,
		GUI_STATS_BG,
		GUI_ATK_ICON,
		GEO_CONTROLS,
		GEO_CREDITS,

		//BACKGROUND
		GO_BACKGROUND_1,

		//PASSIVE_TILE,
		GEO_BRICK,
		GEO_PLAYER,
		GEO_STONEBRICK,
		GEO_SOIL_TILE,
		GEO_GRASS_SOIL_TILE,
		GEO_GRASS_SOIL_FLOWERS_TILE,
		GEO_SPIKE,

		GEO_WARP_GATE_TILE,

		//weapons
		GEO_BOW,
		GEO_STAFF,
		GEO_PORTALGUN,

		//Interactive objects
		GEO_WEAPON_STATION,
		GEO_PORTAL_GATE_ENTRANCE,
		GEO_PORTAL_GATE_EXIT,

		// Enemy
		GEO_ZOMBIE,
		GEO_SKELETONARCHER,
		GEO_SPIDER,
		GEO_BOOMER,
		GEO_NYMPH,
		GEO_TURRET,
		GEO_DEMONLORD,

		//projectiles
		GEO_ARROW,
		GEO_MAGICBALL,
		GEO_PORTAL,

		//enemy projectiles
		GEO_TURRETBULLET,
		GEO_SKELEARROW,
		GEO_SPIDERWEB,

		NUM_GEOMETRY,
	};

	void ChangeMat(int idx, Color color, float ambient, float diffuse, float specular, float Shiny);
	void FontLoader(std::string file_path);
	Mesh* GetMeshID(GEOMETRY_TYPE ID);
	int GetTextWidth(int ID);

protected:
	CentralMesh();
	~CentralMesh();

	int textWidth[256];

	Mesh* meshList[NUM_GEOMETRY];
};

#endif