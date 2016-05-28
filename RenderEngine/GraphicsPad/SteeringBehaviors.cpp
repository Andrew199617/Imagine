#include "SteeringBehaviors.h"
#include "SpatialComponent.h"
#include <time.h> 


SteeringBehaviors::SteeringBehaviors()
{
}


SteeringBehaviors::~SteeringBehaviors()
{
}

SteeringForce SteeringBehaviors::Seek(glm::vec3 position, glm::vec3 target)
{
	glm::vec3 steering = glm::vec3(0.0f,0.0f,0.0f);
	glm:: vec3 desired_velocity = glm::normalize(target - position) * MAX_SPEED;
	if(glm::distance(target,position) > 0.1f)
	steering = desired_velocity - m_velocity;
	return steering;
}

SteeringForce SteeringBehaviors::Flee(glm::vec3 position, glm::vec3 target, glm::vec3 velocity)
{
	glm::vec3 steering;
	glm::vec3 desired_velocity = glm::normalize(position - target) * MAX_SPEED;
	steering = desired_velocity - velocity;
	return steering;
}

SteeringForce SteeringBehaviors::Pursuit(glm::vec3 position)
{
	glm::vec3 steering;
	static glm::vec3 lastTargetLocation = m_target;
	glm::vec3 target = lastTargetLocation - m_target;
	lastTargetLocation = m_target;
	steering = Seek(position,(target * 15.0f) + m_target) / 2.0f;
	return steering;
}

SteeringForce SteeringBehaviors::Evasion(glm::vec3 position)
{
	glm::vec3 steering;
	static glm::vec3 lastTargetLocation = m_target;
	glm::vec3 target = lastTargetLocation - m_target;
	lastTargetLocation = m_target;
	steering = Flee(position, (target * 15.0f) + m_target, m_velocity) / 2.5f;
	return steering;
}

SteeringForce SteeringBehaviors::Seperation(glm::vec3 position, float r)
{
	glm::vec3 steering = glm::vec3(0.0f,0.0f,0.0f);
	for (int i = 0; i < FLOCKSIZE; ++i)
	{
		//dont check yourself
		if (i != m_flockI)
		{
			glm::vec3 dist = position - m_flockPos[i];
			if (glm::length(dist) < r)
			{
				steering += glm::normalize(dist)/ glm::length(dist);
			}
		}
		
	}
	return steering;
}

SteeringForce SteeringBehaviors::Cohesion(glm::vec3 position, float r)
{
	glm::vec3 steering, CenterOfMass;
	int NeighborCount = 0;
	for (int i = 0; i < FLOCKSIZE; ++i)
	{
		//dont check yourself
		if (i != m_flockI)
		{
			glm::vec3 dist = position - m_flockPos[i];
			if (glm::length(dist) < r)
			{
				CenterOfMass += m_flockPos[i];
				NeighborCount++;
			}
		}
	}
	if (NeighborCount > 2)
	{
		CenterOfMass /= (double)NeighborCount;
		
		steering = Seek(position, CenterOfMass);
	}

	return steering;
}

SteeringForce SteeringBehaviors::Alignment(glm::vec3 position, float r)
{
	glm::vec3 average = glm::vec3(0.0f,0.0f,0.0f);
	int NeighborCount = 0;
	for (int i = 0; i < FLOCKSIZE; ++i)
	{
		//dont check yourself
		if (i != m_flockI)
		{
			glm::vec3 dist = position - m_flockPos[i];
			if (glm::length(dist) < r + 10 && i == leader)
			{
				average += m_flockVel[i];
				++NeighborCount;
			}
		}
	}
	if (NeighborCount > 0)
	{
		average /= (double)NeighborCount;
		average -= m_flockVel[m_flockI];
	}
	return average;
}

SteeringForce SteeringBehaviors::Flocking()
{
	return SteeringForce();
}

SteeringForce SteeringBehaviors::Hide()
{
	return SteeringForce();
}

SteeringForce SteeringBehaviors::Wander(glm::vec3 steering)
{
	
	int randpom = rand() % 2;
	if (randpom > 1)
	{
		steering.x += rand() % 2;
		steering.z += rand() % 2;
	}
	else
	{
		steering.x -= rand() % 2;
		steering.z -= rand() % 2;
	}

	if (steering.x > MAX_SPEED)
	{
		steering.x = MAX_SPEED;
	}
	else if (steering.z > MAX_SPEED)
	{
		steering.z = MAX_SPEED;
	}
	else if (steering.x < -MAX_SPEED)
	{
		steering.x = -MAX_SPEED;
	}
	else if (steering.z < -MAX_SPEED)
	{
		steering.z = -MAX_SPEED;
	}
	return steering;
}

SteeringForce SteeringBehaviors::Arrival(glm::vec3 position,int slowing_distance)
{
	glm::vec3 steering;
	glm::vec3 ToTarget = m_target - position;
	float distance = glm::length(ToTarget);
	if (distance > 0)
	{
		//because Deceleration is enumerated as an int, this value is required
		//to provide fine tweaking of the deceleration.
		const double DecelerationTweaker = 0.3;
		//calculate the speed required to reach the target given the desired
		//deceleration
		float speed = distance / (slowing_distance *(float)DecelerationTweaker);
		//make sure the velocity does not exceed the max
		speed = glm::min(speed, MAX_SPEED);
		//from here proceed just like Seek except we don't need to normalize
		//the ToTarget vector because we have already gone to the trouble
		//of calculating its length: dist.
		glm::vec3 DesiredVelocity = ToTarget * speed / distance;
		steering = DesiredVelocity - m_velocity;
	}
	
	return steering;
}
