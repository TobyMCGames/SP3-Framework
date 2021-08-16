#include "GameObject.h"

class Projectile : public GameObject
{
protected:
	enum STATES
	{
		// insert more states here
		NUM_STATES,
	};
public:
	Projectile();
	~Projectile();
	virtual void Update(double dt) = 0;
};