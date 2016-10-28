#include "RigidBody.h"
#include "..\SpatialComponent.h"
#include "..\MeshComponent.h"

RigidBody::~RigidBody()
{
}

void RigidBody::Awake()
{
	spatial = GetSiblingComponent<SpatialComponent>();
	transformMatrix = &this->GetSiblingComponent<MeshComponent>()->renderinfo.getTransformInfo()->ModelViewProjectionMatrix;
}

bool RigidBody::Initialize()
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool RigidBody::Update(float)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void RigidBody::SetInertiaTensor(const glm::mat3 InertiaTensor)
{
	inverseInertiaTensor = InertiaTensor._inverse();
	//_checkInverseInertiaTensor(inverseInertiaTensor);
}
