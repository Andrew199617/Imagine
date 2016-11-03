#pragma once
#include "SteeringBehaviors.h"
class EvasionComponent :
	public SteeringBehaviors
{
public:
	EvasionComponent();
	~EvasionComponent();

	// Inherited via SteeringBehaviors
	virtual void Update(float dt) override;
};

