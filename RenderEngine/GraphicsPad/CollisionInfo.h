#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include "glm.hpp"
#pragma warning(pop)

struct CollisionInfo
{
	CollisionInfo(float minT, glm::vec3 p0 = glm::vec3(0, 0, 0), glm::vec3 p1 = glm::vec3(0, 0, 0), glm::vec3 p2 = glm::vec3(0, 0, 0))
	{
		this->minT = minT;
		this->p0 = p0;
		this->p1 = p1;
		this->p2 = p2;
	}
	float minT;
	glm::vec3 p0;
	glm::vec3 p1;
	glm::vec3 p2;

};