#include "SceneBase.h"
#include "Player.h"
#include <vector>

class GameLevelBase : public SceneBase
{
protected:
	std::vector<GameObject*>map;
	Player* player;
public:
	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Destroy();
	bool SetMap();
	//bool SetMap(string);
};