#pragma once
#include "SteeringBehaviors.h"
class PursuitComponent :
	public SteeringBehaviors
{
public:
	PursuitComponent();
	~PursuitComponent();

	// Inherited via SteeringBehaviors
	virtual void Update(float dt) override;
};

