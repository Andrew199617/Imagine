#include "SeekBehaviorComponent.h"
#include "SpatialComponent.h"


SeekBehaviorComponent::SeekBehaviorComponent()
{
	m_target = glm::vec3(FLT_MAX, FLT_MAX, FLT_MAX);
}


SeekBehaviorComponent::~SeekBehaviorComponent()
{
}

bool SeekBehaviorComponent::Update(float dt)
{
	SpatialComponent* spatial = this->GetSiblingComponent<SpatialComponent>();
	if (!spatial)
	{
		string s = ": can not obtain Spatial Component";
		GameLogger::log(this->GetName() + s);
		GameLogger::shutdownLog();
		return false;
	}
	if (m_target == glm::vec3(FLT_MAX, FLT_MAX, FLT_MAX))
	{
		string s = " : m_target was never set";
		GameLogger::log(this->GetName() + s);
		return false;
	}
	m_velocity = Seek(spatial->position,m_target);
	spatial->position += m_velocity * dt;
	/*string x = "x :" + std::to_string(spatial->position.x);
	string y = " , y :" + std::to_string(spatial->position.y);
	string z = " , z :" + std::to_string(spatial->position.z);
	GameLogger::log(x + y + z);*/
	return true;
}

bool SeekBehaviorComponent::Initialize()
{
	m_velocity = glm::vec3(0.0, 0.0, 0.0);
	return true;
}

