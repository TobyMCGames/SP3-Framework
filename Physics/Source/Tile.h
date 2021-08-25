#include "GameObject.h"
class Tile : public GameObject
{
protected:
	enum TILE_TYPE
	{
		PASSIVE_TILE,
		AGGRO_TILE,
		INTERACTIVE_TILE
	};
	TILE_TYPE tiletype;
public:
	Tile();
	~Tile();
	void Response(GameObject* go);
	void Render();
	bool getDestructable();
	void setDestructable(bool destructable);

private:
	bool destructable;

};