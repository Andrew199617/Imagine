#include "CollisionTester.h"



CollisionTester::CollisionTester()
{
}


CollisionTester::~CollisionTester()
{
}

float CollisionTester::rayTriangleIntersect(const glm::vec3 &rayOrg, const glm::vec3 &rayDelta, const glm::vec3 &p0, const glm::vec3 &p1, const glm::vec3 &p2, float minT)
{
	const float kNoIntersection = FLT_MAX;

	glm::vec3 e1 = p1 - p0;
	glm::vec3 e2 = p2 - p1;

	glm::vec3 n = glm::cross(e1, e2);

	float dot = glm::dot(n, rayDelta);
	if (!(dot < 0.0f))
	{
		return kNoIntersection;
	}

	float d = glm::dot(n, p0);

	float t = d - glm::dot(n,rayOrg);

	if (!(t <= 0.0f))
	{
		return kNoIntersection;
	}

	if (!(t >= dot * minT))
	{
		return kNoIntersection;
	}

	t /= dot;

	//assert(t >= 0.0f);
	//assert(t <= minT);
	if (!(t >= 0.0f) && !(t <= minT))
	{
		return kNoIntersection;
	}

	glm::vec3 p = rayOrg + rayDelta * t;

	float u0, u1, u2;
	float v0, v1, v2;
	if (fabs(n.x) > fabs(n.y))
	{
		if (fabs(n.x) > fabs(n.z))
		{
			u0 = p.y - p0.y;
			u1 = p1.y - p0.y;
			u2 = p2.y - p0.y;

			v0 = p.z - p0.z;
			v1 = p1.z - p0.z;
			v2 = p2.z - p0.z;
		}
		else
		{
			u0 = p.x - p0.x;
			u1 = p1.x - p0.x;
			u2 = p2.x - p0.x;

			v0 = p.y - p0.y;
			v1 = p1.y - p0.y;
			v2 = p2.y - p0.y;
		}
	}
	else
	{
		if (fabs(n.y) > fabs(n.z))
		{
			u0 = p.x - p0.x;
			u1 = p1.x - p0.x;
			u2 = p2.x - p0.x;

			v0 = p.z - p0.z;
			v1 = p1.z - p0.z;
			v2 = p2.z - p0.z;
		}
		else
		{
			u0 = p.x - p0.x;
			u1 = p1.x - p0.x;
			u2 = p2.x - p0.x;

			v0 = p.y - p0.y;
			v1 = p1.y - p0.y;
			v2 = p2.y - p0.y;
		}
	}

	float temp = u1 * v2 - v1 * u2;
	if (!(temp != 0.0f))
	{
		return kNoIntersection;
	}
	temp = 1.0f / temp;

	float alpha = (u0 * v2 - v0 * u2) * temp;
	if (!(alpha >= 0.0f))
	{
		return kNoIntersection;
	}

	float beta = (u1 * v0 - v1 * u0) * temp;
	if (!(beta >= 0.0f))
	{
		return kNoIntersection;
	}

	float gamma = 1.0f - alpha - beta;
	if (!(gamma >= 0.0f))
	{
		return kNoIntersection;
	}

	return t;
}

void CollisionTester::FindWall(glm::vec3 fromPosition, glm::vec3 rayDirection)
{
	fromPosition;
	rayDirection;
}


