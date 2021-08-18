#include "Entity.h"

class DisguisedEnemy : public Entity
{
protected:
	enum BEHAVIOUR
	{
		// insert more states here
		NUM_STATES,
	};
public:
	DisguisedEnemy();
	~DisguisedEnemy();
	void Update(double dt);
	void Response(GameObject* go);
};