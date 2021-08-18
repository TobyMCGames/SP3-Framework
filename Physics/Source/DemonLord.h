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
	virtual void Update(double dt);
	virtual void Response(GameObject*);
};