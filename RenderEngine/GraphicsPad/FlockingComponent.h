#pragma once
#include "SteeringBehaviors.h"
class FlockingComponent :
	public SteeringBehaviors
{
public:
	FlockingComponent();
	~FlockingComponent();

	// Inherited via SteeringBehaviors
	virtual void Update(float dt) override;
};

