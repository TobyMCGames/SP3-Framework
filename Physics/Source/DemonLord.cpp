#include "DemonLord.h"
#include "CentralMesh.h"
#include "MeshRender.h"
#include "ProjectileFactory.h"
#include "GameLevelManager.h"
#include "Player.h"

DemonLord::DemonLord()
	: Floating(NULL)
	, portalSpinTime(0)
	, portalScale(0, 0, 1)
	, FSMcounter(0)
{
	health = 3500;
	//health = 300;
	curFSM = ARRIVAL;
	portalSpinTime = 6.f;

	Floating = new SpriteAnimation(CentralMesh::GetInstance()->GetMeshID(CentralMesh::GEO_DEMONLORD));
	Floating->AddAnimation("Floating", 0, 2);
	Floating->PlayAnimation("Floating", -1, 0.5);

	Charging = new SpriteAnimation(CentralMesh::GetInstance()->GetMeshID(CentralMesh::GEO_DEMONBALL_CHARGE));
	Charging->AddAnimation("Charging", 0, 8);
}

DemonLord::~DemonLord()
{
	delete Floating;
	delete Charging;
	return;
}

void DemonLord::Update(double dt,float m_speed)
{
	switch (curFSM)
	{
	case ARRIVAL:
		if (portalSpinTime > 3)
		{
			float angle = 715 * (portalSpinTime - 3.f) / 3.f;
			normal.Rotate(angle * dt);
			portalScale.x += 0.5 * dt;
			portalScale.y += 0.5 * dt;
			portalSpinTime -= dt;
		}
		else if (portalSpinTime <= 3 && portalSpinTime > 0)
		{
			normal.Set(1, 0, 0);
			portalScale.x -= 0.5 * dt;
			portalSpinTime -= dt;
		}
		else
		{
			FSMcounter = 2.f;
			curFSM = IDLE;
		}
		break;
	case IDLE:
		if (FSMcounter > 0)
		{
			FSMcounter -= dt;
		}
		else
		{
			FSMcounter = 2.f;
			Charging->PlayAnimation("Charging", 1, 2.f);
			Charging->Reset();
			curFSM = ATTACK_DEMONBALL;
		}
		break;
	case ATTACK_DEMONBALL:
		if (FSMcounter > 0)
		{
			Charging->Update(dt);
			FSMcounter -= dt;
		}
		else
		{
			Vector3 direction = (Player::GetInstance()->pos - pos).Normalized();
			AdvanceGO* temp;
			temp = ProjectileFactory::GetInstance()->produceProjectile(
				ProjectileFactory::PTYPE_DEMONBALL,
				pos,
				direction,
				Vector3(10, 10, 1),
				Vector3(1, 0, 0)
			);
			GameLevelManager::GetInstance()->getcurrentLevel()->getProjectileList()->push_back(temp);
			FSMcounter = 6.f;
			curFSM = IDLE;
		}
		break;
	case RETREAT:
		if (portalSpinTime > 3)
		{
			portalScale.x += 0.5 * dt;
		}
		else if (portalSpinTime > 0)
		{
			portalScale.x -= 0.5 * dt;
		}
		else
		{
			active = false;
		}
		portalSpinTime -= dt;
		break;
	}

	if (health <= 0 && curFSM != RETREAT)
	{
		if (portalSpinTime <= 0)
		{
			portalSpinTime = 6.f;
			curFSM = RETREAT;
		}
	}
	Floating->Update(dt);
	return;
}

void DemonLord::Response(GameObject* go) 
{
	cout << health << endl;
	if (curFSM != ARRIVAL && curFSM != RETREAT)
	{
		switch (go->type)
		{
		case GO_ARROW:
		case GO_MAGICBALL:
			if ((go->pos - pos).LengthSquared() <= (scale.y / 3) * (scale.y / 3))
			{
				go->active = false;
				takeDamage(go->damage);
				CSoundController::GetInstance()->PlaySoundByID(40);
			}
			break;
		}
	}
	return;
}

void DemonLord::Render()
{
	MS* modelStack = MeshRender::GetInstance()->GetModelStack();
	switch (curFSM)
	{
	case ARRIVAL:
		modelStack->PushMatrix();
		{
			modelStack->Scale(portalScale.x, portalScale.y, portalScale.z);
			modelStack->Translate(0, -0.035, 0);
			MeshRender::GetInstance()->RenderMesh(CentralMesh::GetInstance()->GetMeshID(CentralMesh::GEO_DEMONLORD_PORTAL), false);
		}
		modelStack->PopMatrix();
		if (portalSpinTime <= 3 && portalSpinTime > 0)
		{
			modelStack->PushMatrix();
			{
				modelStack->Translate(0, -0.035, 0.0001);
				MeshRender::GetInstance()->RenderAnimation(
					Floating->GetSprite(),
					Floating->GetCurFrame(),
					6,
					false
				);
			}
			modelStack->PopMatrix();
		}
		break;
	case IDLE:
		MeshRender::GetInstance()->RenderAnimation(
			Floating->GetSprite(),
			Floating->GetCurFrame(),
			6,
			false
		);
		break;
	case ATTACK_DEMONBALL:
		MeshRender::GetInstance()->RenderAnimation(
			Floating->GetSprite(),
			Floating->GetCurFrame(),
			6,
			false
		);
		modelStack->PushMatrix();
		{
			modelStack->Translate(0, 0, 0.0001);
			modelStack->Scale(0.2, 0.2, 0.2);
			MeshRender::GetInstance()->RenderAnimation(
				Charging->GetSprite(),
				Charging->GetCurFrame(),
				6,
				false
			);
		}
		modelStack->PopMatrix();
		break;
	case RETREAT:
		modelStack->PushMatrix();
		{
			modelStack->Scale(portalScale.x, portalScale.y, portalScale.z);
			modelStack->Translate(0, -0.035, 0);
			MeshRender::GetInstance()->RenderMesh(CentralMesh::GetInstance()->GetMeshID(CentralMesh::GEO_DEMONLORD_PORTAL), false);
		}
		modelStack->PopMatrix();
		if (portalSpinTime <= 6 && portalSpinTime > 3)
		{
			modelStack->PushMatrix();
			{
				modelStack->Translate(0, -0.035, 0.0001);
				MeshRender::GetInstance()->RenderAnimation(
					Floating->GetSprite(),
					Floating->GetCurFrame(),
					6,
					false
				);
			}
			modelStack->PopMatrix();
		}
		break;
	}
}

void DemonLord::dead()
{
	this->active = false;
}

