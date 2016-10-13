#pragma once
#include "TransformLayout.h"
#include "CollisionInfo.h"
#include "CollisionTester.h"
#include "Component.h"
#include "SpatialComponent.h"
class MeshComponent;
class EntityManager;

class ObjectSelectorComponent :
	public Component
{
public:
	enum TransformationType
	{
		Move,
		Scale,
		Rotate
	};

	ObjectSelectorComponent();
	~ObjectSelectorComponent();

	TransformationType curType;
	virtual bool Initialize() override;
	void ProcessKeys();
	void ProcessMousePress(QMouseEvent* e, EntityManager* entityManager);
	void GetVerts(QMouseEvent* e);
	bool CastRayFromMousePosition(QMouseEvent* e, glm::vec3 pos0, glm::vec3 pos1, glm::vec3 pos2);
	inline void SetMeshs(int num, MeshComponent* m_Meshes)
	{
		numMeshes = num;
		this->meshes = m_Meshes;
	}

private:
	SpatialComponent* spatial;
	CollisionTester collisionTester;
	CollisionInfo* info;
	float objSelectedMinT;
	int objSelected;
	MeshComponent* meshes;
	int numMeshes;
};

