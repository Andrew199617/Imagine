#pragma once
#include "GL\glew.h"
#include "glm.hpp"

struct Scene
{
	int numVertices;
	int numIndices;
	int sizeVertex;
	int sizeIndex;
	int SceneOutputFormat;
	bool hasAnimation;
	void* centerOfMass;
	void* vertices;
	void* indices;
};

struct AnimationScene
{
	int animationLength;
	//int numKeys;
	//void* keys;
	void* animationData;
};