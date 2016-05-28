#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm.hpp>
#pragma warning(pop)
#include "Entity.h"


class CollisionTester
{
public:
	CollisionTester();
	~CollisionTester();

	static float rayTriangleIntersect(const glm::vec3 &rayOrg, const glm::vec3 &rayDelta,
		const glm::vec3 &p0, const glm::vec3 &p1, const glm::vec3 &p2, float minT);
	void FindWall(glm::vec3 fromPosition, glm::vec3 rayDirection);
	void FindWall(Entity entity);
	void FindFloor(Entity entity);

};

