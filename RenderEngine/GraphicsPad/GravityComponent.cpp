#include "GravityComponent.h"
#include "OriginalGame.h"
#include "MeshComponent.h"
#include "CollisionTester.h"
#include "Vertex.h"
#include "SpatialComponent.h"
#include "CollisionInfo.h"
#include "glm.hpp"

#define CASE(caseValue,VertexFormat) case caseValue: { VertexFormat* vertex = reinterpret_cast<VertexFormat*>(geo->vertices); \
			for (int j = 0; j < numVerts; j += 3) \
			{ \
				if (SomethingIsBelow(vertex[j].position, vertex[j + 1].position, vertex[j + 2].position)) \
				{ \
					break; \
				} \
			}break;} \

GravityComponent::~GravityComponent()
{
}

void GravityComponent::fall(float)
{
}

bool GravityComponent::SomethingIsBelow(glm::vec3 pos0, glm::vec3 pos1, glm::vec3 pos2)
{
	glm::vec3 Direction = glm::vec3(0,-1,0);
	glm::vec3 Position = spatial->GetPosition();

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

void GravityComponent::GetVerts()
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
		CASE(PositionOnly,vPosition)
		CASE(PositionColor, vPositionColor)
		CASE(PositionColorNormal, vPositionColorNormal)
		CASE(PositionColorTexture, vPositionColorTexture)
		CASE(PositionTexture, vPositionTexture)
		CASE(PositionNormal, vPositionNormal)
		CASE(PositionTextureNormal, vPositionTextureNormal)
		CASE(PositionColorTextureNormal, vPositionColorTextureNormal)
		}
		if (info->minT < objSelectedMinT)
		{
			objSelectedMinT = info->minT;
			floorCollision = (info->p0.x + info->p1.y + info->p2.z)/3;
		}
		delete info;
	}
}

void GravityComponent::Update(float dt)
{
	spatial = this->GetSiblingComponent<SpatialComponent>();
	if (!spatial)
	{
		string s = ": can not obtain a Component";
		GameLogger::log(this->GetName() + s);
		GameLogger::shutdownLog();
	}

	//should check to see the scene output format and do a switch
	GetVerts();

	if (objSelectedMinT > 0.05f + DistanceFromWall)
	{
		fall(dt);
	}
	/*else if (objSelectedMinT <= 0.05f)
	{
		spatial->position.y = floorCollision + .05f;
	}*/
	objSelectedMinT = FLT_MAX;
}

bool GravityComponent::Initialize()
{
	floorCollision = 0;
	objSelectedMinT = FLT_MAX;
	numMeshes = OriginalGame::entityManager.num_Objs;
	meshes = OriginalGame::entityManager.entitieMeshs;
	return true;
}

