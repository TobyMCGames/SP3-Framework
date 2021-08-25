#ifndef BOMB_H
#define BOMB_H

#include "Projectile.h"
#include <vector>
class Bomb : public Projectile
{
public:
	virtual void Update(double dt, float m_speed);
	virtual void Response(GameObject* go);
	virtual void Render();
	void explode(std::vector<GameObject*> tilelist,std::vector<GameObject*> entityList);

	Bomb();
	~Bomb();

private:
	float bomb_TimeLeft;
	const int explosionRange = 3;
	const float bombTimer = 5;
	
};
#endif