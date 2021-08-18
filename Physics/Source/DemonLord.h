#include "Entity.h"

class DemonLord : public Entity
{
protected:
	enum BEHAVIOUR
	{
		// insert more states here
		NUM_STATES,
	};
public:
	DemonLord();
	~DemonLord();
	void Update(double dt);
	void Response(GameObject* go);
};