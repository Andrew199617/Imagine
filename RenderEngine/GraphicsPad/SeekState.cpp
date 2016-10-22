#include "SeekState.h"



SeekState::SeekState()
{
}


SeekState::~SeekState()
{
}

void SeekState::Enter(StateComponent *, Imgn::Entity* entity)
{
	
	spatial = entity->GetComponentByType<SpatialComponent>();
	seek = entity->GetComponentByType<SeekBehaviorComponent>();
	if (spatial == 0 || seek == 0)
	{
		string str = "could not use a Component";
		GameLogger::log(m_name + str);
		GameLogger::shutdownLog();
		exit(1);
	}
	seek->Enable();
	seek->setTarget(m_target);
	seek->setVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
}

void SeekState::Execute(StateComponent * sc, Imgn::Entity* entity, float dt)
{
	//AIEntity* ai = reinterpret_cast<AIEntity*>(entity);
	static float m_dt = 0;

	/*string x = "x :" + std::to_string(spatial->position.x);
	string y = " , y :" + std::to_string(spatial->position.y);
	string z = " , z :" + std::to_string(spatial->position.z);
	GameLogger::log(entity->GetName() + x + y + z);*/

	if (glm::distance(spatial->position, m_target) <= m_radius)
	{
		if (!m_AtTarget)
		{
			seek->Disable();
			seek->setVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
			WhatDoWhenAtLocation(sc,entity,dt);
			m_AtTarget = true;
		}
	}

	WhenToChangeState(sc, entity, dt);
}

void SeekState::Exit(StateComponent *, Imgn::Entity*)
{
	seek->Disable();
	seek->setVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
}

