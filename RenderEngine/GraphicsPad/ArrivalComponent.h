#pragma once
#include "SteeringBehaviors.h"
class ArrivalComponent :
	public SteeringBehaviors
{
public:
	ArrivalComponent();
	~ArrivalComponent();

	// Inherited via SteeringBehaviors
	virtual bool Update(float dt) override;
};

