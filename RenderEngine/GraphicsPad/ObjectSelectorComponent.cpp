#include "ObjectSelectorComponent.h"
#include <Windows.h>
#include "MeshComponent.h"
#include "EntityManager.h"
#include "DetailsLayout.h"
#include <QtGui\qmouseevent>
#include "Vertex.h"
#include "CameraComponent.h"
#include "gtc\matrix_transform.hpp"
#include "gtx\transform.hpp"
#include "RenderEngine\RenderEngine.h"
#include "ImgnViewport.h"
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
	drawRay = false;
	objSelectedMinT = FLT_MAX;
	objSelected = -1;
	return true;
}

void ObjectSelectorComponent::SendDataToOpenGl()
{
	renderinfo.setGeometry(ShapeGenerator::makeLine(position, dir * 100));
	renderinfo.setTransfromInfo(new TransformInfo(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::quat()));
	renderinfo.setTextureInfo(new TextureInfo());

	FragmentShaderInfo* fragmentShader = new FragmentShaderInfo("..\\Graphicspad\\Shader\\ctFragmentShaderCode.glsl");
	VertexShaderInfo* vertexShaderInfo = new VertexShaderInfo();
	GLuint fId = fragmentShader->createShader();
	vertexShaderInfo->installShader(fId);
	renderinfo.setVertexShaderInfo(vertexShaderInfo);

	renderinfo.color = glm::vec3(0, 1, 0);
	renderinfo.isEnabled = drawRay;
	RenderEngine::AddRenderInfo(&renderinfo);
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

void ObjectSelectorComponent::ProcessMousePress(QMouseEvent * qme,EntityManager* entityManager)
{
	if (qme->button() & Qt::RightButton)
	{
		int _objectSelectedLocal = -1;
		_objectSelectedLocal = SelectObject(qme->pos());
		if (_objectSelectedLocal != -1)
		{
			if (entityManager->CurrentlySelectedObject() != _objectSelectedLocal)
			{
				entityManager->SetCurrentlySelectedObject(_objectSelectedLocal);
			}
		}
	}
}

int ObjectSelectorComponent::SelectObject(QPoint pos)
{
	int _objectSelectedLocal = -1;
	CalculateRayDir(pos);
	GetVerts();

	if (objSelected != -1)
	{
		_objectSelectedLocal = objSelected;

		objSelected = -1;
		objSelectedMinT = FLT_MAX;
	}
	return _objectSelectedLocal;
}

void ObjectSelectorComponent::CalculateRayDir(QPoint pos)
{
	if (numMeshes > 0)
	{
		CameraComponent* camera = GetSiblingComponent<CameraComponent>();
		SpatialComponent* spatial = GetSiblingComponent<SpatialComponent>();
		Imgn::Vector3 direction = camera->viewDirection;
		position = spatial->GetPosition();

		mouseX = pos.x();
		mouseY = 0 - (pos.y() - screenHeight);
		mouseX = mouseX / screenWidth * 2 - 1.0f;
		mouseY = mouseY / screenHeight * 2 - 1.0f;

		Imgn::Vector3 screenHoritzontally = glm::cross(direction, glm::vec3(0, 1, 0));
		screenHoritzontally.normalize();
		Imgn::Vector3 screenVertically = glm::cross(screenHoritzontally, direction);
		screenVertically.normalize();

		SetFovAndNear(90, 1.0f);

		screenVertically *= halfHeight;
		screenHoritzontally *= halfScaledAspectRatio;

		Imgn::Vector3 pos = position + direction;
		pos += (screenVertically*mouseY + screenHoritzontally*mouseX);
		dir = pos - position;

		if (drawRay)
		{
			renderinfo.setGeometry(ShapeGenerator::makeLine(position, dir * 100));
		}
	}
}

void ObjectSelectorComponent::GetVerts()
{
	for (int i = 0; i < numMeshes; i++)
	{
		Geometry* geo = meshes[i]->renderinfo.getGeometry();
		TransformInfo* tranInfo = meshes[i]->renderinfo.getTransformInfo();
		int numVerts = geo->m_indexCount;
		info = new CollisionInfo(FLT_MAX);
		glm::vec3 offset(tranInfo->ModelViewProjectionMatrix[3].x, tranInfo->ModelViewProjectionMatrix[3].y, tranInfo->ModelViewProjectionMatrix[3].z);
		glm::vec3 scale(tranInfo->ModelViewProjectionMatrix[0].x, tranInfo->ModelViewProjectionMatrix[1].y, tranInfo->ModelViewProjectionMatrix[2].z);

		vPositionTextureNormal* P = reinterpret_cast<vPositionTextureNormal*>(geo->vertices);
		
		for (int j = 0; j < numVerts; j += 3)
		{
			if(CastRayFromMousePosition(offset + (P[j].position * scale),
				offset + (P[j + 1].position * scale),
				offset + (P[j + 2].position * scale)))
			{
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

bool ObjectSelectorComponent::CastRayFromMousePosition(glm::vec3 pos0, glm::vec3 pos1, glm::vec3 pos2)
{
	float tempMinT = CollisionTester::rayTriangleIntersect(position, dir, pos0, pos1, pos2, info->minT);
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

void ObjectSelectorComponent::SetFovAndNear(float fov, float nearClippingPlane)
{
	float radians = (float)(fov * R_PI / 180.0f);
	halfHeight = (float)(tan(radians / 2) * nearClippingPlane);
	halfScaledAspectRatio = halfHeight * (screenWidth / screenHeight);
}

float ObjectSelectorComponent::screenWidth = 0;
float ObjectSelectorComponent::screenHeight = 0;
