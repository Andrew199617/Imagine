#pragma once
#include "StateMachine\State.h"
#include "SpatialComponent.h"
#include "SeekBehaviorComponent.h"
#include "StateMachine\StateComponent.h"
#include"HealthEntity.h"

class SeekState :
	public State
{
public:
	SeekState();
	~SeekState();

protected:
	SpatialComponent* spatial;
	SeekBehaviorComponent* seek;
	glm::vec3 m_target;
	float m_radius;
	bool m_AtTarget;

	// Inherited via State
	virtual void Enter(StateComponent *, Entity *) override;
	virtual void Execute(StateComponent *, Entity *, float) override;
	virtual void Exit(StateComponent *, Entity *) override;
	virtual void WhatDoWhenAtLocation(StateComponent *, Entity *, float) = 0;
	virtual void WhenToChangeState(StateComponent *, Entity *, float) = 0;

};

