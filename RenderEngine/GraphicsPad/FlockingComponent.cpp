#include "FlockingComponent.h"
#include "SpatialComponent.h"


FlockingComponent::FlockingComponent()
{
}


FlockingComponent::~FlockingComponent()
{
}

bool FlockingComponent::Update(float dt)
{
	SpatialComponent* spatial = this->GetSiblingComponent<SpatialComponent>();
	if (!spatial)
	{
		string s = ": can not obtain Spatial Component";
		GameLogger::log(this->GetName() + s);
		GameLogger::shutdownLog();
		return false;
	}
	float localNeighboorhood = 5.0f;
	glm::vec3 SeperationVel = Seperation(spatial->position, localNeighboorhood);
	glm::vec3 cohesionVel = Cohesion(spatial->position, localNeighboorhood);
	glm::vec3 alignmentVel = Alignment(spatial->position, localNeighboorhood);
	m_velocity = (SeperationVel * 2.0f + alignmentVel * 2.9f + cohesionVel * .15f) / 3.0f;
	spatial->position += m_velocity * dt;

	return true;
}
