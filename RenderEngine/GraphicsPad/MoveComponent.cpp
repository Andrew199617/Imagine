#include "MoveComponent.h"
#include "SpatialComponent.h"


MoveComponent::MoveComponent()
{
}


MoveComponent::~MoveComponent()
{
}

bool MoveComponent::Update(float dt)
{
	this->GetSiblingComponent<SpatialComponent>()->velocity.x = -1.0f;
	this->GetSiblingComponent<SpatialComponent>()->position.x -= 1.0f * dt;
	return true;
}
