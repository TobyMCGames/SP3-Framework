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
	void Update(double dt);
	void Response(GameObject*);
};