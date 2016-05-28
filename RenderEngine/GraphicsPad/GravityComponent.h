#pragma once
#include "Component.h"
#include "CollisionTester.h"
#include "Vertex.h"
#include "CameraComponent.h"
#include "SpatialComponent.h"
#include "MeshComponent.h"
#include "CollisionInfo.h"
#include "RenderEngine\RenderInfo.h"
#include <Windows.h>
#pragma warning(push)
#pragma warning (disable:4127)
#include <QtGui\qkeyevent>
#pragma warning(pop)

class SpatialComponent;

class GravityComponent :
	public Component
{
public:
	GravityComponent();
	~GravityComponent();

	void fall(SpatialComponent* spatial,float dt);
	CollisionInfo SomethingIsBelow(SpatialComponent*);
	//CollisionInfo WallCollision();
	virtual bool Update(float dt) override;
	virtual bool Initialize() override;

	//should be a pointer to an array meshes to cast for now im onlyusing dans hideout
	RenderInfo* DansMesh;
	float DistanceFromGround;
	float DistanceFromWall;
	float GravitySpeed;
};

