#include "SceneBase.h"
#include "Player.h"
#include "GamePhysics.h"
#include <vector>
#include <string>
using namespace std;

class GameLevelBase : public SceneBase
{
protected:
	vector<GameObject*>map;
	Player* player;
public:
	GameLevelBase();
	~GameLevelBase();
	virtual void Init() = 0;
	virtual void Update(double dt) = 0;
	virtual void Render() = 0;
	virtual void Destroy() = 0;
	bool SetMap(string);
};

