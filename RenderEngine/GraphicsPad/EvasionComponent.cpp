#include "EvasionComponent.h"
#include "SpatialComponent.h"


EvasionComponent::EvasionComponent()
{
}


EvasionComponent::~EvasionComponent()
{
}

void EvasionComponent::Update(float dt)
{
	SpatialComponent* spatial = this->GetSiblingComponent<SpatialComponent>();
	if (!spatial)
	{
		string s = ": can not obtain Spatial Component";
		GameLogger::log(this->GetName() + s);
		GameLogger::shutdownLog();
	}
	m_velocity = Evasion(spatial->GetPosition());

	spatial->SetPosition(spatial->GetPosition() + m_velocity * dt);
}
