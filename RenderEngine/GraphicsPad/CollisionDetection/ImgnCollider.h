#pragma once
#include "../ImgnComponent.h"
#include "../ImgnProperties.h"
#include "glm.hpp"

class ImgnCollider : public ImgnComponent
{
	
public:
	~ImgnCollider() {}
protected:
	bool isTrigger;
	glm::vec3 center;


	void Awake() override
	{
	}

};