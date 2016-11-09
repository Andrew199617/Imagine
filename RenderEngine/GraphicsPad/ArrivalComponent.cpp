#include "ArrivalComponent.h"
#include "SpatialComponent.h"


ArrivalComponent::ArrivalComponent()
{
}


ArrivalComponent::~ArrivalComponent()
{
}

void ArrivalComponent::Update(float dt)
{
	SpatialComponent* spatial = this->GetSiblingComponent<SpatialComponent>();
	if (!spatial)
	{
		string s = ": can not obtain Spatial Component";
		GameLogger::log(this->GetName() + s);
		GameLogger::shutdownLog();
	}
	m_velocity = Arrival(spatial->GetPosition(),3);
	spatial->SetPosition(spatial->GetPosition() + m_velocity * dt);

	if (spatial->GetPosition().z < m_target.z + 1.0f)
	{
		spatial->SetPosition(spatial->GetPosition() + glm::vec3(0, 0, -40));
	}
}
