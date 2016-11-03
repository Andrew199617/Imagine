#pragma once
#include "SteeringBehaviors.h"
class FleeBehaviorComponent :
	public SteeringBehaviors
{
public:
	FleeBehaviorComponent();
	~FleeBehaviorComponent();

	// Inherited via SteeringBehaviors
	virtual void Update(float dt) override;
	virtual bool Initialize() override;
};

