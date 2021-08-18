#include "Entity.h"

class Spider : public Entity
{
protected:
	enum BEHAVIOUR
	{
		// insert more states here
		NUM_STATES,
	};
public:
	Spider();
	~Spider();
	void Update(double dt);
	void Response(GameObject* go);
};