#include "ObjectSelectorComponent.h"
#include <Windows.h>
#include "MeshComponent.h"
#include "EntityManager.h"
#include "DetailsLayout.h"
#include <QtGui\qmouseevent>
#include "Vertex.h"
#include "CameraComponent.h"
#include "Physics\Vector3.h"
#include "gtc\matrix_transform.hpp"
#include "gtx\transform.hpp"
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
	return true;
}

void ObjectSelectorComponent::ProcessKeys()
{
	if (GetAsyncKeyState(Qt::Key::Key_Shift) & 0x8000)
	{
		if (GetAsyncKeyState(Q) & 0x8000)
		{
			curType = Move;
		}
		else if (GetAsyncKeyState(W) & 0x8000)
		{
			curType = Scale;
		}
		else if (GetAsyncKeyState(R) & 0x8000)
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
			if (entityManager->CurrentlySelectedObject() != objSelected)
			{
				entityManager->SetCurrentlySelectedObject(objSelected);
			}
			objSelected = -1;
			objSelectedMinT = FLT_MAX;
		}
	}
}

void ObjectSelectorComponent::GetVerts(QMouseEvent * e)
{
	for (int i = 0; i < numMeshes; i++)
	{
		Geometry* geo = meshes[i]->renderinfo.getGeometry();
		TransformInfo* tranInfo = meshes[i]->renderinfo.getTransformInfo();
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

bool ObjectSelectorComponent::CastRayFromMousePosition(QMouseEvent * qme, glm::vec3 pos0, glm::vec3 pos1, glm::vec3 pos2)
{
	CameraComponent* camera = GetSiblingComponent<CameraComponent>();
	SpatialComponent* spatial = GetSiblingComponent<SpatialComponent>();
	Imgn::Vector3 Direction = camera->viewDirection;
	Imgn::Vector3 Position = spatial->GetPosition();

	float x = qme->pos().x();
	float y = 0 - (qme->pos().y() - screenHeight);
	x = x / screenWidth * 2 - 1.0f;
	y = y / screenHeight * 2 - 1.0f;

	Imgn::Vector3 screenHoritzontally = glm::cross(Direction, glm::vec3(0,1,0));
	screenHoritzontally.normalize();
	Imgn::Vector3 screenVertically = glm::cross(screenHoritzontally, Direction);
	screenVertically.normalize();

	//should only be called when screen changes.
	float fov = 90;
	float nearClippingPlane = 1.0f;
	float radians = (float)(fov * R_PI / 180.0f);
	float halfHeight = (float)(tan(radians / 2) * nearClippingPlane);
	float halfScaledAspectRatio = halfHeight * (screenWidth/screenHeight);

	screenVertically *= halfHeight;
	screenHoritzontally *= halfScaledAspectRatio;

	Imgn::Vector3 pos = Position + Direction;
	pos += (screenVertically*y + screenHoritzontally*x);
	Imgn::Vector3 dir = pos - Position;

	float tempMinT = CollisionTester::rayTriangleIntersect(Position, dir, pos0, pos1, pos2, info->minT);
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

float ObjectSelectorComponent::screenWidth = 0;
float ObjectSelectorComponent::screenHeight = 0;

