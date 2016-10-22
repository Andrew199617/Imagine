#pragma once
#include "ImgnComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm.hpp>
#pragma warning(pop)
#include "SpatialComponent.h"

typedef glm::vec3 SteeringForce;
#define FLOCKSIZE 12

class SteeringBehaviors : public ImgnComponent
{
public:
	SteeringBehaviors();
	~SteeringBehaviors();
	virtual bool Update(float dt) = 0;

public:
	SteeringForce Seek(glm::vec3 position, glm::vec3 target);
	SteeringForce Flee(glm::vec3 position, glm::vec3 target, glm::vec3 velocity);
	SteeringForce Pursuit(glm::vec3 position);
	SteeringForce Evasion(glm::vec3 position);
	SteeringForce Seperation(glm::vec3 position, float r);
	SteeringForce Cohesion(glm::vec3 position, float r);
	SteeringForce Alignment(glm::vec3 position, float r);
	SteeringForce Flocking();
	SteeringForce Hide();
	SteeringForce Wander(glm::vec3 steering);
	SteeringForce Arrival(glm::vec3 position, int slowing_distance);
	void setTarget(glm::vec3 target) { this->m_target = target; }
	void setVelocity(glm::vec3 vel) { this->m_velocity = vel; }
	glm::vec3 Target() { return this->m_target; }
	glm::vec3 getvel() { return m_velocity; }
	void setFlock(SpatialComponent* entities,int M_flockI) 
	{ 
		this->m_flockI = M_flockI;
		for (int i = 0; i < FLOCKSIZE; ++i)
		{
			m_flockPos[i] = entities[i].position;
			m_flockVel[i] = entities[i].velocity;
		}
	}
	int leader;
	
protected:
	const float MAX_SPEED = 15.0f;
	glm::vec3 m_velocity;
	glm::vec3 m_target;
	int m_flockI;
	glm::vec3 m_flockPos[FLOCKSIZE];
	glm::vec3 m_flockVel[FLOCKSIZE];
	
	
};

