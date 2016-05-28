#include "WanderingComponent.h"
#include "SpatialComponent.h"


WanderingComponent::WanderingComponent()
{
	srand(3);
	m_velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	int randmod = (int)(MAX_SPEED * 2);
	steering = glm::vec3(MAX_SPEED - (rand() % randmod), 0.0f, MAX_SPEED - (rand() % randmod));
}


WanderingComponent::~WanderingComponent()
{
}

bool WanderingComponent::Update(float dt)
{
	SpatialComponent* spatial = this->GetSiblingComponent<SpatialComponent>();
	if (!spatial)
	{
		string s = ": can not obtain Spatial Component";
		GameLogger::log(this->GetName() + s);
		GameLogger::shutdownLog();
		return false;
	}
	static float sumdt = 0;
	sumdt += dt;
	if (sumdt > 2)
	{
		steering = Wander(steering);
		m_velocity = glm::normalize(steering) * MAX_SPEED;
		sumdt = 0;
	}
	spatial->position += m_velocity * dt;

	//Helps Demostrate wandering
	if (spatial->position.z > m_Bound.z + m_Bound.offset)
	{
		m_velocity.z = -m_velocity.z;
		steering.z = -steering.z;
		
	}
	else if (spatial->position.z < m_Bound.z - m_Bound.offset)
	{
		m_velocity.z = -m_velocity.z;
		steering.z = -steering.z;
	}
	if (spatial->position.x < m_Bound.x - m_Bound.offset)
	{
		m_velocity.x = -m_velocity.x;
		steering.x = -steering.x;
	}
	else if (spatial->position.x > m_Bound.x + m_Bound.offset)
	{
		m_velocity.x = -m_velocity.x;
		steering.x = -steering.x;
	}
	return true;
}

bool WanderingComponent::Initialize()
{
	return true;
}