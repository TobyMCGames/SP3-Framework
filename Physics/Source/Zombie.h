#include "Entity.h"

class Zombie : public Entity
{
protected:
	enum BEHAVIOUR
	{
		// insert more states here
		NUM_STATES,
	};
public:
	Zombie();
	~Zombie();
	virtual void Update(double dt);
	virtual void Response(GameObject* go);
};