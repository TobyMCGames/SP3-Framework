#include "AdvanceGO.h"

class Interactables : public AdvanceGO
{
public:
	Interactables() {};
	~Interactables() {};
	virtual void Update(double dt, float m_speed) {};
	virtual void Response(GameObject* go) {};
	virtual void Render() {};
};

struct WeaponStation : public Interactables
{
	WeaponStation(GameObject::GAMEOBJECT_TYPE weapon) { type = weapon; };
	~WeaponStation() {};
	virtual void Update(double dt, float m_speed) {};
	virtual void Response(GameObject* go) {};
	virtual void Render() {};
};

struct PortalGate : public Interactables
{
	PortalGate(GameObject::GAMEOBJECT_TYPE gatetype) { type = gatetype; };
	~PortalGate() {};
	virtual void Update(double dt, float m_speed) {};
	virtual void Response(GameObject* go) {};
	virtual void Render() {};
};