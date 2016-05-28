#pragma once
#include "SteeringBehaviors.h"
#include "Area.h"

class WanderingComponent :
	public SteeringBehaviors
{
private:
	Area m_Bound;
public:
	WanderingComponent();
	~WanderingComponent();

	// Inherited via SteeringBehaviors
	virtual bool Update(float dt) override;
	virtual bool Initialize() override;
	void SetBound(float x, float z, float offset) { m_Bound.x = x; m_Bound.z = z; m_Bound.offset = offset; }

	glm::vec3 steering;
};

