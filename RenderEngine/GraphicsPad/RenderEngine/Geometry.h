#pragma once
#include <string>
#pragma warning(push)
#pragma warning(disable:4201)
#include "glm.hpp"
#pragma warning(pop)
#include "../Vertex.h"
#include "GL\glew.h"
#include "AnimationInfo.h"

class Geometry
{
public:
	Geometry();
	~Geometry();
	unsigned m_vertexId;
	unsigned m_vertexByteOffset;
	unsigned m_vertexCount;
	unsigned m_vertexStride;
	unsigned m_indexId;
	unsigned m_indexByteOffset;
	unsigned m_indexCount;
	unsigned m_indexStride;
	std::string objName;
	std::string texturePath;
	int VertexFormat;
	void* vertices;
	void* Verts;
	void* indices;
	GLuint* indicesShort;
	AnimationInfo m_animationInfo;
};

