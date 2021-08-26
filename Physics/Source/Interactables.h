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

struct WarpGate : public Interactables
{
	WarpGate() { type = GameObject::WARP_GATE; };
	~WarpGate() {};
	virtual void Update(double dt, float m_speed) {};
	virtual void Response(GameObject* go) {};
	virtual void Render() {};
};

struct BombCrate : public Interactables
{
	BombCrate(GameObject::GAMEOBJECT_TYPE cratetype) { type = cratetype; };
	~BombCrate() {};
	virtual void Update(double dt, float m_speed) {};
	virtual void Response(GameObject* go) {};
	virtual void Render() {};
};

struct VineSeeds : public Interactables
{
	VineSeeds(GameObject::GAMEOBJECT_TYPE gotype) { type = gotype; };
	~VineSeeds() {};
	virtual void Update(double dt, float m_speed) {};
	virtual void Response(GameObject* go) {};
	virtual void Render() {};
};

struct TreeSeeds : public Interactables
{
	TreeSeeds(GameObject::GAMEOBJECT_TYPE gotype) { type = gotype; };
	~TreeSeeds() {};
	virtual void Update(double dt, float m_speed) {};
	virtual void Response(GameObject* go) {};
	virtual void Render() {};
};

struct Tree : public Interactables
{
	Tree(GameObject::GAMEOBJECT_TYPE gotype) { type = gotype; };
	~Tree() {};
	virtual void Update(double dt, float m_speed) {};
	virtual void Response(GameObject* go) {};
	virtual void Render() {};
};