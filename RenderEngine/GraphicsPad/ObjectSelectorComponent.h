#pragma once
#include "CollisionInfo.h"
#include "CollisionTester.h"
#include "SpatialComponent.h"
#include "Physics\Vector3.h"
#include "RenderEngine\RenderInfo.h"
class MeshComponent;
class EntityManager;

class ObjectSelectorComponent :
	public ImgnComponent
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

	void SendDataToOpenGl();

	void ProcessKeys();
	void ProcessMousePress(QMouseEvent* e, EntityManager* entityManager);
	void GetVerts();
	bool CastRayFromMousePosition(glm::vec3 pos0, glm::vec3 pos1, glm::vec3 pos2);

	inline void SetMeshs(int num, MeshComponent** m_Meshes)
	{
		numMeshes = num;
		this->meshes = m_Meshes;
	}

	static float screenWidth;
	static float screenHeight;
	
private:
	void SetFovAndNear(float fov, float nearClippingPlane);

	bool drawRay;
private:
	RenderInfo renderinfo;
	CollisionTester collisionTester;
	CollisionInfo* info;
	float objSelectedMinT;
	int objSelected;
	MeshComponent** meshes;
	int numMeshes;

	float mouseX;
	float mouseY;
	Imgn::Vector3 dir;
	Imgn::Vector3 position;
	float halfHeight;
	float halfScaledAspectRatio;
};

