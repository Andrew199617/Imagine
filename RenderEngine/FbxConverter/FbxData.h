#pragma once
#include <string>
#pragma warning(push)
#pragma warning(disable : 4201)
#include <glm.hpp>
#pragma warning(pop)
//#include <GL\glew.h>

using namespace std;

struct FbxData
{
	string name;

	glm::vec3* verts;
	glm::vec3* colors;
	glm::vec2 texture[1000];
	glm::vec3* normals;

	int numVerts;
	int numIndcies;
	int SceneOutputFormat;
};

