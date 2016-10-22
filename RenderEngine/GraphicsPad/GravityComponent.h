#pragma once
#include "ImgnComponent.h"
#include "glm.hpp"
#include "ImgnProperties.h"
struct CollisionInfo;
class MeshComponent;
class SpatialComponent;

class GravityComponent :
	public ImgnComponent
{
	IMGN_GENERATE(GravityComponent)
	IMGN_PROPERTY(GravitySpeed, 0.98f)
	IMGN_PROPERTY(DistanceFromWall, 0)
	IMGN_END(GravityComponent)
public:

	void fall(float dt);
	bool SomethingIsBelow(glm::vec3 pos0, glm::vec3 pos1, glm::vec3 pos2);
	void GetVerts();
	virtual bool Update(float dt) override;
	virtual bool Initialize() override;
	void SetMeshes() {}

private:
	int numMeshes;
	CollisionInfo* info;
	float floorCollision;
	float objSelectedMinT;
	MeshComponent** meshes;
	SpatialComponent* spatial;

	int DistanceFromWall;
	float GravitySpeed;
};

