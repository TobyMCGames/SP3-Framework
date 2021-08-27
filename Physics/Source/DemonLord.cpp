#include "DemonLord.h"
#include "CentralMesh.h"
#include "MeshRender.h"

DemonLord::DemonLord()
	: Floating(NULL)
	, portalSpinTime(0)
	, portalScale(1.5, 1.5, 1)
{
	curFSM = ARRIVAL;
	portalSpinTime = 6.f;

	Floating = new SpriteAnimation(CentralMesh::GetInstance()->GetMeshID(CentralMesh::GEO_DEMONLORD));
	Floating->AddAnimation("Floating", 0, 2);
	Floating->PlayAnimation("Floating", -1, 1.5);
}

DemonLord::~DemonLord()
{
	return;
}

void DemonLord::Update(double dt,float m_speed)
{
	switch (curFSM)
	{
	case ARRIVAL:
		if (portalSpinTime > 3)
		{
			float angle = 720 * (portalSpinTime - 3.f) / 3.f;
			normal.Rotate(angle * dt);
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
			curFSM = IDLE;
		}
	}
	if (Floating != NULL)
	{
		Floating->Update(dt * m_speed);
	}
	return;
}

void DemonLord::Response(GameObject* go) 
{
	std::cout << "Dlord response" << std::endl;
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
				modelStack->Translate(0, -0.035, 0.001);
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
	}
}

void DemonLord::dead()
{
	this->active = false;
}

