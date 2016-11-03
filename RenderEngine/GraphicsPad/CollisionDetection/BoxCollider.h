#pragma once
#include "../ImgnComponent.h"
#include "../ImgnProperties.h"
#include "glm.hpp"

class BoxCollider :
	public ImgnComponent
{
	IMGN_GENERATE(BoxCollider)
	IMGN_PROPERTY(isTrigger, false)
	IMGN_PROPERTY(center,glm::vec3(0, 0, 0))
	IMGN_PROPERTY(size,glm::vec3(0, 0, 0))
	IMGN_END(BoxCollider)
public:
	bool isTrigger;
	glm::vec3 center;
	glm::vec3 size;
};

