#pragma once
#include "GL\glew.h"

struct Scene
{
	int numVertices;
	int numIndices;
	int sizeVertex;
	int sizeIndex;
	int SceneOutputFormat;
	bool hasAnimation;
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