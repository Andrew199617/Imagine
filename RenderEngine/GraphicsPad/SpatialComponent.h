#pragma once
#include "Component.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm.hpp>
#pragma warning(pop)

class SpatialComponent :
	public Component
{
	
public:
	SpatialComponent();
	~SpatialComponent();


	glm::vec3 position;
	glm::vec3 velocity;
	const glm::vec3 UP;
};

