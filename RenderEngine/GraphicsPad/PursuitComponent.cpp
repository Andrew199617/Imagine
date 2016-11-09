#include "PursuitComponent.h"
#include "SpatialComponent.h"


PursuitComponent::PursuitComponent()
{
}


PursuitComponent::~PursuitComponent()
{
}

void PursuitComponent::Update(float dt)
{
	SpatialComponent* spatial = this->GetSiblingComponent<SpatialComponent>();
	if (!spatial)
	{
		string s = ": can not obtain Spatial Component";
		GameLogger::log(this->GetName() + s);
		GameLogger::shutdownLog();
	}
	m_velocity = Pursuit(spatial->GetPosition());

	spatial->SetPosition(spatial->GetPosition() + m_velocity * dt);
}
