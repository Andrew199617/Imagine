#pragma once
#include <string>
#pragma warning(push)
#pragma warning(disable : 4201)
#include <glm.hpp>
#pragma warning(pop)
//#include <GL\glew.h>
#include "fbxsdk.h"

using namespace std;

struct FbxData
{
	string name;

	glm::vec3* verts;
	glm::vec3* colors;
	glm::vec2* texture;
	glm::vec3* normals;

	glm::vec3 centerOfMass;

	int numVerts;
	int numIndcies;
	int SceneOutputFormat;

	int animationLength;
	bool hasAnimation;
	int numKeys;
	FbxTime* keys;
	glm::mat4* animationData;
};

