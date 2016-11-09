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

void WanderingComponent::Update(float dt)
{
	SpatialComponent* spatial = this->GetSiblingComponent<SpatialComponent>();
	if (!spatial)
	{
		string s = ": can not obtain Spatial Component";
		GameLogger::log(this->GetName() + s);
		//GameLogger show.
	}
	static float sumdt = 0;
	sumdt += dt;
	if (sumdt > 2)
	{
		steering = Wander(steering);
		m_velocity = glm::normalize(steering) * MAX_SPEED;
		sumdt = 0;
	}
	spatial->SetPosition(spatial->GetPosition() + m_velocity * dt);

	//Helps Demostrate wandering
	if (spatial->GetPosition().z > m_Bound.z + m_Bound.offset)
	{
		m_velocity.z = -m_velocity.z;
		steering.z = -steering.z;
		
	}
	else if (spatial->GetPosition().z < m_Bound.z - m_Bound.offset)
	{
		m_velocity.z = -m_velocity.z;
		steering.z = -steering.z;
	}
	if (spatial->GetPosition().x < m_Bound.x - m_Bound.offset)
	{
		m_velocity.x = -m_velocity.x;
		steering.x = -steering.x;
	}
	else if (spatial->GetPosition().x > m_Bound.x + m_Bound.offset)
	{
		m_velocity.x = -m_velocity.x;
		steering.x = -steering.x;
	}
}

bool WanderingComponent::Initialize()
{
	return true;
}
