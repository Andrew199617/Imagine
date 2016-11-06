#pragma once
#include "../ImgnComponent.h"
#include "../ImgnProperties.h"
#include "glm.hpp"
#include <vector>

class ImgnCollider : public ImgnComponent
{
	
public:
	ImgnCollider();
	~ImgnCollider() {}
protected:
	bool isTrigger;
	glm::vec3 center;


	void Awake() override
	{
	}
	
	Imgn::CollisionData* collisionData;
};

