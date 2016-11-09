#include "SeekBehaviorComponent.h"
#include "SpatialComponent.h"


SeekBehaviorComponent::SeekBehaviorComponent()
{
	m_target = glm::vec3(FLT_MAX, FLT_MAX, FLT_MAX);
}


SeekBehaviorComponent::~SeekBehaviorComponent()
{
}

void SeekBehaviorComponent::Update(float dt)
{
	SpatialComponent* spatial = this->GetSiblingComponent<SpatialComponent>();
	if (!spatial)
	{
		string s = ": can not obtain Spatial Component";
		GameLogger::log(this->GetName() + s);
		SetBreak(true);
	}
	if (m_target == glm::vec3(FLT_MAX, FLT_MAX, FLT_MAX))
	{
		string s = " : m_target was never set";
		GameLogger::log(this->GetName() + s);
	}

	m_velocity = Seek(spatial->GetPosition(),m_target);
	spatial->SetPosition(spatial->GetPosition() + m_velocity * dt);

}

bool SeekBehaviorComponent::Initialize()
{
	m_velocity = glm::vec3(0.0, 0.0, 0.0);
	return true;
}

