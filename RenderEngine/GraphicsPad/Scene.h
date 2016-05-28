#pragma once
#include <GL\glew.h>
#include "Vertex.h"


struct Scene
{
	int numVertices;
	int numIndices;
	int sizeVertex;
	int sizeIndex;
	int SceneOutputFormat;
	void* vertices;
	void* indices;
};