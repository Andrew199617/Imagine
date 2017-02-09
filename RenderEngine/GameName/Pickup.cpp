#include "Pickup.h"
#include "SpatialComponent.h"
#include "Physics\PhysicsTypeDefs.hpp"

Pickup::~Pickup()
{

}

void Pickup::Update(float dt)
{
	SpatialComponent* spatial = GetSiblingComponent<SpatialComponent>();
	if (spatial)
	{
		spatial->SetRotation(spatial->GetRotation() + glm::vec3(rotationSpeed,0,0));
		spatial->UpdateRotate();
	}
}

