#pragma once
#include "..\ImgnComponent.h"
#include "..\ImgnProperties.h"
#include "glm.hpp"

class RigidBody :
	public ImgnComponent
{
	IMGN_GENERATE(RigidBody)
	IMGN_END(RigidBody)
public:
	virtual void Awake() override;
	virtual bool Initialize() override;
	virtual bool Update(float) override;

	void SetInertiaTensor(const glm::mat3 InertiaTensor);

private:
	float inverseMass;
	glm::mat4* transformMatrix;
	class SpatialComponent* spatial;
	glm::mat3 inverseInertiaTensor;;
};

