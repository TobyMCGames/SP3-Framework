#include "Entity.h"

class SkeletonArcher : public Entity
{
protected:
	enum BEHAVIOUR
	{
		// insert more states here
		NUM_STATES,
	};
public:
	SkeletonArcher();
	~SkeletonArcher();
	virtual void Update(double dt);
	virtual void Response(GameObject* go);
};