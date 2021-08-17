#include "Entity.h"

class Turret : public Entity
{
protected:
	enum BEHAVIOUR
	{
		// insert more states here
		NUM_STATES,
	};
public:
	Turret();
	~Turret();
	void Update(double dt);
	void Response(GameObject*);
};