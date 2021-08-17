#include "Entity.h"
#include "Prototype.h"

class Zombie : public Entity, public Prototype<Zombie>
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
	void Update(double dt);
	void Response(GameObject*);
};