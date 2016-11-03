#include "FleeBehaviorComponent.h"
#include "SpatialComponent.h"


FleeBehaviorComponent::FleeBehaviorComponent()
{
}


FleeBehaviorComponent::~FleeBehaviorComponent()
{
}

void FleeBehaviorComponent::Update(float dt)
{
	SpatialComponent* spatial = this->GetSiblingComponent<SpatialComponent>();
	if (!spatial)
	{
		string s = ": can not obtain Spatial Component";
		GameLogger::log(this->GetName() + s);
		GameLogger::shutdownLog();
	}
	glm::vec3 Position = spatial->position;
	m_velocity = Flee(Position, m_target, m_velocity);
	spatial->position += m_velocity * dt;
	if (spatial->position.z > -40)
	{
		spatial->position.z = -70;
	}
}

bool FleeBehaviorComponent::Initialize()
{
	
	m_velocity = glm::vec3(0.0, 0.0, 0.0);
	return true;
}

