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
	m_velocity = Arrival(spatial->position,3);
	spatial->position += m_velocity * dt;

	if (spatial->position.z < m_target.z + 1.0f)
	{
		spatial->position.z = -40;
	}
}
