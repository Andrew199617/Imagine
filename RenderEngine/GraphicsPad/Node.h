#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm.hpp>
#pragma warning(pop)

class Node
{
public:
	Node() : id((unsigned)-1) {}
	glm::vec3 position;
	unsigned id;
};