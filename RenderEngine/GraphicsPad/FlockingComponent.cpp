#include "FlockingComponent.h"
#include "SpatialComponent.h"


FlockingComponent::FlockingComponent()
{
}


FlockingComponent::~FlockingComponent()
{
}

void FlockingComponent::Update(float dt)
{
	SpatialComponent* spatial = this->GetSiblingComponent<SpatialComponent>();
	if (!spatial)
	{
		string s = ": can not obtain Spatial Component";
		GameLogger::log(this->GetName() + s);
		GameLogger::shutdownLog();
	}
	float localNeighboorhood = 5.0f;
	glm::vec3 SeperationVel = Seperation(spatial->GetPosition(), localNeighboorhood);
	glm::vec3 cohesionVel = Cohesion(spatial->GetPosition(), localNeighboorhood);
	glm::vec3 alignmentVel = Alignment(spatial->GetPosition(), localNeighboorhood);
	m_velocity = (SeperationVel * 2.0f + alignmentVel * 2.9f + cohesionVel * .15f) / 3.0f;
	spatial->SetPosition(spatial->GetPosition() + m_velocity * dt);

}
