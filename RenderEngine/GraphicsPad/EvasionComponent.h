#pragma once
#include "SteeringBehaviors.h"
class EvasionComponent :
	public SteeringBehaviors
{
public:
	EvasionComponent();
	~EvasionComponent();

	// Inherited via SteeringBehaviors
	virtual bool Update(float dt) override;
};

