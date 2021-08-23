#include "GameObject.h"
class Tile : public GameObject
{
protected:
	enum TILE_TYPE
	{
		PASSIVE_TILE,
		INTERACTIVE_TILE
	};
	TILE_TYPE tiletype;
public:
	Tile();
	Tile(GameObject::GAMEOBJECT_TYPE objtype);
	~Tile();
	GameObject* clone(Vector3 pos, Vector3 vel,Vector3 scale,Vector3 Normal);
	void Response(GameObject* go);
	void Render();
};