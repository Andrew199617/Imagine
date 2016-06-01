#pragma once
#pragma warning(push)
#pragma warning(disable:4099)
#include "glm.hpp"
#include "ConfigReader.h"
#include "RenderEngine\Geometry.h"
#pragma warning(pop)

class ShapeGenerator
{
	
	static Geometry*  makePlaneVerts(unsigned dimension);
	static Geometry*  makePlaneIndices(unsigned dimension);
public:
	static Geometry*  DrawQuad();
	static Geometry*  makeLine(glm::vec3 point1, glm::vec3 point2);
	static Geometry*  readScene(string ObjName);
	static Geometry*  readScene(string File, string ObjName);
};

