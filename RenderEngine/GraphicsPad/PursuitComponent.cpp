#include "PursuitComponent.h"
#include "SpatialComponent.h"


PursuitComponent::PursuitComponent()
{
}


PursuitComponent::~PursuitComponent()
{
}

bool PursuitComponent::Update(float dt)
{
	SpatialComponent* spatial = this->GetSiblingComponent<SpatialComponent>();
	if (!spatial)
	{
		string s = ": can not obtain Spatial Component";
		GameLogger::log(this->GetName() + s);
		GameLogger::shutdownLog();
		return false;
	}
	m_velocity = Pursuit(spatial->position);

	spatial->position += m_velocity * dt;
	return true;
}
