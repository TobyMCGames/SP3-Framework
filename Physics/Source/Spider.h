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
	virtual void Update(double dt);
	virtual void Response(GameObject*);
};