#include "ObjectSelectorComponent.h"
#include <Windows.h>
#pragma warning(push)
#pragma warning (disable:4201)
#include "MeshComponent.h"
#pragma warning(pop)
#include "EntityManager.h"
#define Q 81
#define W 87
#define R 82


ObjectSelectorComponent::ObjectSelectorComponent()
{
}

ObjectSelectorComponent::~ObjectSelectorComponent()
{
}

bool ObjectSelectorComponent::Initialize()
{
	objSelectedMinT = FLT_MAX;
	objSelected = -1;
	spatial = this->GetSiblingComponent<SpatialComponent>();
	if (!spatial)
	{
		return false;
	}
	return true;
}

void ObjectSelectorComponent::ProcessKeys()
{
	if (GetAsyncKeyState(Qt::Key::Key_Shift) != 0)
	{
		if (GetAsyncKeyState(Q) != 0)
		{
			curType = Move;
		}
		else if (GetAsyncKeyState(W) != 0)
		{
			curType = Scale;
		}
		else if (GetAsyncKeyState(R) != 0)
		{
			curType = Rotate;
		}
	}
}

void ObjectSelectorComponent::ProcessMousePress(QMouseEvent * e,EntityManager* entityManager)
{
	if (e->button() & Qt::RightButton)
	{
		GetVerts(e);
		if (objSelected != -1)
		{
			entityManager->currentlySelectedObject = objSelected;
			TransformLayout::SetTextBoxValues();
			objSelected = -1;
			objSelectedMinT = FLT_MAX;
		}
	}
}

void ObjectSelectorComponent::GetVerts(QMouseEvent * e)
{
	for (int i = 0; i < numMeshes; i++)
	{
		Geometry* geo = meshes[i].renderinfo.getGeometry();
		TransformInfo* tranInfo = meshes[i].renderinfo.getTransformInfo();
		int numVerts = geo->m_indexCount;
		info = new CollisionInfo(FLT_MAX);
		glm::vec3 offset(tranInfo->ModelViewProjectionMatrix[3].x, tranInfo->ModelViewProjectionMatrix[3].y, tranInfo->ModelViewProjectionMatrix[3].z);
		switch (geo->VertexFormat)
		{
		case PositionOnly:
		{
			vPosition* P = reinterpret_cast<vPosition*>(geo->vertices);
			for (int j = 0; j < numVerts; j += 3)
			{
				if(CastRayFromMousePosition(e, P[j].position, P[j + 1].position, P[j + 2].position))
				{
					break;
				}
			}
			break;
		}
		case PositionColor:
		{
			vPositionColor* PC = reinterpret_cast<vPositionColor*>(geo->vertices);
			for (int j = 0; j < numVerts; j += 3)
			{
				if(CastRayFromMousePosition(e, PC[j].position, PC[j + 1].position, PC[j + 2].position))
				{
					break;
				}
			}
			break;
		}
		case PositionColorNormal:
		{
			vPositionColorNormal* PCN = reinterpret_cast<vPositionColorNormal*>(geo->vertices);
			for (int j = 0; j < numVerts; j += 3)
			{
				if(CastRayFromMousePosition(e, PCN[j].position, PCN[j + 1].position, PCN[j + 2].position))
				{
					break;
				}
			}
			break;
		}
		case PositionColorTexture:
		{
			vPositionColorTexture* PCT = reinterpret_cast<vPositionColorTexture*>(geo->vertices);
			for (int j = 0; j < numVerts; j += 3)
			{
				if(CastRayFromMousePosition(e, PCT[j].position, PCT[j + 1].position, PCT[j + 2].position))
				{
					break;
				}
			}
			break;
		}
		case PositionTexture:
		{
			vPositionTexture* PT = reinterpret_cast<vPositionTexture*>(geo->vertices);
			for (int j = 0; j < numVerts; j += 3)
			{
				if (CastRayFromMousePosition(e, offset + PT[j].position, offset + PT[j + 1].position, offset + PT[j + 2].position ))
				{
					break;
				}
			}
			break;
		}
		case PositionNormal:
		{
			vPositionNormal* PN = reinterpret_cast<vPositionNormal*>(geo->vertices);
			for (int j = 0; j < numVerts; j += 3)
			{
				if (CastRayFromMousePosition(e, PN[j].position, PN[j + 1].position, PN[j + 2].position))
				{
					break;
				}
			}
			break;
		}
		case PositionTextureNormal:
		{
			vPositionTextureNormal* PTN = reinterpret_cast<vPositionTextureNormal*>(geo->vertices);
			for (int j = 0; j < numVerts; j += 3)
			{
				if (CastRayFromMousePosition(e, offset + PTN[j].position, offset + PTN[j + 1].position, offset + PTN[j + 2].position))
				{
					break;
				}
			}
			break;
		}
		case PositionColorTextureNormal:
		{
			vPositionColorTextureNormal* PCTN = reinterpret_cast<vPositionColorTextureNormal*>(geo->vertices);
			for (int j = 0; j < numVerts; j += 3)
			{
				if (CastRayFromMousePosition(e, PCTN[j].position, PCTN[j + 1].position, PCTN[j + 2].position))
				{
					break;
				}
			}
			break;
		}
		}
		if (info->minT < objSelectedMinT)
		{
			objSelectedMinT = info->minT;
			objSelected = i;
		}
		delete info;
	}
}

bool ObjectSelectorComponent::CastRayFromMousePosition(QMouseEvent * e, glm::vec3 pos0, glm::vec3 pos1, glm::vec3 pos2)
{
	e;
	CameraComponent* camera = this->GetSiblingComponent<CameraComponent>();
	glm::vec3 Direction = camera->viewDirection;
	glm::vec3 Position = spatial->position;
	
	//CollisionInfo info = CollisionInfo(FLT_MAX);

	float tempMinT = CollisionTester::rayTriangleIntersect(Position, Direction, pos0, pos1, pos2, info->minT);
	if (tempMinT < info->minT)
	{
		info->minT = tempMinT;
		info->p0 = pos0;
		info->p1 = pos1;
		info->p2 = pos2;
		return true;
	}

	return false;
}

