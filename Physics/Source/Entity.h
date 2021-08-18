#include "GameObject.h"
//#include "Projectile.h"

class Entity : public GameObject
{
protected:
	enum STATES
	{
		STATE_NORMAL,
		STATE_INVINCIBLE,
		STATE_FROZEN,
		NUM_STATES,
	};

	enum LOCATION
	{
		ON_GROUND,
		IN_AIR
	};

	STATES curState;
	LOCATION curLocation;

public:
	Entity();
	~Entity();
	virtual void Update(double dt) = 0;
	virtual void Response(GameObject* go) = 0;
};