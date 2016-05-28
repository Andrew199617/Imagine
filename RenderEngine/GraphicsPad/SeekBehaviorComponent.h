#pragma once
#include "SteeringBehaviors.h"

class SeekBehaviorComponent : 
	public SteeringBehaviors
{
public:
	SeekBehaviorComponent();
	~SeekBehaviorComponent();

	// Inherited via SteeringBehaviors
	virtual bool Update(float dt) override;
	virtual bool Initialize() override;
};

