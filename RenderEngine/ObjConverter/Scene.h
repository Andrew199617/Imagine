#pragma once
#include <GL\glew.h>
struct Vertex;


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