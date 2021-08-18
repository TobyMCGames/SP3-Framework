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
	void Update(double dt);
	void Response(GameObject* go);
};