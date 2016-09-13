#pragma once
#include <string>
#pragma warning(push)
#pragma warning(disable : 4201)
#include <glm.hpp>
#pragma warning(pop)
#include <GL\glew.h>

using namespace std;
using namespace glm;

struct FbxData
{
	string name;

	vec3* verts;
	vec3* colors;
	vec2 texture[100];
	vec3* normals;

	//GLuint* positionIndicies;
	//GLuint* textureIndicies;
	//GLuint* normalIndicies;
	//GLuint* indices;

	int SceneOutputFormat;
	string outputColor;
	string outputTexture;
	string outputNormal;
};

