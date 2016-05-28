#include "EvasionComponent.h"
#include "SpatialComponent.h"


EvasionComponent::EvasionComponent()
{
}


EvasionComponent::~EvasionComponent()
{
}

bool EvasionComponent::Update(float dt)
{
	SpatialComponent* spatial = this->GetSiblingComponent<SpatialComponent>();
	if (!spatial)
	{
		string s = ": can not obtain Spatial Component";
		GameLogger::log(this->GetName() + s);
		GameLogger::shutdownLog();
		return false;
	}
	m_velocity = Evasion(spatial->position);

	spatial->position += m_velocity * dt;
	return true;
}
