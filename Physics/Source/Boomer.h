#include "Entity.h"

class Boomer : public Entity
{
protected:
	enum BEHAVIOUR
	{
		// insert more states here
		NUM_STATES,
	};
public:
	Boomer();
	~Boomer();
	void Update(double dt);
	void Response(GameObject*);
};