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
	virtual void Update(double dt);
	virtual void Response(GameObject*);
};