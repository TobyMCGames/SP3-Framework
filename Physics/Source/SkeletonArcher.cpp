#include "SkeletonArcher.h"
#include "GameLevelManager.h"
#include "ProjectileFactory.h"
#include "SkeleArrow.h"

SkeletonArcher::SkeletonArcher()
{
	shootCounter = 0;
}

SkeletonArcher::~SkeletonArcher()
{
}

void SkeletonArcher::Update(double dt, float m_speed)
{
	
	normal = ((Player::GetInstance()->pos - pos).Normalize());
	//normal.x = 45;
	//normal.y = 45;
	vel += GamePhysics::GetInstance()->gravity * dt * m_speed;
	//cout << normal << endl;

	if (shootCounter > MaxFirerate)
	{
		Projectile* skelearrow =
			ProjectileFactory::GetInstance()->produceProjectile(ProjectileFactory::PTYPE_SKELEARROW,
				pos + (normal * scale.x), normal, scale, normal);
		GameLevelManager::GetInstance()->getcurrentLevel()->getProjectileList()->push_back(skelearrow);
		//cout << "Skelearrow created" << endl;
		shootCounter = 0;
		float test = (Player::GetInstance()->pos.x) - pos.x;
		float time = test / (normal * skelearrow->Default_Speed).x;
		//float 
	}
	shootCounter++;

}

void SkeletonArcher::Response(GameObject* go)
{
}

void SkeletonArcher::dead()
{
	this->active = false;
}

