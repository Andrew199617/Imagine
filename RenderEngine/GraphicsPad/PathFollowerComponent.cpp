#include "PathFollowerComponent.h"
#include "SeekBehaviorComponent.h"



PathFollowerComponent::PathFollowerComponent()
{
}


PathFollowerComponent::~PathFollowerComponent()
{
}

bool PathFollowerComponent::Initialize()
{
	m_pathFinder.setOwner(this);
	m_pathFinder.Initialize();
	return true;
}

void PathFollowerComponent::Update(float)
{
	
	SeekBehaviorComponent* seek = this->GetSiblingComponent<SeekBehaviorComponent>();
	if (!seek)
	{
		string str = ": can not obtain Seek Component";
		GameLogger::log(this->GetName() + str);
	}
	SpatialComponent* spatial = this->GetSiblingComponent<SpatialComponent>();
	if (!seek)
	{
		string str = ": can not obtain Spatial Component";
		GameLogger::log(this->GetName() + str);
	}
	

	if (!m_pathFinder.m_foundGoal)
	{
		m_pathFinder.FindPath(m_start,m_goal);
	}
	else if (m_pathFinder.m_foundGoal)
	{
		glm::vec3 target = m_pathFinder.NextPathPos(spatial, 1.0f);
		if (glm::distance(spatial->position, target) > 1.5f)
		{
			//seek->setVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
			seek->setTarget(target);
			seek->Enable();
		}
		else if (m_pathFinder.m_atTarget)
		{
			Done(seek);
		}
		else
		{
			seek->Disable();
			seek->setVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
			m_pathFinder.index++;
		}
	}
	if (m_pathFinder.m_noPathPossible)
	{
		Done(seek);
	}
	
}

void PathFollowerComponent::Done(SeekBehaviorComponent* seek)
{
	/*string s = ": I have finshed pathing";
	GameLogger::log(this->GetName() + s);*/
	seek->setVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
	seek->Disable();
	this->Disable();
	m_pathFinder.Initialize();
}
