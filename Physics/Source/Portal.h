#ifndef PORTAL_H
#define PORTAL_H

#include "Projectile.h"
#include "InteractableFactory.h"
#include <vector>

class Portal : public Projectile
{
private:
	enum COLLIDEPOS
	{
		NOTHING,
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	//void PortalcleanupList(vector<int>* indexlist);
	int getIndex(AdvanceGO* K);
public:
	virtual void Update(double dt, float m_speed);
	virtual void Response(GameObject* go);
	virtual void Render();
	Portal();
	~Portal();
};
#endif